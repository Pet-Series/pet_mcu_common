#include <stdint.h>

#include <ros/time.h>
#include <ros/duration.h>

#include "rosserial_node.h"
#include "modules.h"

#include "prgmem_string.h"

// Synchronises topic information and time stamp with the rosserial server.
void synchronise_with_server()
{
    pet::nh.negotiateTopics();

    uint32_t last_sync_time = pet::nh.get_last_sync_receive_time();
    pet::nh.requestSyncTime();
    while (last_sync_time == pet::nh.get_last_sync_receive_time())
    {
        pet::nh.spinOnce();
    }
}

void setup()
{
    pet::nh.initNode();

    while (!pet::nh.connected())
    {
        pet::nh.spinOnce();
    }

    pet::nh.loginfo(PET_PSTR("Arduino starting..."));

    auto result = pet::configure_modules();
    switch (result)
    {
    case pet::ConfigResult::Success:
        pet::nh.loginfo(PET_PSTR("Module setup done."));
        break;
    case pet::ConfigResult::AllocationError:
        pet::nh.logerror(PET_PSTR("AllocationError during module setup!"));
        break;
    case pet::ConfigResult::TimerRegistrationError:
        pet::nh.logerror(PET_PSTR("TimerRegistrationError during module setup!"));
        break;
    }

    // Ensure topic information is updated on server-side.
    synchronise_with_server();

    pet::g_timer.start();

    pet::nh.loginfo(PET_PSTR("Arduino setup done!"));
}

void loop()
{
    pet::nh.spinOnce();
    pet::g_timer.spin_once();
}
