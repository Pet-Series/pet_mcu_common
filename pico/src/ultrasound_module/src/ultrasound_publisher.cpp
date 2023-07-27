#include "pico/ultrasound_publisher.hpp"

#include <cstring>

#include <sensor_msgs/msg/range.h>

#include <rcl/time.h>
#include <rclc/publisher.h>
#include <rclc/timer.h>

namespace pet
{
namespace pico
{

UltrasoundPublisher::UltrasoundPublisher(int trigger_pin, int echo_pin, const char* id)
    : m_sensor(trigger_pin, echo_pin, id)
{
    std::strncpy(m_frame_id, id, kFrameIdCapacity); 
    m_frame_id[kFrameIdCapacity-1] = '\0'; // Ensure frame id is always null terminated.

    m_msg.header.frame_id.data     = m_frame_id;
    m_msg.header.frame_id.size     = std::strlen(m_frame_id);
    m_msg.header.frame_id.capacity = kFrameIdCapacity;
}

rcl_timer_t &UltrasoundPublisher::get_timer()
{
    return m_timer;
}

void UltrasoundPublisher::init(const rcl_node_t &node)
{
    rclc_publisher_init_default(
        &m_publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Range),
        m_sensor.topic());

    rcl_allocator_t allocator = rcl_get_default_allocator();
    rcl_ros_clock_init(&m_clock, &allocator);

    m_sensor.start_ping();
}

void UltrasoundPublisher::timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    m_sensor.stop_ping();

    int64_t current_time_ns;
    rcl_clock_get_now(&m_clock, &current_time_ns);

    m_msg.header.stamp.sec     = current_time_ns / 1'000'000'000;
    m_msg.header.stamp.nanosec = current_time_ns % 1'000'000'000;
    m_msg.range                = m_sensor.get_distance();

    const auto result = rcl_publish(&m_publisher, &m_msg, nullptr);

    m_sensor.start_ping();
}

} // namespace pico
} // namespace pet