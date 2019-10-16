#include "timer.h"

AMTimerRef AMTimerInit(AMTimerRef timer, AMTick interval, AMPlatformRef platform) {
  timer->platform = platform;
  timer->interval = interval;
  timer->tick = AMPlatformGetTicks(platform);
  return timer;
}

bool AMTimerTick(AMTimerRef timer) {
  AMTick now = AMPlatformGetTicks(timer->platform);
  if(now - timer->tick > timer->interval) {
    timer->tick = now;
    return true;
  }
  return false;
}
