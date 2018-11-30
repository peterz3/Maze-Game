#pragma once

#include "game.h"
#include "Map.cpp"
#include "PositionComponent.h"
#include "PlayerComponent.h"
#include "ECS.h"
#include "KeyBoardController.h"
#include <iostream>

SDL_Texture *image;
Manager manager;
SDL_Rect src,dst;


auto& playerEntity(manager.addEntity());

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255,  255);
		
		}
		is_running = true;
	}
	//player = new GameObject("knight.png", 0, 0);
	//enemy = new GameObject("dragon.png", 250, 250);
	map = new Map();
	playerEntity.addComponent<PositionComponent>();
	playerEntity.addComponent<PlayerComponent>("knight.png");
	playerEntity.addComponent<KeyboardController>(map);
} 
void Game::handleEvents() {
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
	//player->Update();
	//enemy->Update()
	manager.refresh();
	manager.update();

}
void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();
	//player->Render();
	//enemy->Render();
	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	//delete player;
	//delete enemy;
	delete map;

	std::cout << "QUITTTED";
}
bool Game::running() {
	return is_running;
}