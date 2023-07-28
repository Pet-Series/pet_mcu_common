#pragma once

#include <array>
#include <cstring>

#include <sensor_msgs/msg/range.h>

#include <rcl/time.h>
#include <rclc/publisher.h>
#include <rclc/timer.h>

#include "pico/ultrasound.h"

namespace pet
{
namespace pico
{

constexpr float deg2rad(float degrees)
{
    constexpr float pi = 3.141593;
    return degrees * pi / 180.0f;
}

template<int kSensorCount>
class UltrasoundModule
{
private:
    static constexpr int    kFrequency_hz    = 10;
    static constexpr size_t kFrameIdCapacity = 40;

public:
    UltrasoundModule(const std::array<int, kSensorCount>         &trigger_pins,
                     const std::array<int, kSensorCount>         &echo_pins,
                     const std::array<const char*, kSensorCount> &sensor_ids);

    void init(const rcl_node_t &node);

    void timer_callback(rcl_timer_t *timer, int64_t last_call_time);

    rcl_timer_t &get_timer();

  private:
    std::array<Ultrasound, kSensorCount>              m_sensors;
    std::array<rcl_publisher_t, kSensorCount>         m_publishers;
    std::array<sensor_msgs__msg__Range, kSensorCount> m_messages;

    rcl_timer_t m_timer{};
    rcl_clock_t m_clock{};

    int m_current_sensor = 0;
};

template<int kSensorCount>
UltrasoundModule<kSensorCount>::UltrasoundModule(const std::array<int, kSensorCount>         &trigger_pins,
                                                 const std::array<int, kSensorCount>         &echo_pins,
                                                 const std::array<const char*, kSensorCount> &sensor_ids)
{
    for (int i = 0; i < kSensorCount; ++i)
    {
        m_sensors[i] = Ultrasound{trigger_pins[i], echo_pins[i], sensor_ids[i]};

        // std::strlen does not count the null character, so we add one to the length.
        const size_t id_length = std::strlen(sensor_ids[i]) + 1;
        m_messages[i].header.frame_id.data     = new char[id_length];
        m_messages[i].header.frame_id.size     = id_length;
        m_messages[i].header.frame_id.capacity = id_length;

        // Copy frame id and set the null character.
        std::strcpy(m_messages[i].header.frame_id.data, sensor_ids[i]); 
        m_messages[i].header.frame_id.data[id_length-1] = '\0';

        // Set sensor meta data.
        m_messages[i].radiation_type = sensor_msgs__msg__Range__ULTRASOUND;
        m_messages[i].field_of_view  = deg2rad(50);
        m_messages[i].min_range      = Ultrasound::kMinDistance_cm / 100.0f;
        m_messages[i].max_range      = Ultrasound::kMaxDistance_cm / 100.0f;
    }
}

template<int kSensorCount>
void UltrasoundModule<kSensorCount>::init(const rcl_node_t &node)
{
    for (int i = 0; i < kSensorCount; ++i)
    {
        rclc_publisher_init_default(
            &m_publishers[i],
            &node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Range),
            m_sensors[i].topic());
    }

    rcl_allocator_t allocator = rcl_get_default_allocator();
    const auto clock_result = rcl_ros_clock_init(&m_clock, &allocator);

    m_sensors[m_current_sensor].start_ping();
}

template<int kSensorCount>
void UltrasoundModule<kSensorCount>::timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{    
    auto& current_sensor = m_sensors[m_current_sensor];

    current_sensor.stop_ping();

    int64_t current_time_ns;
    const auto clock_result = rcl_clock_get_now(&m_clock, &current_time_ns);

    m_messages[m_current_sensor].header.stamp.sec     = current_time_ns / 1'000'000'000;
    m_messages[m_current_sensor].header.stamp.nanosec = current_time_ns % 1'000'000'000;
    m_messages[m_current_sensor].range                = current_sensor.get_distance();

    const auto publish_result = rcl_publish(&m_publishers[m_current_sensor], &m_messages[m_current_sensor], nullptr);

    m_current_sensor = (m_current_sensor + 1) % kSensorCount;
    m_sensors[m_current_sensor].start_ping();
}

template<int kSensorCount>
rcl_timer_t &UltrasoundModule<kSensorCount>::get_timer()
{
    return m_timer;
}

} // namespace pico
} // namespace pet
