#pragma once

#include "../platform/platform.h"

typedef struct AMWorld *AMWorldRef;

AMWorldRef AMWorldCreate(AMPlatformRef platform);

void AMWorldSetup(AMWorldRef world);
void AMWorldTick(AMWorldRef world);
