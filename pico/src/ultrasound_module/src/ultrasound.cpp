#include "pico/ultrasound.hpp"

#include <pico/stdlib.h>

namespace pet
{
namespace pico
{

namespace
{

auto micros()
{
    return to_us_since_boot(get_absolute_time());
}

}

Ultrasound::Ultrasound(int trigger_pin, int echo_pin)
    : m_trigger_pin(trigger_pin)
    , m_echo_pin(echo_pin)
{
    gpio_init(m_trigger_pin);
    gpio_set_dir(m_trigger_pin, GPIO_OUT);

    gpio_init(m_echo_pin);
    gpio_set_dir(m_echo_pin, GPIO_IN);

    gpio_put(m_trigger_pin, GPIO_LOW);
}

bool Ultrasound::start_ping()
{
    stop_ping();
    m_echo_recieved = false;
    if (!ping_trigger()) // Trigger a ping, if it returns false, return without starting the echo timer.
    {
        return false;
    }

    return add_repeating_timer_us(kEchoTimerFreq_us, Ultrasound::interrupt_callback, this, &m_timer_info);
}

void Ultrasound::stop_ping()
{
    if (m_timer_info.alarm_id > 0) // If timer is active, cancel it.
    {
        cancel_repeating_timer(&m_timer_info);
    }
}

float Ultrasound::get_distance() const
{
    if (m_echo_recieved) {
        return convert_to_distance(m_ping_duration_us);
    } else {
        return -1.0f;
    }
}

bool Ultrasound::echo_check()
{
    if (micros() > m_ping_timeout_us) // Outside the time-out limit.
    {
        m_echo_recieved = false;
        return false; // Disable timer interrupt.
    }

    if (!gpio_get(m_echo_pin)) // Ping echo received.
    {
        m_ping_duration_us = (micros() - (m_ping_timeout_us - kMaxRoundtripDuration_us) - kPingTimerOverhead_us); // Calculate ping time including overhead.
        m_echo_recieved = true;
        return false; // Disable timer interrupt.
    }

    m_echo_recieved = false; // false because there's no ping echo yet.
    return true; // Continue timer interrupts.
}

bool Ultrasound::interrupt_callback(repeating_timer_t *timer_info)
{
    Ultrasound *current_sensor = reinterpret_cast<Ultrasound *>(timer_info->user_data);
    return current_sensor->echo_check();
}

bool Ultrasound::ping_trigger()
{
	gpio_put(m_trigger_pin, GPIO_HIGH);  // Set trigger pin high, this tells the sensor to send out a ping.
	sleep_us(kTriggerWidth_us);          // Wait long enough for the sensor to realize the trigger pin is high.
	gpio_put(m_trigger_pin, GPIO_LOW);   // Set trigger pin back to low.

    if (gpio_get(m_echo_pin))
    {
        return false; // Previous ping hasn't finished, abort.
    }

    /// TODO: Remove or minimise blocking of execution.
    // Maximum time we'll wait for ping to start.
    const uint64_t starting_timeout = micros() + kMaxRoundtripDuration_us + kMaxSensorDelay_us;
    while (!gpio_get(m_echo_pin))
    {
        if (micros() > starting_timeout)
        {
            return false; // Took too long to start, abort.
        }
    }

    // Ping started successfully, set the time-out.
	m_ping_timeout_us = micros() + kMaxRoundtripDuration_us;
	return true;
}

float Ultrasound::convert_to_distance(int roundtrip_duration_us)
{
    return roundtrip_duration_us / 2 * kSpeedOfSound_mps / 1'000'000;
}

} // namespace pico
} // namespace pet
