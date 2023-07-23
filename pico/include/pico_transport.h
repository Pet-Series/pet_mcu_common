#ifndef _PET_MCU_COMMON_PICO_PICO_TRANSPORT
#define _PET_MCU_COMMON_PICO_PICO_TRANSPORT

#include <stdio.h>
#include <stdint.h>

#include <uxr/client/profile/transport/custom/custom_transport.h>

bool pico_serial_transport_open(struct uxrCustomTransport * transport);
bool pico_serial_transport_close(struct uxrCustomTransport * transport);
size_t pico_serial_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
size_t pico_serial_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);

#endif //_PET_MCU_COMMON_PICO_PICO_TRANSPORT