#ifndef PET_LIGHT_BEACON_MODULE_H
#define PET_LIGHT_BEACON_MODULE_H

#include <Servo.h>

#include <ros/duration.h>

#include <pet_mk_iv_msgs/LightBeacon.h>

#include "arduino_module.h"
#include "timer.h"

namespace pet
{

class LightBeaconModule : public ArduinoModule
{
private:
    static constexpr double kFrequency = 50;
    static const ros::Duration kPeriod;

    // How long we have to wait for virtual servo to realise we have changed its position.
    static const ros::Duration kPressDuration;

    // Fake 'On' position for the virtual servo. Specified in degrees.
    static constexpr int kServoOn  = 45;
    // Fake 'Off' position for the virtual servo. Specified in degrees.
    static constexpr int kServoOff = 135;

public:
    /// @param servo_signal_pin orange wire
    /// @param servo_power_pin red wire
    LightBeaconModule(int servo_signal_pin, int servo_power_pin);

    ros::Time callback(const TimerEvent& event) override;

private:
    void mode_msg_callback(const pet_mk_iv_msgs::LightBeacon& msg);

    static ros::Duration period() { return kPeriod; }

    static ros::Duration press_duration() { return kPressDuration; }

private:
    Servo m_led_servo{};

    // NOTE: Hardware initialises to ROTATING_FAST mode when powered on.
    int m_current_mode = pet_mk_iv_msgs::LightBeacon::ROTATING_FAST;
    int m_desired_mode = pet_mk_iv_msgs::LightBeacon::OFF;

    int m_current_position = kServoOff;

    ros::Subscriber<pet_mk_iv_msgs::LightBeacon, LightBeaconModule> m_subscriber;
};

} // namespace pet

#endif // PET_LIGHT_BEACON_MODULE_H
