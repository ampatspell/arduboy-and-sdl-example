#include "platform.h"

extern "C" {
#include "../../world/world.h"
}

#include <Arduino.h>
#include <Arduboy2.h>
#include <Sprites.h>

Arduboy2 arduboy;

struct AMPlatform {
  AMWorldRef world;
};

struct AMPlatform __platform;
AMPlatformRef platform;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(24);

  platform = &__platform;

  platform->world = AMWorldCreate(platform);
  AMWorldSetup(platform->world);
}

void loop() {
  if(!arduboy.nextFrame()) {
    return;
  }
  AMWorldTick(platform->world);
  arduboy.display(true);
}

//

void AMPlatformSetCursor(AMPlatformRef platform, uint8_t x, uint8_t y) {
  arduboy.setCursor(x, y);
}

void AMPlatformPrintString(AMPlatformRef platform, char *str) {
  arduboy.print(str);
}

void AMPlatformDrawSpritePlusMask(AMPlatformRef platform, uint8_t x, uint8_t y, const unsigned char *ptr, uint8_t index) {
  Sprites::drawPlusMask(x, y, ptr, index);
}