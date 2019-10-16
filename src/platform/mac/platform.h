#define PROGMEM

#include <stdint.h>

typedef struct AMPlatform *AMPlatformRef;

void AMPlatformDrawSpritePlusMask(AMPlatformRef platform, uint8_t x, uint8_t y, const unsigned char *ptr, uint8_t index);
