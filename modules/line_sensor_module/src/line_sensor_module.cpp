#include "line_sensor_module.h"

#include <Arduino.h>

#include <ros/time.h>

#include <pet_mk_iv_msgs/LineDetection.h>

#include "rosserial_node.h"
#include "timer.h"

namespace pet
{

const ros::Duration LineSensorModule::kPeriod = ros::Duration{1.0/kFrequency};

LineSensorModule::LineSensorModule(const Pin& pin, const char* topic)
    : m_pin(pin.value())
    , m_msg()
    , m_publisher(topic, &m_msg)
{
    pinMode(pin.value(), INPUT);
    nh.advertise(m_publisher);
}

ros::Time LineSensorModule::callback(const TimerEvent& event)
{
    switch (digitalRead(m_pin))
    {
    case 0:
        m_msg.value = pet_mk_iv_msgs::LineDetection::DARK;
        break;
    case 1:
        m_msg.value = pet_mk_iv_msgs::LineDetection::LIGHT;
        break;
    }

    m_msg.header.stamp = event.current_time;
    m_publisher.publish(&m_msg);
    return event.desired_time + kPeriod;    // Calculate next time this module wants to be called again
}

} // namespace pet
