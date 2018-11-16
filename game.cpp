#include "game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.cpp"
#include <iostream>

SDL_Texture *image;
SDL_Rect src,dst;
GameObject* player;
GameObject* enemy;
Map* map;

SDL_Renderer* Game::renderer = nullptr;



Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	dst.h = 50;
	dst.w = 50;
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255,  255);
			is_running = true;
		}
		player = new GameObject("knight.png", 0, 0);
		enemy = new GameObject("dragon.png", 250, 250);
		map = new Map();
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
	player->Update();
	enemy->Update();

}
void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();
	player->Render();
	enemy->Render();
	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	delete player;
	delete enemy;
	delete map;

	std::cout << "QUITTTED";
}
bool Game::running() {
	return is_running;
}