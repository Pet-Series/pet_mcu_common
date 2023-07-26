#include "pico/ultrasound_publisher.hpp"

#include <sensor_msgs/msg/range.h>

#include <rclc/publisher.h>
#include <rclc/timer.h>

namespace pet
{
namespace pico
{

UltrasoundPublisher::UltrasoundPublisher(int trigger_pin, int echo_pin, const char* id)
    : m_sensor(trigger_pin, echo_pin, id)
{
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

    m_sensor.start_ping();
}

void UltrasoundPublisher::timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    m_sensor.stop_ping();

    /// TODO: Set header timestamp and frame_id.
    // m_msg.header.stamp    = Time.now();
    // m_msg.header.frame_id = m_sensor.frame_id();
    m_msg.range           = m_sensor.get_distance();

    const auto result = rcl_publish(&m_publisher, &m_msg, nullptr);

    // m_sensor.start_ping();
}

} // namespace pico
} // namespace pet