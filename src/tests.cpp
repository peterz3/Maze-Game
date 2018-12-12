/*
#define CATCH_CONFIG_MAIN
#pragma once

#include "catch.hpp"
#include "game.h"
#include "position_component.h"
#include "player_component.h"
#include "keyboard_controller.h"
#include "maze_solver.h"
#include "map.h"
#include "ECS.h"


TEST_CASE(){
	Game *game = new Game();
	auto& playerEntity(game->manager.AddEntity());
	playerEntity.AddComponent<Map>(5,5);
	playerEntity.AddComponent<PositionComponent>(0, 0);
	playerEntity.AddComponent<PlayerComponent>("knight.png");
	playerEntity.AddComponent<KeyboardController>();
	playerEntity.AddComponent<MazeSolver>();
	
	playerEntity.GetComponent<PlayerComponent>().Init();
	event.type = SDL_KEYDOWN;
	playerEntity.Update();
	
	//game->Update();
	std::cout << playerEntity.GetComponent<PositionComponent>().y();
	std::cout << playerEntity.GetComponent<PositionComponent>().y();
	std::cout << playerEntity.GetComponent<PositionComponent>().y();
	std::cout << playerEntity.GetComponent<PositionComponent>().y();
	REQUIRE(true);
}*/
