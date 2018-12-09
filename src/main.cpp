#pragma once

#include "SDL.h"
#include "game.h"
#include "ofMain.h"
#include "ofApp.h"



Game *game = nullptr;
int main(int argc, char *argv[]) {
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new ofApp());

	const int fps = 60;
	const int framedelay = 100 / fps;
	Uint32 framestart;
	int frametime;

	game = new Game();
	game->init("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, false);
	while (game->running()) {

		framestart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime) {
			SDL_Delay(framedelay - frametime);
		}

	}
	game->clean();
	return 0;
}