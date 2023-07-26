#include "pico/ultrasound_publisher.hpp"

#include <sensor_msgs/msg/range.h>

#include <rclc/executor.h>
#include <rclc/publisher.h>
#include <rclc/timer.h>

namespace pet
{
namespace pico
{
namespace
{

UltrasoundPublisher g_ultrasound_publisher{};

} // namespace

void create_ultrasound_publisher(int trigger_pin, int echo_pin, const char* id)
{
    g_ultrasound_publisher = UltrasoundPublisher(trigger_pin, echo_pin, id);
}

void init_ultrasound_publisher(const rcl_node_t &node, rclc_support_t &support, rclc_executor_t &executor)
{
    g_ultrasound_publisher.init(node, support, executor);
}

void static_timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    g_ultrasound_publisher.timer_callback(timer, last_call_time);
}

UltrasoundPublisher::UltrasoundPublisher(int trigger_pin, int echo_pin, const char* id)
    : m_sensor(trigger_pin, echo_pin, id)
{
}

void UltrasoundPublisher::init(const rcl_node_t &node, rclc_support_t &support, rclc_executor_t &executor)
{
    rclc_publisher_init_default(
        &m_publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Range),
        m_sensor.topic());

    rclc_timer_init_default(
        &m_timer,
        &support,
        RCL_MS_TO_NS(100),
        static_timer_callback); /// TODO: Can callback be non-static?

    rclc_executor_add_timer(&executor, &m_timer);

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