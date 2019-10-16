#include "timer.h"

AMTimerRef AMTimerInit(AMTimerRef timer, AMTick interval) {
  timer->interval = interval;
  timer->tick = AMPlatformGetTicks();
  return timer;
}

bool AMTimerTick(AMTimerRef timer) {
  AMTick now = AMPlatformGetTicks();
  if(now - timer->tick > timer->interval) {
    timer->tick = now;
    return true;
  }
  return false;
}
