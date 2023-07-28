#pragma once

#include <pico/stdlib.h>

namespace pet
{
namespace pico
{

constexpr bool GPIO_HIGH = true;
constexpr bool GPIO_LOW  = false;

class Ultrasound
{
public:
    static constexpr float kMinDistance_m           = 0.02f;  // [m] Minimum distance we trust the sensor for.
    static constexpr float kMaxDistance_m           = 4.0f;   // [m] Maximum distance we want to ping for. Maximum sensor distance is rated at 4-5 m.

private:
    static constexpr float kSpeedOfSound_mps        = 343.0f; // [m/s] Approximate speed of sound in dry air at 20 °C.
    static constexpr int   kMaxRoundtripDuration_us = 2 * kMaxDistance_m / kSpeedOfSound_mps * 1'000'000; // [us] Maximum flight time of one roundtrip. 

    static constexpr int   kTriggerWidth_us         = 12;     // [us] Width of box signal to trigger sensor to start a ping.
    static constexpr int   kMaxSensorDelay_us       = 5800;   // [us] Maximum time it takes for sensor to start the ping.
    static constexpr int   kEchoTimerFreq_us        = 24;     // [us] Frequency to check for a ping echo (every 24uS is about 0.4cm accuracy).
    static constexpr int   kPingTimerOverhead_us    = 13;     // [us] Overhead subtracted from measured flight time of ping.

public:
    Ultrasound() : Ultrasound(-1, -1, "") {}
    Ultrasound(int trigger_pin, int echo_pin, const char* id);

    /// @brief Start a new sensor ping.
    /// @return true if ping was started successfully, false otherwise.
    bool start_ping();
    void stop_ping();

    /// @return Measured distance in meters [m]
    float get_distance() const;

    const char* frame_id() const;
    const char* topic() const;

private:
    /// @return true to continue repeating, false to stop.
    /// @note This function will be called inside an interrupt.
    bool echo_check();

    bool ping_trigger();

    /// @return true to continue repeating, false to stop.
    /// @note This function will be called inside an interrupt.
    static bool interrupt_callback(repeating_timer_t *timer_info);

    /// @brief Calculate the distance to an object given the total roundtrip flight time.
    /// @param roundtrip_duration_us [us] The time it took the sound wave to reach the object and bounce back.
    /// @return [m] The distance to the object in meters.
    static float convert_to_distance(int roundtrip_duration_us);

private:
    int m_trigger_pin;
    int m_echo_pin;
    const char* m_id;

    bool m_echo_recieved = false;
    int m_ping_duration_us;
    int m_ping_timeout_us;

    repeating_timer_t m_timer_info;
};

} // namespace pico
} // namespace pet
