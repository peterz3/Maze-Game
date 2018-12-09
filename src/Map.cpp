#pragma once

#include "texture_manager.h"
#include "maze_generator.h"
#include "map.h"


Map::Map() {
	wall = TextureManager::LoadTexture("wall.png");
	space = TextureManager::LoadTexture("space.png");
	finish = TextureManager::LoadTexture("finish.png");

}
Map::~Map() {
	delete generator;
	for (int i = 0; i < map_height; i++) {
		delete map[i];
	}
	delete map;
}
void Map::init() {
	int x;
	int y;
	std::cout << "please enter map height ";
	std::cin >> x;
	map_height = x * 2 - 1;
	std::cout << "please enter map width ";
	std::cin >> y;
	map_width = y * 2 - 1;
	map = new int*[map_height];
	for (int i = 0; i < map_height; i++) {
		map[i] = new int[map_width];
	}
	generateRemainderRectangles();
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;
	dest.w = screen_width / map_width;
	dest.h = screen_height / map_height;
	dest.x = dest.y = 0;

	for (int row = 0; row < map_height; row++) {
		for (int col = 0; col < map_width; col++) {
			if (row % 2 == 1 || col % 2 == 1) {
				map[row][col] = 1;
			}
			else {
				map[row][col] = 0;
			}
		}
	}
	generator = new MazeGenerator(map, map_height, map_width);
	//map = generator->GenerateBackTrackMaze();
	map = generator->GenerateDepthFirstMaze();
	map[map_height - 1][map_width - 1] = 2;
}

void Map::DrawMap() {
	int type = 0;
	for (int row = 0; row < map_height; row++) {
		for (int column = 0; column < map_width; column++) {
			type = map[row][column];
			dest.x = (column * dest.w);
			dest.y = (row * dest.h);
			switch (type) {
			case 0:
				TextureManager::Draw(space, src, dest);
				break;
			case 1:
				TextureManager::Draw(wall, src, dest);
				break;
			case 2:
				TextureManager::Draw(finish, src, dest);
				break;
			default:
				break;
			}
		}
	}
	TextureManager::Draw(wall, src, remainder_height);
	TextureManager::Draw(wall, src, remainder_width);
}

void Map::generateRemainderRectangles() {
	int width_scaler = screen_width / map_width;
	int height_scaler = screen_height / map_height;
	remainder_height.w = screen_width;
	remainder_height.h = screen_height - (height_scaler * map_height);
	remainder_height.x = 0;
	remainder_height.y = screen_height - remainder_height.h;
	remainder_width.w = screen_width - (width_scaler * map_width);
	remainder_width.h = 800 - remainder_height.h;
	remainder_width.y = 0;
	remainder_width.x = 1250 - remainder_width.w;
}
int Map::getVal(int row, int column) {
	std::cout << row << std::endl;
	std::cout << column << std::endl;
	return map[row][column];
}
int Map::getHeight() { return map_height; }
int Map::getWidth() { return map_width; }
int Map::getDestRectHeight() { return dest.h; }
int Map::getDestRectWidth() { return dest.w; }