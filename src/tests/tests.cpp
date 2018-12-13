/*
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
	delete game;
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
		delete game;
	}

	SECTION("player moves down") {
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_s;

		playerEntity.GetComponent<KeyboardController>().Update();
		REQUIRE(playerEntity.GetComponent<PositionComponent>().y() == 1);
		delete game;

	}

	SECTION("player tries to move up at the start(shouldn't work") {
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_w;

		playerEntity.GetComponent<KeyboardController>().Update();
		REQUIRE(playerEntity.GetComponent<PositionComponent>().y() == 0);
		delete game;
	}

	SECTION("player tries to move left at the start(shouldn't work") {
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_a;

		playerEntity.GetComponent<KeyboardController>().Update();
		REQUIRE(playerEntity.GetComponent<PositionComponent>().x() == 0);
		delete game;
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
		delete game;
	}

	SECTION("player tries to move to the right(should keep him at x = 8 )") {
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_d;

		playerEntity.GetComponent<KeyboardController>().Update();
		REQUIRE(playerEntity.GetComponent<PositionComponent>().x() == 8);
		delete game;
	}
}

TEST_CASE("maze Generation") {
	Game *game = new Game();
	auto& playerEntity(game->manager.AddEntity());
	playerEntity.AddComponent<Map>(5, 5);
	playerEntity.AddComponent<PositionComponent>(0, 0);
	playerEntity.AddComponent<PlayerComponent>("images/knight.png");
	playerEntity.AddComponent<KeyboardController>();
	playerEntity.AddComponent<MazeSolver>();


	playerEntity.GetComponent<Map>().Init();
	Map map = playerEntity.GetComponent<Map>();

	SECTION("check maze is generating with walls, spaces and a finish") {
		bool spaces_exist = false;
		bool walls_exist = false;
		bool finish_exists = false;
		for (int i = 0; i < map.GetHeight(); i++) {
			for (int j = 0; j < map.GetWidth(); j++) {
				switch (map.GetVal(i, j)) {
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
		MazeGenerator *generator = map.GetGenerator();
		for (int i = 0; i < generator->GetVisitArrHeight(); i++) {
			for (int j = 0; j < generator->GetVisitArrWidth(); j++) {
				REQUIRE(generator->GetVisitArrVal(i, j) == true);
			}
		}
	}

	SECTION("try to move to the right on a maze piece") {
		//move to the right until you hit a piece of maze
		while (map.GetVal(playerEntity.GetComponent<PositionComponent>().x(), playerEntity.GetComponent<PositionComponent>().y() + 1) != 1) {
			playerEntity.GetComponent<PositionComponent>().Move_Right();
		}
		//remember the current y, then try to move to the right and check y didnt change(cus u cant go through walls)
		int current_y = playerEntity.GetComponent<PositionComponent>().y();
		playerEntity.GetComponent<PositionComponent>().Move_Right();
		REQUIRE(current_y == playerEntity.GetComponent<PositionComponent>().y());
	}

	SECTION("try to move down on a maze piece") {
		// move down until you hit a maze piece
		while (map.GetVal(playerEntity.GetComponent<PositionComponent>().x() + 1, playerEntity.GetComponent<PositionComponent>().y()) != 1) {
			playerEntity.GetComponent<PositionComponent>().Move_Down();
		}
		//remember the current x, then try to move down and check x didnt change(cus u cant go through walls)
		int current_x = playerEntity.GetComponent<PositionComponent>().x();
		playerEntity.GetComponent<PositionComponent>().Move_Down();
		REQUIRE(current_x == playerEntity.GetComponent<PositionComponent>().x());
	}
}

TEST_CASE("check maze stops running when moving to solution block") {
	Game *game = new Game();
	auto& playerEntity(game->manager.AddEntity());
	playerEntity.AddComponent<Map>(5, 5);
	playerEntity.AddComponent<PositionComponent>(0, 0);
	playerEntity.AddComponent<PlayerComponent>("images/knight.png");
	playerEntity.AddComponent<KeyboardController>();
	playerEntity.AddComponent<MazeSolver>();

	playerEntity.GetComponent<Map>().Init();
	Map map = playerEntity.GetComponent<Map>();
	//first it finds wether there is a spot avaiable on top or to the right of the finish block, then it moves onto the block
	if (map.GetVal(7, 8) == 0) {
		playerEntity.GetComponent<PositionComponent>().SetPos(7, 8);
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_d;
		playerEntity.GetComponent<KeyboardController>().Update();
	}
	else if (map.GetVal(8, 7) == 0) {
		playerEntity.GetComponent<PositionComponent>().SetPos(8, 7);
		Game::event.type = SDL_KEYDOWN;
		Game::event.key.keysym.sym = SDLK_s;
		playerEntity.GetComponent<KeyboardController>().Update();
	}
	REQUIRE(game->Running() == false);
}

TEST_CASE("maze solver tests") {
	Game *game = new Game();
	auto& playerEntity(game->manager.AddEntity());
	playerEntity.AddComponent<Map>(5, 5);
	playerEntity.AddComponent<PositionComponent>(0, 0);
	playerEntity.AddComponent<PlayerComponent>("images/knight.png");
	playerEntity.AddComponent<KeyboardController>();
	playerEntity.AddComponent<MazeSolver>();

	playerEntity.GetComponent<Map>().Init();
	Map map = playerEntity.GetComponent<Map>();
	playerEntity.GetComponent<MazeSolver>().Init();

	SECTION("check that finish block still exists after solution generated") {
		playerEntity.GetComponent<MazeSolver>().SolveMaze();
		REQUIRE(map.GetVal(8, 8) == 2);
	}

	SECTION("check that solution blocks lead to the finish") {
		bool solution_exists = false;
		playerEntity.GetComponent<MazeSolver>().SolveMaze();
		//scans 2x2 area around finish for solution block
		for (int i = map.GetHeight() - 2; i < map.GetHeight(); i++) {
			for (int j = map.GetWidth() - 2; j < map.GetWidth(); j++) {
				if (map.GetVal(i, j) == 3) {
					solution_exists = true;
				}
			}
		}
		REQUIRE(solution_exists == true);
	}
}*/