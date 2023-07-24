#ifndef PET_PICO_ULTRASOUND_H
#define PET_PICO_ULTRASOUND_H

namespace pet
{
namespace pico
{

class Ultrasound
{
public:
    static constexpr int kMinDistance_cm = 2;    // [cm] Minimum distance we trust the sensor for.
    static constexpr int kMaxDistance_cm = 400;  // [cm] Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

public:
    Ultrasound() : Ultrasound(-1, -1, "") {}
    Ultrasound(int trigger_pin, int echo_pin, const char* id);

    void start_ping();
    void stop_ping();

    /// @return Measured distance in meters [m]
    float get_distance() const;

    const char* frame_id() const;
    const char* topic() const;

private:
    void echo_check();

    bool ping_trigger(); // From NewPing

    static void interrupt_callback();

private:
    int m_trigger_pin;
    int m_echo_pin;
    bool m_echo_recieved = false;
    const char* m_id;

    int m_max_echo_time_us;

    // TODO: Protect this from concurrent use. Maybe a mutex-like variable?
    static Ultrasound* s_current_sensor;
};

} // namespace pico
} // namespace pet

#endif // PET_PICO_ULTRASOUND_H
