#include <array>
#include <stdio.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>

#include "pico/stdlib.h"
#include "pico_transport.h"
#include "pico/ultrasound_module.hpp"

namespace pet
{
namespace pico
{

void register_left_right_ultrasound(const rcl_node_t &node, rclc_support_t &support, rclc_executor_t &executor)
{
    static constexpr int kTriggerPinLeft  = 8;
    static constexpr int kEchoPinLeft     = 9;
    static constexpr int kTriggerPinRight = 22;
    static constexpr int kEchoPinRight    = 26;

    static constexpr auto kTriggerPins = std::array{kTriggerPinLeft, kTriggerPinRight};
    static constexpr auto kEchoPins    = std::array{kEchoPinLeft, kEchoPinRight};
    static constexpr auto kSensorIds   = std::array{"ultrasound/top_left", "ultrasound/top_right"};

    static UltrasoundModule<2> ultrasound_module(kTriggerPins, kEchoPins, kSensorIds);

    ultrasound_module.init(node);

    rclc_timer_init_default(
        &ultrasound_module.get_timer(),
        &support,
        RCL_MS_TO_NS(ultrasound_module.get_timer_period_ms()),
        [](rcl_timer_t *timer, int64_t last_call_time) {
            return ultrasound_module.timer_callback(timer, last_call_time);
        });

    rclc_executor_add_timer(&executor, &ultrasound_module.get_timer());
}

} // namespace pico
} // namespace pet

constexpr uint LED_PIN = 25;

void blink_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    static bool led_status = true;
    gpio_put(LED_PIN, led_status);
    led_status = !led_status;
}

int main()
{
    rmw_uros_set_custom_transport(
		true,
		NULL,
		pico_serial_transport_open,
		pico_serial_transport_close,
		pico_serial_transport_write,
		pico_serial_transport_read
	);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    rcl_timer_t blink_timer;
    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor;

    allocator = rcl_get_default_allocator();

    // Wait for agent successful ping for 2 minutes.
    const int timeout_ms = 1000;
    const uint8_t attempts = 120;

    const rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);
    if (ret != RCL_RET_OK)
    {
        // Unreachable agent, exiting program.
        return ret;
    }

    rclc_support_init(&support, 0, NULL, &allocator);

    rclc_node_init_default(&node, "pico_node", "", &support);

    rclc_timer_init_default(
        &blink_timer,
        &support,
        RCL_MS_TO_NS(500),
        blink_callback);

    rclc_executor_init(&executor, &support.context, 3, &allocator);
    rclc_executor_add_timer(&executor, &blink_timer);

    // pet::pico::register_top_left_ultrasound(node, support, executor);
    // pet::pico::register_top_right_ultrasound(node, support, executor);
    pet::pico::register_left_right_ultrasound(node, support, executor);

    while (true)
    {
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    }
    return 0;
}
