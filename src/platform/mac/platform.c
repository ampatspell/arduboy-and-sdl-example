#ifdef PLATFORM_MAC

#include "platform.h"
#include "../../world/world.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

struct AMPlatform {
  uint8_t pixel;
  uint8_t width;
  uint8_t height;
  uint8_t padding;
  uint32_t interval;
  uint32_t next;
  SDL_Window *window;
  SDL_Renderer *renderer;
  uint8_t *buffer;
  AMWorldRef world;
};

struct AMPlatform __platform;

typedef struct {
  int width;
  int height;
} AMPlatformWindowSize;

AMPlatformWindowSize AMPlatformCalculateWindowSize(AMPlatformRef platform) {
  AMPlatformWindowSize size = {
    .width = (platform->width * platform->pixel) + (2 * platform->padding),
    .height = (platform->height * platform->pixel) + (2 * platform->padding)
  };
  return size;
}

void AMPlatformHandleSDLError(void) {
  const char *err = SDL_GetError();
  printf("AMPlatform SDL Error: %s", err);
  abort();
}

AMPlatformRef AMPlatformCreate() {
  AMPlatformRef platform = &__platform;
  
  platform->pixel = 3;
  platform->width = 128;
  platform->height = 64;
  platform->padding = 5;
  platform->interval = 30;
  platform->buffer = malloc((platform->width * platform->height) / 8);
  
  AMPlatformWindowSize size = AMPlatformCalculateWindowSize(platform);
  
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    AMPlatformHandleSDLError();
  }
  
  platform->window = SDL_CreateWindow("Thing",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      size.width,
                                      size.height,
                                      SDL_WINDOW_OPENGL);
  
  if(!platform->window) {
    AMPlatformHandleSDLError();
  }
  
  platform->renderer = SDL_CreateRenderer(platform->window, -1, SDL_RENDERER_ACCELERATED);
  
  if(!platform->renderer) {
    AMPlatformHandleSDLError();
  }
  
  platform->next = SDL_GetTicks() + platform->interval;
  
  return platform;
}

void AMPLatformSetPixel(AMPlatformRef platform, uint8_t pixel) {
  platform->pixel = pixel;
  AMPlatformWindowSize size = AMPlatformCalculateWindowSize(platform);
  SDL_SetWindowSize(platform->window, size.width, size.height);
}

void AMPlatformHandleKeyboardEvent(AMPlatformRef platform, SDL_Event event) {
  SDL_Keycode code = event.key.keysym.sym;
  uint8_t pixel;
  if(code == SDLK_1) {
    pixel = 1;
  } else if(code == SDLK_2) {
    pixel = 2;
  } else if(code == SDLK_3) {
    pixel = 3;
  } else if(code == SDLK_4) {
    pixel = 4;
  } else if(code == SDLK_5) {
    pixel = 5;
  } else if(code == SDLK_6) {
    pixel = 6;
  } else if(code == SDLK_7) {
    pixel = 7;
  } else if(code == SDLK_8) {
    pixel = 8;
  } else {
    return;
  }
  AMPLatformSetPixel(platform, pixel);
}

void AMPlatformDrawPixel(AMPlatformRef platform, uint8_t x, uint8_t y, bool white) {
  uint8_t padding = platform->padding;
  uint8_t pixel = platform->pixel;
  
  SDL_Rect rect = {
    .x = padding + (x * pixel),
    .y = padding + (y * pixel),
    .w = pixel,
    .h = pixel
  };
  
  uint8_t color;
  if(white) {
    color = 255;
  } else {
    color = 0;
  }
  
  SDL_SetRenderDrawColor(platform->renderer, color, color, color, 255);
  SDL_RenderFillRect(platform->renderer, &rect);
}

typedef enum {
  AMPlatformPollEventActionNone,
  AMPlatformPollEventActionQuit
} AMPlatformPollEventAction;

AMPlatformPollEventAction AMPlatformPollEvents(AMPlatformRef platform) {
  SDL_Event event;
  if(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      return AMPlatformPollEventActionQuit;
    } else if(event.type == SDL_KEYDOWN) {
      AMPlatformHandleKeyboardEvent(platform, event);
    }
  }
  return AMPlatformPollEventActionNone;
}

void AMPlatformDrawBackground(AMPlatformRef platform) {
  SDL_Renderer *renderer = platform->renderer;
  uint8_t padding = platform->padding;
  uint8_t pixel = platform->pixel;
  uint8_t width = platform->width;
  uint8_t height = platform->height;
  
  uint8_t background = 20;
  SDL_SetRenderDrawColor(renderer, background, background, background, 255);
  SDL_RenderClear(renderer);
  
  SDL_Rect stroke = {
    .x = padding - 1,
    .y = padding - 1,
    .w = width * pixel + 2,
    .h = height * pixel + 2
  };
  
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
  SDL_RenderDrawRect(renderer, &stroke);
  
  SDL_Rect fill = {
    .x = padding,
    .y = padding,
    .w = width * pixel,
    .h = height * pixel
  };
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, &fill);
}

void AMPlatformPresent(AMPlatformRef platform) {
  SDL_RenderPresent(platform->renderer);
}

uint32_t AMPlatformTimeLeft(AMPlatformRef platform) {
  Uint32 now = SDL_GetTicks();
  if(platform->next <= now) {
    return 0;
  }
  return platform->next - now;
}

void AMPlatformWait(AMPlatformRef platform) {
  SDL_Delay(AMPlatformTimeLeft(platform));
  platform->next += platform->interval;
}

#pragma mark -

int main(int argc, const char * argv[]) {
  AMPlatformRef platform = AMPlatformCreate();
  
  platform->world = AMWorldCreate(platform);
  AMWorldSetup(platform->world);
  
  while(1) {
    AMPlatformPollEventAction action = AMPlatformPollEvents(platform);
    if(action == AMPlatformPollEventActionQuit) {
      break;
    }
    
    AMPlatformDrawBackground(platform);
    
    AMWorldTick(platform->world);
    
    AMPlatformPresent(platform);
    AMPlatformWait(platform);
  }
  
  return 0;
}

#pragma mark -

void AMPlatformSetCursor(AMPlatformRef platform, uint8_t x, uint8_t y) {
}

void AMPlatformPrintString(AMPlatformRef platform, char *str) {
}

void AMPlatformDrawSpritePlusMask(AMPlatformRef platform, uint8_t _x, uint8_t _y, const unsigned char *ptr, uint8_t index) {
  uint8_t width = *ptr++;
  uint8_t height = *ptr++;
  
  size_t size = (width * height) / 4;
  ptr += (size * index);
  
  uint8_t pages = height / 8;
  for(uint8_t page = 0; page < pages; page++) {
    for(uint8_t x = 0; x < width; x++) {
      const unsigned char color = *ptr++;
      const unsigned char mask = *ptr++;
      for(uint8_t y = 0; y < 8; y++) {
        int white = color & (1 << y);
        int draw = mask & (1 << y);
        if(draw) {
          AMPlatformDrawPixel(platform, _x + x, _y + (page * 8) + y, !!white);
        }
      }
    }
  }
}

#endif
