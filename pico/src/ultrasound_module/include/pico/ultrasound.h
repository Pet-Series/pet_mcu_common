#ifndef PET_PICO_ULTRASOUND_H
#define PET_PICO_ULTRASOUND_H

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
    static constexpr int kMinDistance_cm       = 2;     // [cm] Minimum distance we trust the sensor for.
    static constexpr int kMaxDistance_cm       = 400;   // [cm] Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
    static constexpr int kUsRoundtripCm        = 57;    // [us * 2cm^-1] Microseconds it takes sound to travel round-trip 1cm (2cm total).
    static constexpr int kTriggerWidth_us      = 12;    // [us] Width of box signal to trigger sensor to start a ping.
    static constexpr int kMaxSensorDelay_us    = 5800;  // [us] Maximum time it takes for sensor to start the ping.
    static constexpr int kEchoTimerFreq_us     = 24;    // [us] Frequency to check for a ping echo (every 24uS is about 0.4cm accuracy).
    static constexpr int kPingTimerOverhead_us = 13;    // [us] Overhead subtracted from measured flight time of ping.

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
    void echo_check();

    bool ping_trigger(); // From NewPing

    static bool interrupt_callback(repeating_timer_t *timer_info);

private:
    int m_trigger_pin;
    int m_echo_pin;
    const char* m_id;

    bool m_echo_recieved = false;
    int m_ping_duration_us;

    int m_max_echo_time_us;
    int m_ping_timeout_us;
    bool m_one_pin_mode;

    repeating_timer_t m_timer_info;

    // TODO: Protect this from concurrent use. Maybe a mutex-like variable?
    static Ultrasound* s_current_sensor;
};

} // namespace pico
} // namespace pet

#endif // PET_PICO_ULTRASOUND_H
