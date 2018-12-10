#pragma once

#include "ECS.h"
#include "position_component.h"
#include "game.h"
class KeyboardController : public Component {
public:
	PositionComponent *position;
	Map *map;

	KeyboardController() {
	}
	bool ValidPosCheck(int row, int col) {
		return (map->GetVal(row , col )) != 1;
	}

	void Init() override {
		position = &entity->GetComponent<PositionComponent>();
		map = &entity->GetComponent<Map>();
		x_movement = map->GetDestRectWidth();
		y_movement = map->GetDestRectHeight();
	}
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
						Game::is_running = false;
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
						Game::is_running = false;
						std::cout << "YOU WIN CONGRATS!" << std::endl;
						break;
					}
					position->Move_Right();
				}
				break;
			case SDLK_p:
			
			default:
				break;
			}
		}
	}
	bool WinCheck(int x , int y) {
		return map->GetVal(x, y) == 2;
	}
private:
	int x_movement;
	int y_movement;
};