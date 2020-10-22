#ifndef PET_PRGMEM_STRING_H
#define PET_PRGMEM_STRING_H

#define PET_PSTR(s) pet::prgmem_string(PSTR(s))

namespace pet
{

// Retrives a c-string from program memory and returns a usable c-string.
// Usage: prgmem_string(PSTR("My constant string"))
char* prgmem_string(const char* toBuffer);

} // namespace pet

#endif // PET_PRGMEM_STRING_H