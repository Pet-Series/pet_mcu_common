#ifndef _PET_ARDUINO_MODULE_H
#define _PET_ARDUINO_MODULE_H

#include <ros/time.h>

namespace pet
{

struct TimerEvent;

// Abstract base class for Arduino software modules.
class ArduinoModule
{
public:
    // Allows the module to do stuff. Returns the next time the module desires to be called.
    virtual ros::Time callback(const TimerEvent& event) = 0;
};

} // namespace pet

#endif // _PET_ARDUINO_MODULE_H