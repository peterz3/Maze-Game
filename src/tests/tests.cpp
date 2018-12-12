
#define CATCH_CONFIG_MAIN
#pragma once

#include "catch.hpp"
#include "../game.h"
#include "../position_component.h"
#include "../player_component.h"
#include "../keyboard_controller.h"
#include "../maze_solver.h"
#include "../map.h"
#include "../ECS.h"

TEST_CASE("test map generation size") {
	Game *game = new Game();
	auto& playerEntity(game->manager.AddEntity());
	playerEntity.AddComponent<Map>(5, 5);
	playerEntity.AddComponent<PositionComponent>(0, 0);
	playerEntity.AddComponent<PlayerComponent>("images/knight.png");
	playerEntity.AddComponent<KeyboardController>();
	playerEntity.AddComponent<MazeSolver>();

	REQUIRE(playerEntity.GetComponent<Map>().GetHeight() == 9);
	REQUIRE(playerEntity.GetComponent<Map>().GetWidth() == 9);
}
TEST_CASE("player is at the start (0,0)") {
	Game *game = new Game();
	auto& playerEntity(game->manager.AddEntity());
	playerEntity.AddComponent<Map>(5, 5);
	playerEntity.AddComponent<PositionComponent>(0, 0);
	playerEntity.AddComponent<PlayerComponent>("images/knight.png");
	playerEntity.AddComponent<KeyboardController>();
	playerEntity.AddComponent<MazeSolver>();

	playerEntity.GetComponent<PlayerComponent>().Init();
	playerEntity.GetComponent<PositionComponent>().Init();
	SECTION("player moves to the right") {
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_d;

		playerEntity.GetComponent<KeyboardController>().Update();
		REQUIRE(playerEntity.GetComponent<PositionComponent>().x() == 1);
	}
	SECTION("player moves down") {
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_s;

		playerEntity.GetComponent<KeyboardController>().Update();
		REQUIRE(playerEntity.GetComponent<PositionComponent>().y() == 1);

	}
	SECTION("player tries to move up at the start(shouldn't work") {
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_w;

		playerEntity.GetComponent<KeyboardController>().Update();
		REQUIRE(playerEntity.GetComponent<PositionComponent>().y() == 0);
	}
	SECTION("player tries to move left at the start(shouldn't work") {
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_a;

		playerEntity.GetComponent<KeyboardController>().Update();
		REQUIRE(playerEntity.GetComponent<PositionComponent>().x() == 0);
	}
}
TEST_CASE("player is at boundary, (8,8) for a 5x5 maze") {
	Game *game = new Game();
	auto& playerEntity(game->manager.AddEntity());
	playerEntity.AddComponent<Map>(5, 5);
	playerEntity.AddComponent<PositionComponent>(8, 8);
	playerEntity.AddComponent<PlayerComponent>("images/knight.png");
	playerEntity.AddComponent<KeyboardController>();
	playerEntity.AddComponent<MazeSolver>();

	SECTION("player tries to move down(should keep him at y = 8 )") {
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_s;

		playerEntity.GetComponent<KeyboardController>().Update();
		REQUIRE(playerEntity.GetComponent<PositionComponent>().y() == 8);
	}
	SECTION("player tries to move to the right(should keep him at x = 8 )") {
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_d;

		playerEntity.GetComponent<KeyboardController>().Update();
		REQUIRE(playerEntity.GetComponent<PositionComponent>().x() == 8);
	}
}
TEST_CASE("maze Generation") {
	Game *game = new Game();
	auto& playerEntity(game->manager.AddEntity());
	playerEntity.AddComponent<Map>(5, 5);
	playerEntity.AddComponent<PositionComponent>(8, 8);
	playerEntity.AddComponent<PlayerComponent>("images/knight.png");
	playerEntity.AddComponent<KeyboardController>();
	playerEntity.AddComponent<MazeSolver>();


	playerEntity.GetComponent<Map>().Init();

	Map emptymap = playerEntity.GetComponent<Map>();
	SECTION("check maze is generating with walls, spaces and a finish") {
		bool spaces_exist = false;
		bool walls_exist = false;
		bool finish_exists = false;
		for (int i = 0; i < emptymap.GetHeight(); i++) {
			for (int j = 0; j < emptymap.GetWidth(); j++) {
				switch (emptymap.GetVal(i, j)) {
				case 0:
					spaces_exist = true;
					break;
				case 1:
					walls_exist = true;
					break;
				case 2:
					finish_exists = true;
					break;
				}

			}
		}
		REQUIRE(spaces_exist == true);
		REQUIRE(walls_exist == true);
		REQUIRE(finish_exists == true);
	}
	SECTION("check every cell is being visited") {
		MazeGenerator *generator = emptymap.GetGenerator();
		for (int i = 0; i < generator->GetVisitArrHeight(); i++) {
			for (int j = 0; j < generator->GetVisitArrWidth(); j++) {
				REQUIRE(generator->GetVisitArrVal(i, j) == true);
			}
		}
	}
}