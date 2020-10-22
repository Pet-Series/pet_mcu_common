#ifndef PET_ULTRASOUND_MODULE_H
#define PET_ULTRASOUND_MODULE_H

#include <ros/time.h>
#include <ros/duration.h>

#include <pet_mk_iv_msgs/DistanceMeasurement.h>

#include "arduino_module.h"
#include "timer.h"

#include "ultrasound.h"

namespace pet
{

class UltrasoundModule : public ArduinoModule
{
private:
    static constexpr double kFrequency = 30;
    static constexpr auto   kPeriod = ros::Duration{1.0/kFrequency};
    static constexpr auto   kTopicName = "dist_sensors";

    static constexpr int kSensorCount = 3;

    static constexpr int kTriggerPinRight  = 14;   // A0  "Right"
    static constexpr int kEchoPinRight     = 14;   // A0  "Right"
    static constexpr int kTriggerPinMid    = 15;   // A1  "Middle"
    static constexpr int kEchoPinMid       = 15;   // A1  "Middle"
    static constexpr int kTriggerPinLeft   = 16;   // A2  "Left"
    static constexpr int kEchoPinLeft      = 16;   // A2  "Left"

public:
    UltrasoundModule();

    ros::Time callback(const TimerEvent& event) override;

private:
    pet_mk_iv_msgs::DistanceMeasurement m_msg;
    ros::Publisher m_publisher;

    int m_current_sensor = 0;
    Ultrasound m_sensors[kSensorCount] = {
        Ultrasound(kTriggerPinRight, kEchoPinRight, "dist_sensor_right"),
        Ultrasound(kTriggerPinMid, kEchoPinMid, "dist_sensor_mid"),
        Ultrasound(kTriggerPinLeft, kEchoPinLeft, "dist_sensor_left")
    };
};

} // namespace pet

#endif // PET_ULTRASOUND_MODULE_H
