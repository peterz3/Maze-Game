#pragma once
#include "SDL.h"
#include "MazeGenerator.h"

class Map {
public:
	Map();
	~Map();
	void DrawMap();
	int getHeight();
	int getWidth();
	int getDestRectHeight();
	int getDestRectWidth();
	void generateRemainderRectangles();
	int getVal(int row, int column);
	void init();
	const int screen_width = 1250;
	const int screen_height = 800;
private:
	SDL_Rect dest;
	SDL_Rect src;
	SDL_Rect remainder_width;
	SDL_Rect remainder_height;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	MazeGenerator *generator;
	int **map;
	int map_width;
	int map_height;

};



