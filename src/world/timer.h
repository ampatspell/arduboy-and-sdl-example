#pragma once

#include "../platform/platform.h"
#include <stdbool.h>

typedef struct {
  AMPlatformRef platform;
  AMTick tick;
  AMTick interval;
} AMTimer;

typedef AMTimer* AMTimerRef;

AMTimerRef AMTimerInit(AMTimerRef timer, AMTick interval, AMPlatformRef platform);
bool AMTimerTick(AMTimerRef timer);
