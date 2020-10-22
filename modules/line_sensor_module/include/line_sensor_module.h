#ifndef _PET_LINESENSORMODULE_H
#define _PET_LINESENSORMODULE_H

#include <ros/time.h>
#include <ros/duration.h>

#include <pet_mk_iv_msgs/TripleBoolean.h>

#include "rosserial_node.h"
#include "arduino_module.h"
#include "timer.h"

namespace pet
{

// Handler class for three ground pointing light sensors arranged in a left-middle-right pattern.
class LineSensorModule : public ArduinoModule
{
private:
    static constexpr double kFrequency = 100;
    static constexpr auto   kPeriod = ros::Duration{1.0/kFrequency};

    static constexpr int    kLeftPin   = 2;
    static constexpr int    kMiddlePin = 3;
    static constexpr int    kRightPin  = 4;
    // TODO: Change topic name from "line_followers" to something like "line_sensors"...
    static constexpr auto   kTopicName = "line_followers";

public:
    LineSensorModule();

    ros::Time callback(const TimerEvent& event) override;

private:
    pet_mk_iv_msgs::TripleBoolean m_msg;
    ros::Publisher m_publisher;
};

} // namespace pet

#endif // _PET_LINESENSORMODULE_H