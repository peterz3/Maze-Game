#include "game.h"
#include <iostream>

SDL_Texture *image;

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			is_running = true;
		}
		SDL_Surface *tmpSurface = IMG_Load("mark.png");
		std::cout << IMG_GetError();
		image = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
} 
void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
			is_running = false;
			break;
	default:
		break;
	}


}
void Game::update() {
	count++;

}
void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, image, NULL, NULL);
	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "QUITTTED";
}
bool Game::running() {
	return is_running;
}