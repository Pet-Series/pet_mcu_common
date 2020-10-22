#ifndef _PET_TIMER_H
#define _PET_TIMER_H

#include <stdint.h>

#include <ros/time.h>
#include <ros/duration.h>

#include "rosserial_node.h"
#include "arduino_module.h"

namespace pet
{

struct TimerEvent
{
    ros::Time desired_time;
    ros::Time current_time;
};

template<uint8_t capacity>
class Timer
{
private:
    struct Callback
    {
        ArduinoModule* module_ = nullptr;
        ros::Time next_desired_time_{};

        void call(const ros::Time& current_time)
        {
            next_desired_time_ = module_->callback(TimerEvent{next_desired_time_, current_time});
        }
    };

public:
    bool register_module(ArduinoModule* module)
    {
        if (m_size < capacity)
        {
            m_callbacks[m_size].module_ = module;
            ++m_size;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Sets start time on registered modules.
    void start()
    {
        const ros::Time current_time = nh.now();
        for (int i = 0; i < m_size; ++i)
        {
            auto& callback = m_callbacks[i];
            callback.next_desired_time_ = current_time;
        }
    }

    void spin_once()
    {
        for (int i = 0; i < m_size; ++i)
        {
            auto& callback = m_callbacks[i];
            const ros::Time current_time = nh.now();
            if (callback.next_desired_time_ < current_time)
            {
                callback.call(current_time);
            }
        }
    }

private:
    uint8_t m_size = 0;
    Callback m_callbacks[capacity];
};

} // namespace pet

#endif // _PET_TIMER_H
