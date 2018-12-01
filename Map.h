#pragma once
#include "SDL.h"

class Map {
public:
	Map();
	void LoadMap(int arr[20][25]);
	void DrawMap();
	int getHeight();
	int getWidth();
	int getDestRectHeight();
	int getDestRectWidth();
	int getVal(int row, int column);
	void init();
	const int screen_width = 1250;
	const int screen_height = 800;
private:
	SDL_Rect dest;
	SDL_Rect src;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	int **map;
	int map_width;
	int map_height;

};



