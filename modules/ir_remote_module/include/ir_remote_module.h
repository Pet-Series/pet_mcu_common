#ifndef _PET_IRREMOTE_H
#define _PET_IRREMOTE_H

#include <ros/time.h>
#include <ros/duration.h>
#include <IRremote.h>                // Include IR Remote (Library by Ken Shirriff)
#include "ir_remote_decode_map.h"    // Mapping of key-codes for the IR remote
#include <pet_mk_iv_msgs/IrRemote.h>

#include "rosserial_node.h"
#include "arduino_module.h"
#include "timer.h"

namespace pet
{

// Handler class for three ground pointing light sensors arranged in a left-middle-right pattern.
class IrRemoteModule : public ArduinoModule
{
private:
    static constexpr double kFrequency = 10;   // Hz
    static constexpr auto   kPeriod = ros::Duration{1.0/kFrequency};

    static constexpr int    kRecvPin   = 11; // IR-receiver Arduino Nano pin
    static constexpr auto   kTopicName = "ir_remote";

public:
    IrRemoteModule();

    ros::Time callback(const TimerEvent& event) override;

private:
    pet_mk_iv_msgs::IrRemote m_msg;
    ros::Publisher m_publisher;
    
    IRrecv m_irrecv{kRecvPin}; // IRrecv från <IRremote.h>
    decode_results m_decode_results;
};

} // namespace pet

#endif // _PET_IRREMOTE_H