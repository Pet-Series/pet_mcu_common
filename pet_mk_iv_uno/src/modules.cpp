#include "modules.h"

#include "timer.h"

#include "engine_module.h"
#include "line_sensor_module.h"
#include "ultrasound_module.h"

namespace pet
{

Timer<4> g_timer{};

ConfigResult configure_modules()
{
    pet::ArduinoModule* engine_module = new pet::EngineModule();
    if (!engine_module) {
        return ConfigResult::AllocationError;
    }
    if (!g_timer.register_module(engine_module)) {
        return ConfigResult::TimerRegistrationError;
    }

    pet::ArduinoModule* line_follower_module = new pet::LineSensorModule();
    if (!line_follower_module) {
        return ConfigResult::AllocationError;
    }
    if (!g_timer.register_module(line_follower_module)) {
        return ConfigResult::TimerRegistrationError;
    }

    pet::ArduinoModule* ultrasound_module = new pet::UltrasoundModule();
    if (!ultrasound_module) {
        return ConfigResult::AllocationError;
    }
    if (!g_timer.register_module(ultrasound_module)) {
        return ConfigResult::TimerRegistrationError;
    }

    return ConfigResult::Success;
}

} // namespace pet
