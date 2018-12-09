#pragma once
#include "SDL.h"

#pragma once


#include "SDL.h"
#include "Map.h"
#include <stdio.h>
#include <iostream>


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
	int getMapHeight() { return Game::map->getHeight(); }
	int getMapWidth() { return Game::map->getWidth(); }

	static SDL_Event event;
	static SDL_Renderer *renderer;
	static bool is_running;

private:
	Map* map;
	int count = 0;
	SDL_Window *window;
};