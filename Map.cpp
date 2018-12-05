#pragma once

#include "Map.h"
#include "TextureManager.h"
#include "MazeGenerator.h"

int lvl1[20][25] = {
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
Map::Map() {
	dirt = TextureManager::LoadTexture("dirt.png");
	grass = TextureManager::LoadTexture("grass.png");
	water = TextureManager::LoadTexture("water.png");
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
	map = generator->GenerateMaze();

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
				TextureManager::Draw(water, src, dest);
				break;
			case 1:
				TextureManager::Draw(grass, src, dest);
				break;
			case 2:
				TextureManager::Draw(dirt, src, dest);
				break;
			default:
				break;
			}
		}
	}
	TextureManager::Draw(grass, src, remainder_height);
	TextureManager::Draw(grass, src, remainder_width);
}

void Map::generateRemainderRectangles() {
	int width_scaler = 1250 / map_width;
	int height_scaler = 800 / map_height;
	remainder_height.w = 1250;
	remainder_height.h = 800 - (height_scaler * map_height);
	remainder_height.x = 0;
	remainder_height.y = 800 - remainder_height.h;
	remainder_width.w = 1250 - (width_scaler * map_width);
	remainder_width.h = 800 - remainder_height.h;
	remainder_width.y = 0;
	remainder_width.x = 1250 - remainder_width.w;
}
int Map::getVal(int row, int column) {
	std::cout << row << std::endl;
	std::cout << column << std::endl;

	std::cout << map[row][column];
	return map[row][column];
}
int Map::getHeight() { return map_height; }
int Map::getWidth() { return map_width; }
int Map::getDestRectHeight() { return dest.h; }
int Map::getDestRectWidth() { return dest.w; }