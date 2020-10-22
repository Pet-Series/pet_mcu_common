#ifndef PET_MODULES_H
#define PET_MODULES_H

#include "timer.h"

namespace pet
{

extern Timer<4> g_timer;

enum class ConfigResult
{
    Success,
    AllocationError,
    TimerRegistrationError,
};

ConfigResult configure_modules();

} // namespace pet

#endif // PET_MODULES_H
