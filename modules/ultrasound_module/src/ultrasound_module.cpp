#include "ultrasound_module.h"

#include <NewPing.h>

#include "rosserial_node.h"
#include "timer.h"

namespace pet
{

UltrasoundModule::UltrasoundModule()
    : m_msg()
    , m_publisher(kTopicName, &m_msg)
{
    m_sensors[m_current_sensor].start_ping();
    pet::nh.advertise(m_publisher);
}

ros::Time UltrasoundModule::callback(const TimerEvent& event)
{
    m_sensors[m_current_sensor].stop_ping();

    m_msg.header.stamp = pet::nh.now();
    m_msg.header.frame_id = m_sensors[m_current_sensor].frame_id();
    m_msg.distance = m_sensors[m_current_sensor].get_distance();
    m_publisher.publish(&m_msg);

    m_current_sensor = (m_current_sensor + 1) % kSensorCount;
    m_sensors[m_current_sensor].start_ping();
    return event.desired_time + kPeriod;
}

} // namespace pet
