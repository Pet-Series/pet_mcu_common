#pragma once

#include <sensor_msgs/msg/range.h>

#include <rcl/time.h>
#include <rclc/publisher.h>
#include <rclc/timer.h>

#include "pico/ultrasound.h"

namespace pet
{
namespace pico
{

class UltrasoundPublisher
{
  public:
    UltrasoundPublisher() = default;
    UltrasoundPublisher(int trigger_pin, int echo_pin, const char* id);

    rcl_timer_t &get_timer();

    void init(const rcl_node_t &node);

    void timer_callback(rcl_timer_t *timer, int64_t last_call_time);

  private:
    static constexpr size_t kFrameIdCapacity = 40;

  private:
    Ultrasound m_sensor;

    rcl_publisher_t         m_publisher{};
    rcl_timer_t             m_timer{};
    rcl_clock_t             m_clock{};
    sensor_msgs__msg__Range m_msg{};

    char m_frame_id[kFrameIdCapacity];
};

} // namespace pico
} // namespace pet
