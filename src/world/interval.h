#pragma once

#include "../platform/platform.h"
#include <stdbool.h>

typedef struct {
  AMTick tick;
  AMTick interval;
} AMInterval;

typedef AMInterval* AMIntervalRef;

AMIntervalRef AMIntervalInit(AMIntervalRef timer, AMTick interval);
bool AMIntervalTick(AMIntervalRef timer);
