#pragma once
#include "ECS.h"
#include "map.h"

class MazeSolver : public Component{

public:
	MazeSolver() = default;
	void Init() override;
	void SolveMaze();
	bool RecursiveSolver(int x, int y);

private:
	Map *map;
	bool **visit_arr;
	int maze_height;
	int maze_width;
};