#pragma once

#include "ECS.h"
#include "PositionComponent.h"
#include "game.h"
class KeyboardController : public Component {
public:
	PositionComponent *position;
	Map *map;

	KeyboardController(Map *newmap) {
		map = newmap;
	}

	void init() override {
		position = &entity -> getComponent<PositionComponent>();
		x_movement = map->getDestRectWidth();
		y_movement = map->getDestRectHeight();
	}
	void update() override {
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				position->move_up(y_movement);
				break;
			case SDLK_s:
				position->move_down(y_movement);
				break;
			case SDLK_a:
				position->move_left(x_movement);
				break;
			case SDLK_d:
				position->move_right(x_movement);
				break;
			default:
				break;
			}
		}
	}
private:
	int x_movement;
	int y_movement;
};
