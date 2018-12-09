#pragma once

#include "ECS.h"
#include "game.h"
#include <iostream>

class PositionComponent : public Component {
private:
	int xpos;
	int ypos;
	int height_scaler;
	int width_scaler;
public:
	PositionComponent() = default;

	PositionComponent(int x, int y) {
		xpos = x;
		ypos = y;
	}
	void update() override {
	}
	void move_up() { ypos++; }

	void move_down() { ypos--; }

	void move_left() { xpos--; }

	void move_right() { xpos++; }

	int x() { return xpos; }

	void x(int x) { xpos = x; }

	int y() { return ypos; }

	void y(int y) { ypos = y; }

	void setPos(int x, int y) { xpos = x; ypos = y; }
};