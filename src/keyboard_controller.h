#pragma once

#include "ECS.h"
#include "position_component.h"
#include "game.h"
class KeyboardController : public Component {
public:
	PositionComponent *position;
	Map *map;

	KeyboardController(Map *newmap) {
		map = newmap;
	}
	bool ValidPosCheck(int row, int col) {
		return (map->getVal(row , col )) != 1;
	}

	void init() override {
		position = &entity->getComponent<PositionComponent>();
		x_movement = map->getDestRectWidth();
		y_movement = map->getDestRectHeight();
	}
	void update() override {
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				if (position->y() > 0 && ValidPosCheck(position->y() - 1, position->x())) {
					position->move_down();
				}
				break;
			case SDLK_s:
				if ((position->y() < map->getHeight() - 1) && ValidPosCheck(position->y() + 1, position->x())) {
					if (WinCheck(position->y() + 1, position->x() )) {
						position->move_up();
						Game::is_running = false;
						std::cout << "YOU WIN CONGRATS" << std::endl;
					}
					position->move_up();
				}
				break;
			case SDLK_a:
				if (position->x() > 0 && ValidPosCheck(position->y(), position->x() - 1)) {
					position->move_left();
				}
				break;
			case SDLK_d:
				if ((position->x() < map->getWidth() - 1) && ValidPosCheck(position->y(), position->x() + 1)) {
					if (WinCheck(position->y() , position->x() + 1)) {
						position->move_right();
						Game::is_running = false;
						std::cout << "YOU WIN CONGRATS" << std::endl;
						break;
					}
					position->move_right();
				}
				break;
			case SDLK_p:
			
			default:
				break;
			}
		}
	}
	bool WinCheck(int x , int y) {
		return map->getVal(x, y) == 2;
	}
private:
	int x_movement;
	int y_movement;
};