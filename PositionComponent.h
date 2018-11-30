#pragma once

#include "ECS.h"
#include "game.h"
#include <iostream>

class PositionComponent : public Component {
private:
	int xpos;
	int ypos;
public:
	PositionComponent() {
		xpos = 0;
		ypos = 0;
	}

	PositionComponent(int x, int y) {
		xpos = x;
		ypos = y;
	}
	void update() override {
	}
	void move_up(int y_component) {
		int counter = 0;
		while (counter < y_component) {
			ypos++;
			counter++;
		}
	}
	void move_down(int y_component) {
		int counter = 0;
		while (counter < y_component) {
			ypos--;
			counter++;
		}
	}
	void move_left(int x_component ) {
		int counter = 0;
		while (counter < x_component ) {
			xpos--;
			counter++;
		}
	}
	void move_right(int x_component) {
		int counter = 0;
		while (counter < x_component) {
			xpos++;
			counter++;
		}
	}
	int x() { return xpos; }
	void x(int x) { xpos = x; }
	int y() { return ypos; }
	void y(int y) { ypos = y; }
	void setPos(int x, int y) { xpos = x; ypos = y; }

};