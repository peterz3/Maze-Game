#pragma once

#include "SDL.h"
#include "map.h"
#include <stdio.h>
#include <iostream>


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

	static SDL_Event event;
	static SDL_Renderer *renderer;
	static bool is_running;

private:
	int count = 0;
	SDL_Window *window;
};