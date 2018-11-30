#pragma once

#include "Map.h"
#include "TextureManager.h"

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


	//LoadMap(lvl1);

}
void Map::init() {
	std::cout << "please enter map height ";
	std::cin >> map_height;
	std::cout << "please enter map width ";
	std::cin >> map_width;
	std::cout << map_width;
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;
	dest.w = screen_width/map_width;
	dest.h = screen_height/map_height;
	dest.x = dest.y = 0;
	std::cout << map_width;
	for (int row = 0; row < map_height; row++) {
		for (int col = 0; col < map_width; col++) {
			map[row][col] = 0;
		}
	}
}

void Map::LoadMap(int arr[20][25]) {
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			map[row][column] = arr[row][column];
		}
	}
}

void Map :: DrawMap() {
	int type = 0;
	for (int row = 0; row < map_width; row++) {
		for (int column = 0; column < map_height; column++) {
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
}
int Map::getVal(int row, int column) { return map[row][column]; }
int Map::getHeight() { return map_height; }
int Map::getWidth() {
	std::cout << std::endl;
	std::cout << map_width;
	return map_width; 
}
int Map::getDestRectHeight() { return dest.h; }
int Map::getDestRectWidth(){return dest.w; }