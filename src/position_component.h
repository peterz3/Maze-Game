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
	void Update() override {
	}
	void Move_Up() { ypos++; }

	void Move_Down() { ypos--; }

	void Move_Left() { xpos--; }

	void Move_Right() { xpos++; }

	int x() { return xpos; }

	void x(int x) { xpos = x; }

	int y() { return ypos; }

	void y(int y) { ypos = y; }

	void SetPos(int x, int y) { xpos = x; ypos = y; }
};