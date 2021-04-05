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

class IrRemoteModule : public ArduinoModule
{
private:
    static constexpr double kFrequency = 10;   // Hz
    static const ros::Duration kPeriod;

    static constexpr auto   kTopicName = "ir_remote";

public:
    IrRemoteModule(int receiver_pin);

    ros::Time callback(const TimerEvent& event) override;

private:
    pet_mk_iv_msgs::IrRemote m_msg;
    ros::Publisher m_publisher;
    
    IRrecv m_irreceiver;
};

} // namespace pet

#endif // _PET_IRREMOTE_H