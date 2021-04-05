#ifndef PET_ULTRASOUND_H
#define PET_ULTRASOUND_H

#include <NewPing.h>

namespace pet
{

class Ultrasound
{
public:
    static constexpr int kMaxDistance = 400;  // [cm] Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

public:
    Ultrasound() : Ultrasound(-1, -1, "") {}
    Ultrasound(int triggerPin, int echoPin, const char* frame_id);

    void start_ping();
    void stop_ping();

    int get_distance() const;

    const char* frame_id() const;

private:
    void echo_check();

    static void interrupt_callback();

private:
    NewPing m_sonar;
    bool m_echo_recieved = false;
    const char* m_frame_id;

    // TODO: Protect this from concurrent use. Maybe a mutex-like variable?
    static Ultrasound* s_current_sensor;
};

} // namespace pet

#endif // PET_ULTRASOUND_H
