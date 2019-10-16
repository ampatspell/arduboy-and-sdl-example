#pragma once

#include "../platform/platform.h"
#include <stdbool.h>

typedef struct {
  AMTick tick;
  AMTick interval;
} AMTimer;

typedef AMTimer* AMTimerRef;

AMTimerRef AMTimerInit(AMTimerRef timer, AMTick interval);
bool AMTimerTick(AMTimerRef timer);
