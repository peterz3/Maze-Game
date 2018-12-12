#pragma once

#include "maze_generator.h"

MazeGenerator::MazeGenerator(int **MapArray, int map_height, int map_width) {
	height = (map_height + 1) / 2;
	width = (map_width + 1) / 2;
	map = MapArray;
	visit_arr = new bool *[height];
	for (int i = 0; i < height; i++) {
		visit_arr[i] = new bool[width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			visit_arr[i][j] = false;
		}
	}
}

MazeGenerator::~MazeGenerator() {
	for (int i = 0; i < height; i++) {
		delete visit_arr[i];
	}
	delete visit_arr;
}

void  MazeGenerator::RecursiveBackTracker(int x, int y) 
{
	visit_arr[x][y] = true;
	std::vector<Direction> viableDirections;
	viableDirections.push_back(Direction::UP);
	viableDirections.push_back(Direction::LEFT);
	viableDirections.push_back(Direction::RIGHT);
	viableDirections.push_back(Direction::DOWN);
	while (!viableDirections.empty()) {
		int rand = std::rand() % viableDirections.size();
		Direction dir = viableDirections[rand];
		viableDirections.erase(viableDirections.begin() + rand);
		switch (dir) {
			case 1:
				if (x > 0) {
					if (visit_arr[x - 1][y] == false) {
						map[2 * x - 1][2 * y] = 0;
						RecursiveBackTracker(x - 1, y);
					}
				}
				break;
			case 2:
				if (y < width - 1) {
					if (visit_arr[x][y + 1] == false) {
						map[2 * x][2 * y + 1] = 0;
						RecursiveBackTracker(x, y + 1);
					}
				}	
				break;
			case 3:
				if (x < height - 1) {
					if (visit_arr[x + 1][y] == false) {
						map[2 * x + 1][2 * y] = 0;
						RecursiveBackTracker(x + 1, y);
					}
				}
				break;
			case 4:
				if (y > 0) {
					if (visit_arr[x][y - 1] == false) {
						map[2 * x][2 * y - 1] = 0;
						RecursiveBackTracker(x, y - 1);
					}
				}
				break;
			default:
				break;
		}
	}
}