#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>

typedef struct AMPlatform *AMPlatformRef;

typedef uint32_t AMTick;

#ifdef __cplusplus
extern "C" {
#endif

void AMPlatformDrawSpritePlusMask(uint8_t x, uint8_t y, const unsigned char *ptr, uint8_t index);

AMTick AMPlatformGetTicks();

#ifdef __cplusplus
}
#endif
