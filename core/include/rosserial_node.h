#ifndef _PET_ROSSERIAL_NODE_H_
#define _PET_ROSSERIAL_NODE_H_

#include <ros/node_handle.h>
#include <ArduinoHardware.h>

namespace pet
{

using NodeHandle = ::ros::NodeHandle_<ArduinoHardware, 8, 8, 128, 128>;

// Use nh as a global variable since it would be messy to send it everywhere.
extern NodeHandle nh;

} // namespace pet

#endif // _PET_ROSSERIAL_NODE_H_
