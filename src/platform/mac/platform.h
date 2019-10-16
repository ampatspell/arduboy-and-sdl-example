#pragma once

#include <stdint.h>

#define PROGMEM

typedef struct AMPlatform *AMPlatformRef;

void AMPlatformDrawSpritePlusMask(AMPlatformRef platform, uint8_t x, uint8_t y, const unsigned char *ptr, uint8_t index);

typedef uint32_t AMTick;

AMTick AMPlatformGetTicks(AMPlatformRef platform);
