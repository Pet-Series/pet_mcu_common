#ifndef PET_PICO_ULTRASOUND_PUBLISHER_H
#define PET_PICO_ULTRASOUND_PUBLISHER_H

#include <sensor_msgs/msg/range.h>

#include <rclc/executor.h>
#include <rclc/publisher.h>
#include <rclc/timer.h>

#include "pico/ultrasound.h"

namespace pet
{
namespace pico
{

void create_ultrasound_publisher(int trigger_pin, int echo_pin, const char* id);

void init_ultrasound_publisher(const rcl_node_t &node, rclc_support_t &support, rclc_executor_t &executor);

class UltrasoundPublisher
{
  public:
    UltrasoundPublisher() = default;
    UltrasoundPublisher(int trigger_pin, int echo_pin, const char* id);

    void init(const rcl_node_t &node, rclc_support_t &support, rclc_executor_t &executor);

    void timer_callback(rcl_timer_t *timer, int64_t last_call_time);

  private:
    Ultrasound m_sensor;

    rcl_publisher_t         m_publisher{};
    rcl_timer_t             m_timer{};
    sensor_msgs__msg__Range m_msg{};
};

} // namespace pico
} // namespace pet

#endif // PET_PICO_ULTRASOUND_PUBLISHER_H