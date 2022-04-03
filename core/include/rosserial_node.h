#ifndef _PET_ROSSERIAL_NODE_H_
#define _PET_ROSSERIAL_NODE_H_

#include <ros/node_handle.h>
#include <ArduinoHardware.h>

namespace pet
{

constexpr int kMaxSubscribers   = 8;
constexpr int kMaxPublishers    = 8;
constexpr int kInputBufferSize  = 128;
constexpr int kOutputBufferSize = 128;

using NodeHandle = ::ros::NodeHandle_<ArduinoHardware,
                                      kMaxSubscribers,
                                      kMaxPublishers,
                                      kInputBufferSize,
                                      kOutputBufferSize>;

// Use nh as a global variable since it would be messy to send it everywhere.
extern NodeHandle nh;

} // namespace pet

#endif // _PET_ROSSERIAL_NODE_H_
