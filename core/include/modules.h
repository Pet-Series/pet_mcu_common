#ifndef PET_MODULES_H
#define PET_MODULES_H

#include "timer.h"

namespace pet
{

/// Maximum number of modules we support. Current maximum on vehicle: 1 Engine + 1 UltraSound + 3 LineSensor = 5 on Pet-Mk-IV Uno.
constexpr int kMaxNumModules = 5;

extern Timer<kMaxNumModules> g_timer;

enum class ConfigResult
{
    Success,
    AllocationError,
    TimerRegistrationError,
};

ConfigResult configure_modules();

} // namespace pet

#endif // PET_MODULES_H
