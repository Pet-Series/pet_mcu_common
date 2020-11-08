#include "ir_remote_module.h"
#include <IRremote.h>                // Include IR Remote (Library by Ken Shirriff)
#include "ir_remote_decode_map.h"    // Mapping of key-codes for the IR remote
#include <Arduino.h>

#include <ros/time.h>

#include "rosserial_node.h"
#include "timer.h"

namespace pet
{

using pet_mk_iv_msgs::IrRemote;

IrRemoteModule::IrRemoteModule()
    : m_msg()
    , m_publisher(kTopicName, &m_msg)
{
    nh.advertise(m_publisher);
    m_irrecv.enableIRIn();      // Enable the IR Receiver (see kRecvPin value for IR-receiver pin)
    m_msg.key = IrRemote::NOTSET;
}

ros::Time IrRemoteModule::callback(const TimerEvent& event)
{
    if (m_irrecv.decode(&m_decode_results))
    {
        nh.loginfo("IR remote signal received - Tjoho!");     // TODO: Te be removed
        nh.loginfo(String(m_decode_results.value).c_str());   // TODO: Te be removed

        switch (m_decode_results.value)
        {
            case IR_RC6_OnOff_t1:
            case IR_RC6_OnOff_t2:
                m_msg.key = IrRemote::ON;
                // TODO: m_msg.key = IrRemote::OFF;
                break;
            // ****** Color keys 
            // TODO: RED / GREEN / YELLOW / BLUE
            // ****** Arrow & Navigation keys
            case IR_RC6_Ok_t1:
            case IR_RC6_Ok_t2:
                m_msg.key = IrRemote::OK;
                break;
            case IR_RC6_Up_t1:
            case IR_RC6_Up_t2:
                m_msg.key = IrRemote::UP;
                break;
            case IR_RC6_Down_t1:
            case IR_RC6_Down_t2:
                m_msg.key = IrRemote::DOWN;
                break;
            case IR_RC6_Left_t1:
            case IR_RC6_Left_t2:
                m_msg.key = IrRemote::LEFT;
                break;
            case IR_RC6_Right_t1:
            case IR_RC6_Right_t2:
                m_msg.key = IrRemote::RIGHT;
                break;
            case IR_RC6_Menu_t1:
            case IR_RC6_Menu_t2:
                m_msg.key = IrRemote::MENU;
                break;
            case IR_RC6_Info_t1:
            case IR_RC6_Info_t2:
                m_msg.key = IrRemote::INFO;
                break;
            case IR_RC6_Back_t1:
            case IR_RC6_Back_t2:
                m_msg.key = IrRemote::BACK;
                break;
            // ****** Multimedia keys
            case IR_RC6_Play_t1:
            case IR_RC6_Play_t2:
                m_msg.key = IrRemote::PLAY;
                break;
            case IR_RC6_Stop_t1:
            case IR_RC6_Stop_t2:
                m_msg.key = IrRemote::STOP;
                break;
            case IR_RC6_Pause_t1:
            case IR_RC6_Pause_t2:
                m_msg.key = IrRemote::PAUSE;
                break;
            case IR_RC6_FFwd_t1:
            case IR_RC6_FFwd_t2:
                m_msg.key = IrRemote::FAST_FWD;
                break;
            case IR_RC6_Rewind_t1:
            case IR_RC6_Rewind_t2:
                m_msg.key = IrRemote::REWIND;
                break;
            case IR_RC6_Mute_t1:
            case IR_RC6_Mute_t2:
                m_msg.key = IrRemote::MUTE;
                break;
            case IR_RC6_Win_t1:
            case IR_RC6_Win_t2:
                m_msg.key = IrRemote::WINDOWS;
                break;
            case IR_RC6_VolPlus_t1:
            case IR_RC6_VolPlus_t2:
                m_msg.key = IrRemote::VOL_PLUS;
                break;
            case IR_RC6_VolMinus_t1:
            case IR_RC6_VolMinus_t2:
                m_msg.key = IrRemote::VOL_MINUS;
                break;
            // TODO: IR_RC6_ChPlus  CH_PLUS
            // TODO: IR_RC6_ChMinus CH_MINUS
            // TODO: IR_RC6_Eject   EJECT
            // TODO: IR_RC6_Record  RECORD
            // ****** Numeric keys
            case IR_RC6_0_t1:
            case IR_RC6_0_t2:
                m_msg.key = IrRemote::NUM_0;
                break;
            case IR_RC6_1_t1:
            case IR_RC6_1_t2:
                m_msg.key = IrRemote::NUM_1;
                break;
            case IR_RC6_2_t1:
            case IR_RC6_2_t2:
                m_msg.key = IrRemote::NUM_2;
                break;
            case IR_RC6_3_t1:
            case IR_RC6_3_t2:
                m_msg.key = IrRemote::NUM_3;
                break;
            case IR_RC6_4_t1:
            case IR_RC6_4_t2:
                m_msg.key = IrRemote::NUM_4;
                break;              
            case IR_RC6_5_t1:
            case IR_RC6_5_t2:
                m_msg.key = IrRemote::NUM_5;
                break;
            case IR_RC6_6_t1:
            case IR_RC6_6_t2:
                m_msg.key = IrRemote::NUM_6;
                break;
            case IR_RC6_7_t1:
            case IR_RC6_7_t2:
                m_msg.key = IrRemote::NUM_7;
                break;
            case IR_RC6_8_t1:
            case IR_RC6_8_t2:
                m_msg.key = IrRemote::NUM_8;
                break;             
            case IR_RC6_9_t1:
            case IR_RC6_9_t2:
                 m_msg.key = IrRemote::NUM_9;
                break;
            case IR_RC6_Enter_t1:
            case IR_RC6_Enter_t2:
                 m_msg.key = IrRemote::NUM_ENTER;
                 break;
            case IR_RC6_Clear_t1:
            case IR_RC6_Clear_t2:
                 m_msg.key = IrRemote::NUM_CLEAR;
                break;
            // TODO: IR_RC6_Star    NUM_STAR
            // TODO: IR_RC6_Hash    NUM_HASH
            // ****** Unknown key is detected
            default:
                m_msg.key = IrRemote::UNKNOWN;

        }
        
        if (m_msg.key != IrRemote::UNKNOWN)
        {
            m_publisher.publish(&m_msg);
        }
        m_irrecv.resume();
    }

    return event.desired_time + kPeriod;  // Calculate next time this module wants to be called again
}

} // namespace pet
