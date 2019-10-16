#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>

typedef struct AMPlatform *AMPlatformRef;

#ifdef __cplusplus
extern "C" {
#endif

void AMPlatformDrawSpritePlusMask(AMPlatformRef platform, uint8_t x, uint8_t y, const unsigned char *ptr, uint8_t index);

#ifdef __cplusplus
}
#endif
