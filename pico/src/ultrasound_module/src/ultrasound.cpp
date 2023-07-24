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
    if (!ping_trigger()) // Trigger a ping, if it returns false, return without starting the echo timer.
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

bool Ultrasound::ping_trigger()
{
	if (m_sonar._one_pin_mode)
    {
        pinMode(_triggerPin, OUTPUT);  // Set trigger pin to output.
    }

	digitalWrite(m_sonar._triggerPin, HIGH);  // Set trigger pin high, this tells the sensor to send out a ping.
	delayMicroseconds(TRIGGER_WIDTH); // Wait long enough for the sensor to realize the trigger pin is high.
	digitalWrite(m_sonar._triggerPin, LOW);   // Set trigger pin back to low.

	if (m_sonar._one_pin_mode)
    {
        pinMode(m_sonar._triggerPin, INPUT); // Set trigger pin to input (this is technically setting the echo pin to input as both are tied to the same pin).
    }

    if (digitalRead(m_sonar._echoPin))
    {
        return false;                // Previous ping hasn't finished, abort.
    }

    // Maximum time we'll wait for ping to start (most sensors are <450uS, the SRF06 can take up to 34,300uS!)
    m_sonar._max_time = micros() + m_sonar._maxEchoTime + MAX_SENSOR_DELAY;
    while (!digitalRead(m_sonar._echoPin))               // Wait for ping to start.
    {
        if (micros() > m_sonar._max_time)
        {
            return false;                                // Took too long to start, abort.
        }
    }

	m_sonar._max_time = micros() + m_sonar._maxEchoTime; // Ping started, set the time-out.
	return true;                                         // Ping started successfully.
}

} // namespace pico
} // namespace pet
