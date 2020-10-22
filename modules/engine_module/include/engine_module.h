#ifndef PET_ENGINE_MODULE_H
#define PET_ENGINE_MODULE_H

#include <ros/time.h>
#include <ros/duration.h>

#include <pet_mk_iv_msgs/EngineCommand.h>

#include "rosserial_node.h"
#include "arduino_module.h"
#include "timer.h"

namespace pet
{

class EngineModule : public ArduinoModule
{
private:
    static constexpr double kFrequency = 100;
    static constexpr auto   kPeriod = ros::Duration{1.0/kFrequency};
    static constexpr auto   kTimeout = ros::Duration{0.5};

    static constexpr int kLeftReversePin  = 7;
    static constexpr int kLeftForwardPin  = 8;
    static constexpr int kLeftSpeedPin    = 9;
    static constexpr int kRightSpeedPin   = 10;
    static constexpr int kRightForwardPin = 11;
    static constexpr int kRightReversePin = 12;

public:
    EngineModule();

    ros::Time callback(const TimerEvent& event) override;

    static constexpr ros::Duration period() { return kPeriod; }

    static constexpr ros::Duration timeout() { return kTimeout; }

private:
    void cmd_msg_callback(const pet_mk_iv_msgs::EngineCommand& msg)
    {
        m_cmd_msg = msg;
    }

    // Stops all movement by setting current PWM values to 0.
    void stop();

    // Sets engine PWM values according to a command message.
    void set_engine_pwm(const pet_mk_iv_msgs::EngineCommand& cmd);

private:
    pet_mk_iv_msgs::EngineCommand m_cmd_msg;
    ros::Subscriber<pet_mk_iv_msgs::EngineCommand, EngineModule> m_subscriber;
};

} // namespace pet

#endif // PET_ENGINE_MODULE_H