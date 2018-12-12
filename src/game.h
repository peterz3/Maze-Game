#pragma once

#include "map.h"
#include <stdio.h>
#include <iostream>

static SDL_Event event;
static bool is_running = true;

class Game {
public:

	Game();

	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void HandleEvents();

	void Update();

	void Render();

	void Clean();

	bool Running();

	SDL_Texture *image;
	Manager manager;
	SDL_Rect src, dst;
	static SDL_Renderer *renderer;


private:
	int count = 0;
	SDL_Window *window;
};