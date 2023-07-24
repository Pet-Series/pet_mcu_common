#include "ultrasound.h"

namespace pet
{
namespace pico
{

namespace
{

constexpr float centimeter_to_meter(float centimeter)
{
    return centimeter / 100.0f;
}

}

Ultrasound* Ultrasound::s_current_sensor = nullptr;

Ultrasound::Ultrasound(int triggerPin, int echoPin, const char* id)
    : m_sonar(triggerPin, echoPin, kMaxDistance_cm)
    , m_id(id)
{
}

void Ultrasound::start_ping()
{
    m_echo_recieved = false;
    s_current_sensor = this;
    if (!m_sonar.ping_trigger()) // Trigger a ping, if it returns false, return without starting the echo timer.
    {
        return;
    }
    m_sonar.timer_us(ECHO_TIMER_FREQ, Ultrasound::interrupt_callback); // Set ping echo timer check every ECHO_TIMER_FREQ uS.
}

void Ultrasound::stop_ping()
{
    s_current_sensor = nullptr;
    m_sonar.timer_stop();
}

float Ultrasound::get_distance() const
{
    if (m_echo_recieved) {
        return centimeter_to_meter(m_sonar.ping_result / static_cast<float>(US_ROUNDTRIP_CM));
    } else {
        return -1.0f;
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

} // namespace pico
} // namespace pet
