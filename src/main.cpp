#pragma once

#include "SDL.h"
#include "game.h"
#include "ofMain.h"
#include "ofApp.h"



Game *game = nullptr;
int main(int argc, char *argv[]) {

	const int fps = 60;
	const int framedelay = 100 / fps;
	Uint32 framestart;
	int frametime;

	game = new Game();
	game->Init("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, false);
	while (game->Running()) {

		framestart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime) {
			SDL_Delay(framedelay - frametime);
		}

	}

	game->Clean();
	delete game;
	return 0;
}