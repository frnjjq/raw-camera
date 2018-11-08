#pragma once

#include <SDL2/SDL.h>
SDL_Window * window;
SDL_Renderer * renderer;
SDL_Texture * texture;

void init_player(int width, int height);
void play_frame(void* data, int width);
void handle_window();
void close_player();