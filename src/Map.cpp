#pragma once

#include "texture_manager.h"
#include "maze_generator.h"
#include "map.h"

/*
constructors intiialize textures and map_height and width
*/
Map::Map() {
	wall = TextureManager::LoadTexture("images/wall.png");
	space = TextureManager::LoadTexture("images/space.png");
	finish = TextureManager::LoadTexture("images/finish.png");
	solution = TextureManager::LoadTexture("images/solution.png");
	map_height = 0;
	map_width = 0;
}

Map::Map(int height, int width) {
	wall = TextureManager::LoadTexture("images/wall.png");
	space = TextureManager::LoadTexture("images/space.png");
	finish = TextureManager::LoadTexture("images/finish.png");
	solution = TextureManager::LoadTexture("images/solution.png");
	map_height =  2 * height - 1;
	map_width = 2 * width - 1;
}
/*
destroys every array pointer then the double array pointer
also destroys generator
*/
Map::~Map() {
	delete generator;
	for (int i = 0; i < map_height; i++) {
		delete map[i];
	}
	delete map;
}
/*
if the height and width weren't passed throuh the constructor they are obtained by user input
The input is multiplied by two in order to create a grid-like pattern, which is neccesarry for maze generation
after that the map array is filled out in a gridlike pattern
The maze generator is run which destroys walls between cells by visiting every cell, but not destroying every wall
*/
void Map::Init() {
	if (map_height == 0 && map_width == 0) {
		int height_input;
		int width_input;
		std::cout << "please enter a height between 2 and 100" << std::endl;
		while (!(std::cin >> height_input) || height_input > 100 || height_input < 2) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.  Try again: ";
		}
		map_height = height_input * 2 - 1;
		std::cout << "please enter map width between 2 and 100" << std::endl;
		while (!(std::cin >> width_input) || width_input > 100 || width_input < 2) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.  Try again: ";
		}
		map_width = width_input * 2 - 1;
	
	}
	std::cout << "Use W,A,S,D to move or hit P to get solution" << std::endl;

	map = new int*[map_height];
	for (int i = 0; i < map_height; i++) {
		map[i] = new int[map_width];
	}
	GenerateRemainderRectangles();
	src.x = src.y = 0;
	src.w = src.h = 32;
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

/*
map is drawn by iterating through the map double array and displaying the respective texture for each value
*/
void Map::Draw() {
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
				case 3:
					TextureManager::Draw(solution, src, dest);
					break;
				default:
					break;
			}
		}
	}
	TextureManager::Draw(wall, src, remainder_height);
	TextureManager::Draw(wall, src, remainder_width);
}

/*
calculates what part of the screen isn't being used due to decimal point cutting(not every user input heigh and width
fits the screen perfectly) 
The parts not being used have black rectangles overlayed onto them
*/
void Map::GenerateRemainderRectangles() {
	int width_scaler = screen_width / map_width;
	int height_scaler = screen_height / map_height;
	remainder_height.w = screen_width;
	remainder_height.h = screen_height - (height_scaler * map_height);
	remainder_height.x = 0;
	remainder_height.y = screen_height - remainder_height.h;
	remainder_width.w = screen_width - (width_scaler * map_width);
	remainder_width.h = screen_height - remainder_height.h;
	remainder_width.y = 0;
	remainder_width.x = screen_width - remainder_width.w;
}

int Map::GetVal(int row, int column) {
	return map[row][column];
}

void Map::ChangeVal(int row, int col, int val) {
	map[row][col] = val;
}

int Map::GetHeight() { return map_height; }

int Map::GetWidth() { return map_width; }

int Map::GetDestRectHeight() { return dest.h; }

int Map::GetDestRectWidth() { return dest.w; }

int** Map::GetMapArray() { return map; }

MazeGenerator* Map::GetGenerator() { return generator; }
