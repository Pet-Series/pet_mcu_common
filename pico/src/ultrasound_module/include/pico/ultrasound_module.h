#pragma once

#include <ros/time.h>
#include <ros/duration.h>

#include <sensor_msgs/Range.h>

#include "arduino_module.h"
#include "timer.h"

#include "ultrasound.h"

namespace pet
{

constexpr float deg2rad(float degrees)
{
    return degrees * M_PI / 180.0f;
}

class DefaultConstructablePublisher : public ros::Publisher
{
public:
    DefaultConstructablePublisher() : Publisher("dummy_topic", nullptr) {}

    using Publisher::Publisher;
};

template<int kSensorCount>
class UltrasoundModule : public ArduinoModule
{
private:
    static constexpr double kFrequency = 30;
    static const ros::Duration kPeriod;

public:
    UltrasoundModule(const int pins[kSensorCount], const char* const sensor_ids[kSensorCount]);

    ros::Time callback(const TimerEvent& event) override;

private:
    sensor_msgs::Range m_msg{};
    DefaultConstructablePublisher m_publishers[kSensorCount];

    int m_current_sensor = 0;
    Ultrasound m_sensors[kSensorCount];
};

template<int kSensorCount>
const ros::Duration UltrasoundModule<kSensorCount>::kPeriod = ros::Duration{1.0/kFrequency};

template<int kSensorCount>
UltrasoundModule<kSensorCount>::UltrasoundModule(const int pins[kSensorCount], 
                                                 const char* const sensor_ids[kSensorCount])
{
    m_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
    m_msg.field_of_view  = deg2rad(50);
    m_msg.min_range      = Ultrasound::kMinDistance_cm / 100.0f;
    m_msg.max_range      = Ultrasound::kMaxDistance_cm / 100.0f;

    for (int i = 0; i < kSensorCount; ++i) {
        m_sensors[i]    = Ultrasound{pins[i], pins[i], sensor_ids[i]};
        m_publishers[i] = DefaultConstructablePublisher{m_sensors[i].topic(), &m_msg};
        pet::nh.advertise(m_publishers[i]);
    }

    m_sensors[m_current_sensor].start_ping();
}

template<int kSensorCount>
ros::Time UltrasoundModule<kSensorCount>::callback(const TimerEvent& event)
{
    auto& current_sensor = m_sensors[m_current_sensor];

    current_sensor.stop_ping();

    m_msg.header.stamp    = pet::nh.now();
    m_msg.header.frame_id = current_sensor.frame_id();
    m_msg.range           = current_sensor.get_distance();

    m_publishers[m_current_sensor].publish(&m_msg);

    m_current_sensor = (m_current_sensor + 1) % kSensorCount;
    m_sensors[m_current_sensor].start_ping();
    return event.desired_time + kPeriod;
}

} // namespace pet
