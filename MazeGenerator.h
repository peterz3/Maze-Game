#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>

class MazeGenerator {
	enum Direction { UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4 };
public:
	MazeGenerator(int **MapArray, int map_height, int map_width);
	~MazeGenerator();
	int** GenerateMaze() {
		RecursiveBackTracker(0, 0);
		return Map;
	}
	void RecursiveBackTracker(int x, int y);
private:
	int **Map;
	bool **visitArr;
	int height;
	int width;
};