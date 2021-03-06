#pragma once

#include "ECS.h"
#include "position_component.h"
#include "game.h"
#include "maze_solver.h"

class KeyboardController : public Component {
public:
	PositionComponent *position;
	Map *map;
	MazeSolver *solver;

	KeyboardController() = default;

	/*
	checks that the input coordinates don't lead to a wall
	*/
	bool ValidPosCheck(int row, int col) {
		return (map->GetVal(row , col )) != 1;
	}

	/*
	initializes the keyboard controller my getting the map and position member variables
	*/
	void Init() override {
		position = &entity->GetComponent<PositionComponent>();
		map = &entity->GetComponent<Map>();
	}

	/*
	checks wether a key is pressed, also evaluates position before actually moving, by checking
	for walls and game borders.
	Also if you move onto the win block using either D or S the game is turned off
	If P is pressed the maze solver is run
	*/
	void Update() override {
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym) {
				case SDLK_w:
					if (position->y() > 0 && ValidPosCheck(position->y() - 1, position->x())) {
						position->Move_Down();
					}
					break;
				case SDLK_s:
					if ((position->y() < map->GetHeight() - 1) && ValidPosCheck(position->y() + 1, position->x())) {
						if (WinCheck(position->y() + 1, position->x() )) {
							position->Move_Up();
							is_running = false;
							std::cout << "YOU WIN CONGRATS!" << std::endl;
						}
						position->Move_Up();
					}
					break;
				case SDLK_a:
					if (position->x() > 0 && ValidPosCheck(position->y(), position->x() - 1)) {
						position->Move_Left();
					}
					break;
				case SDLK_d:
					if ((position->x() < map->GetWidth() - 1) && ValidPosCheck(position->y(), position->x() + 1)) {
						if (WinCheck(position->y() , position->x() + 1)) {
							position->Move_Right();
							is_running = false;
							std::cout << "YOU WIN CONGRATS!" << std::endl;
							break;
						}
						position->Move_Right();
					}
					break;
				case SDLK_p:
					solver = &entity->GetComponent<MazeSolver>();
					solver->SolveMaze();
					break;
				default:
					break;
			}
		}
	}

	/*
	checks wether the input coordinates lead to a finish block*/
	bool WinCheck(int row , int col) {
		return map->GetVal(row, col) == 2;
	}
};