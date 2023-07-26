#include <stdio.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int32.h>
#include <rmw_microros/rmw_microros.h>

#include "pico/stdlib.h"
#include "pico_transport.h"
#include "pico/ultrasound_publisher.hpp"

const uint LED_PIN = 25;

rcl_publisher_t counter_publisher;
std_msgs__msg__Int32 counter_msg;

void counter_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    rcl_ret_t ret = rcl_publish(&counter_publisher, &counter_msg, NULL);
    counter_msg.data++;
}

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

    rcl_timer_t counter_timer;
    rcl_timer_t blink_timer;
    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor;

    allocator = rcl_get_default_allocator();

    // Wait for agent successful ping for 2 minutes.
    const int timeout_ms = 1000;
    const uint8_t attempts = 120;

    rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);

    if (ret != RCL_RET_OK)
    {
        // Unreachable agent, exiting program.
        return ret;
    }

    rclc_support_init(&support, 0, NULL, &allocator);

    rclc_node_init_default(&node, "pico_node", "", &support);
    rclc_publisher_init_default(
        &counter_publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "pico_counter_publisher");

    rclc_timer_init_default(
        &counter_timer,
        &support,
        RCL_MS_TO_NS(1000),
        counter_callback);

    rclc_timer_init_default(
        &blink_timer,
        &support,
        RCL_MS_TO_NS(500),
        blink_callback);

    rclc_executor_init(&executor, &support.context, 3, &allocator);
    rclc_executor_add_timer(&executor, &counter_timer);
    rclc_executor_add_timer(&executor, &blink_timer);

    // pet::pico::UltrasoundPublisher ultrasound_publisher{26, 26, "ultrasound"};
    // ultrasound_publisher.init(node, support, executor);
    
    int pin = 29;
    pet::pico::create_ultrasound_publisher(pin, pin, "ultrasound");
    pet::pico::init_ultrasound_publisher(node, support, executor);

    counter_msg.data = 0;
    while (true)
    {
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    }
    return 0;
}
