#pragma once

#include "game.h"
#include "map.h"
#include "position_component.h"
#include "player_component.h"
#include "ECS.h"
#include "keyboard_controller.h"
#include "maze_solver.h"
#include <iostream>

SDL_Texture *image;
Manager manager;
SDL_Rect src, dst;


auto& playerEntity(manager.AddEntity());

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::is_running = true;


Game::Game() {

}
Game::~Game() {

}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		}
		is_running = true;
	}
	playerEntity.AddComponent<Map>();
	playerEntity.AddComponent<PositionComponent>(0, 0);
	playerEntity.AddComponent<PlayerComponent>("knight.png");
	playerEntity.AddComponent<KeyboardController>();
	playerEntity.AddComponent<MazeSolver>();
}
void Game::HandleEvents() {
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		std::cout << "close";
		is_running = false;
		break;
	default:
		break;
	}


}
void Game::Update() {
	manager.Refresh();
	manager.Update();

}
void Game::Render() {
	SDL_RenderClear(renderer);
	manager.Draw();
	SDL_RenderPresent(renderer);
}
void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "QUITTTED";
}
bool Game::Running() {
	return is_running;
}