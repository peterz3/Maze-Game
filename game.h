#pragma once


#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"
#include <stdio.h>

class Game {
	public:
		Game();
		~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();

	static SDL_Renderer *renderer;

private:
	int count = 0;
	bool is_running;
	SDL_Window *window;
};



