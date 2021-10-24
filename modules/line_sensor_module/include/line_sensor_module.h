#ifndef _PET_LINESENSORMODULE_H
#define _PET_LINESENSORMODULE_H

#include <ros/time.h>
#include <ros/duration.h>

#include <pet_mk_iv_msgs/LineDetection.h>

#include "rosserial_node.h"
#include "arduino_module.h"
#include "timer.h"

namespace pet
{

class Pin
{
public:
    constexpr Pin(int pin_number) 
        : m_value{pin_number} 
    {};

    constexpr int value() const
    {
        return m_value;
    }

private:
    int m_value;
};


class LineSensorModule : public ArduinoModule
{
private:
    static constexpr double kFrequency = 100;
    static const ros::Duration kPeriod;

public:
    LineSensorModule(const Pin& pin, const char* topic);

    ros::Time callback(const TimerEvent& event) override;

private:
    int m_pin;
    pet_mk_iv_msgs::LineDetection m_msg;
    ros::Publisher m_publisher;
};

} // namespace pet

#endif // _PET_LINESENSORMODULE_H