#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#include"player.h"

void init_player(int width, int height) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return;
	}
	window = SDL_CreateWindow("LHE Rpi Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (window == NULL) {

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window SDL: %s", SDL_GetError());
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer SDL: %s", SDL_GetError());
		return;
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderPresent(renderer);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, width, height);
	return;
}


void play_frame(void* data, int width)
{
	int status;
	status = SDL_UpdateTexture(texture, NULL, data, width);
	if (status != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't update texture SDL: %s", SDL_GetError());
	}
	status = SDL_RenderCopy(renderer, texture, NULL, NULL);
	if (status != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't update renderer SDL: %s", SDL_GetError());
	}
	SDL_RenderPresent(renderer);
}

void handle_window(bool * quit ) {
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {
		switch ( e.type) {
		case SDL_QUIT:

			*quit = true;
			break;
		default:
			break;			
		}
	}
	return;
}

void close_player() {

	SDL_DestroyTexture(texture);
	texture = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	SDL_Quit();
	return;
}