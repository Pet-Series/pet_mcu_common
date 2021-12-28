#include "ultrasound.h"

namespace pet
{

Ultrasound* Ultrasound::s_current_sensor = nullptr;

Ultrasound::Ultrasound(int triggerPin, int echoPin, const char* id)
    : m_sonar(triggerPin, echoPin, kMaxDistance)
    , m_id(id)
{
}

void Ultrasound::start_ping()
{
    m_echo_recieved = false;
    s_current_sensor = this;
    m_sonar.ping_timer(Ultrasound::interrupt_callback);
}

void Ultrasound::stop_ping()
{
    s_current_sensor = nullptr;
    m_sonar.timer_stop();
}

int Ultrasound::get_distance() const
{
    if (m_echo_recieved) {
        return m_sonar.ping_result * 10 / US_ROUNDTRIP_CM;
    } else {
        return -1;
    }
}

const char* Ultrasound::frame_id() const
{
    return m_id;
}

const char* Ultrasound::topic() const
{
    return m_id;
}

// Note: This function will be called inside an interrupt.
void Ultrasound::echo_check()
{
    m_echo_recieved = m_sonar.check_timer();
}

// Note: This function will be called inside an interrupt.
void Ultrasound::interrupt_callback()
{
    s_current_sensor->echo_check();
}

} // namespace pet
