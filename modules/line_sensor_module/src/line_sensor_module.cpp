#include "line_sensor_module.h"

#include <Arduino.h>

#include <ros/time.h>

#include "rosserial_node.h"
#include "timer.h"

namespace pet
{

LineSensorModule::LineSensorModule()
    : m_msg()
    , m_publisher(kTopicName, &m_msg)
{
    pinMode(kLeftPin, INPUT);
    pinMode(kMiddlePin, INPUT);
    pinMode(kRightPin, INPUT);

    // TODO: Replace "line_followers" with something like "line_sensors"
    m_msg.header.frame_id = "line_followers";
    nh.advertise(m_publisher);
}

ros::Time LineSensorModule::callback(const TimerEvent& event)
{
    m_msg.left = digitalRead(kLeftPin);
    m_msg.middle = digitalRead(kMiddlePin);
    m_msg.right = digitalRead(kRightPin);
    m_msg.header.stamp = event.current_time;
    m_publisher.publish(&m_msg);
    return event.desired_time + kPeriod;    // Calculate next time this module wants to be called again
}

} // namespace pet
