#include "ultrasound_legacy.h"

namespace pet
{

UltrasoundLegacy* UltrasoundLegacy::s_current_sensor = nullptr;

UltrasoundLegacy::UltrasoundLegacy(int triggerPin, int echoPin, const char* frame_id)
    : m_sonar(triggerPin, echoPin, kMaxDistance)
    , m_frame_id(frame_id)
{
}

void UltrasoundLegacy::start_ping()
{
    m_echo_recieved = false;
    s_current_sensor = this;
    m_sonar.ping_timer(UltrasoundLegacy::interrupt_callback);
}

void UltrasoundLegacy::stop_ping()
{
    s_current_sensor = nullptr;
    m_sonar.timer_stop();
}

int UltrasoundLegacy::get_distance() const
{
    if (m_echo_recieved) {
        return m_sonar.ping_result * 10 / US_ROUNDTRIP_CM;
    } else {
        return -1;
    }
}

const char* UltrasoundLegacy::frame_id() const
{
    return m_frame_id;
}

// Note: This function will be called inside an interrupt.
void UltrasoundLegacy::echo_check()
{
    m_echo_recieved = m_sonar.check_timer();
}

// Note: This function will be called inside an interrupt.
void UltrasoundLegacy::interrupt_callback()
{
    s_current_sensor->echo_check();
}

} // namespace pet
