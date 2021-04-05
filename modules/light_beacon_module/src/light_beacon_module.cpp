#include "light_beacon_module.h"

#include <pet_mk_iv_msgs/LightBeacon.h>

#include "rosserial_node.h"
#include "timer.h"

namespace pet
{

const ros::Duration LightBeaconModule::kPeriod = ros::Duration{1.0/kFrequency};

const ros::Duration LightBeaconModule::kPressDuration = ros::Duration{0.05};

LightBeaconModule::LightBeaconModule(int servo_signal_pin, int servo_power_pin)
    : m_subscriber("beacon_mode", &LightBeaconModule::mode_msg_callback, this)
{
    // Power up the LED Beacon by setting servo_power_pin to High
    pinMode(servo_power_pin, OUTPUT);
    // NOTE: We hope these delays during construction does not affect the timing of the rest of the system to much.
    // TODO: Clean up delay for hardware power on sync.
    const auto press_duration_millis = static_cast<int>(press_duration().toSec() * 1000);

    digitalWrite(servo_power_pin, HIGH);
    delay(press_duration_millis);

    m_led_servo.attach(servo_signal_pin);
    m_led_servo.write(kServoOff);
    // Wait for hardware to power on and react
    delay(press_duration_millis);
    delay(press_duration_millis);

    nh.subscribe(m_subscriber);
}

ros::Time LightBeaconModule::callback(const TimerEvent& event)
{
    // TODO: Where to say that current mode is changed? On write(On) or write(Off)?
    // If servo is in 'On' state we always want to set it to 'Off', regardless of mode.
    if (m_current_position == kServoOn)
    {
        m_led_servo.write(kServoOff);
        m_current_position = kServoOff;
        return event.current_time + press_duration();
    }
    else if (m_current_mode != m_desired_mode)
    {
        m_led_servo.write(kServoOn);
        m_current_position = kServoOn;
        m_current_mode = (m_current_mode + 1) % 5;
        return event.current_time + press_duration();
    }
    else
    {
        return event.desired_time + LightBeaconModule::period();
    }
}

void LightBeaconModule::mode_msg_callback(const pet_mk_iv_msgs::LightBeacon& msg)
{
    nh.loginfo("Recieved new mode");
    m_desired_mode = msg.mode;
}

} // namespace pet
