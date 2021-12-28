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

template<int kSensorCount>
class UltrasoundModule : public ArduinoModule
{
private:
    static constexpr double kFrequency = 30;
    static const ros::Duration kPeriod;
    static constexpr auto kTopicName = "dist_sensors";

public:
    UltrasoundModule(const int pins[kSensorCount], const char* const sensor_ids[kSensorCount]);

    ros::Time callback(const TimerEvent& event) override;

private:
    pet_mk_iv_msgs::DistanceMeasurement m_msg;
    ros::Publisher m_publisher;

    int m_current_sensor = 0;
    Ultrasound m_sensors[kSensorCount];
};

template<int kSensorCount>
const ros::Duration UltrasoundModule<kSensorCount>::kPeriod = ros::Duration{1.0/kFrequency};

template<int kSensorCount>
UltrasoundModule<kSensorCount>::UltrasoundModule(const int pins[kSensorCount], const char* const sensor_ids[kSensorCount])
    : m_msg()
    , m_publisher(kTopicName, &m_msg)
{
    for (int i = 0; i < kSensorCount; ++i) {
        m_sensors[i] = Ultrasound{pins[i], pins[i], sensor_ids[i]};
    }

    m_sensors[m_current_sensor].start_ping();
    pet::nh.advertise(m_publisher);
}

template<int kSensorCount>
ros::Time UltrasoundModule<kSensorCount>::callback(const TimerEvent& event)
{
    auto& current_sensor = m_sensors[m_current_sensor];

    current_sensor.stop_ping();

    m_msg.header.stamp    = pet::nh.now();
    m_msg.header.frame_id = current_sensor.frame_id();
    m_msg.distance        = current_sensor.get_distance();

    m_publisher.topic_ = current_sensor.topic();
    m_publisher.publish(&m_msg);

    m_current_sensor = (m_current_sensor + 1) % kSensorCount;
    m_sensors[m_current_sensor].start_ping();
    return event.desired_time + kPeriod;
}

} // namespace pet

#endif // PET_ULTRASOUND_MODULE_H
