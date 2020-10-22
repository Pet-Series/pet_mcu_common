#include "prgmem_string.h"

#include <avr/pgmspace.h>

namespace pet
{

// make sure this is large enough for the largest string it must hold
static char buffer[60];

char* prgmem_string(const char* toBuffer)
{
    strcpy_P(buffer, toBuffer);
    return buffer;
}

} // namespace pet
