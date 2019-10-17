#include "interval.h"

AMIntervalRef AMIntervalInit(AMIntervalRef timer, AMTick interval) {
  timer->interval = interval;
  timer->tick = AMPlatformGetTicks();
  return timer;
}

bool AMIntervalTick(AMIntervalRef timer) {
  AMTick now = AMPlatformGetTicks();
  if(now - timer->tick > timer->interval) {
    timer->tick = now;
    return true;
  }
  return false;
}
