#pragma once
#include "SDL.h"
#include "maze_generator.h"
#include "ECS.h"

class Map :  public Component{
public:
	Map();
	~Map();
	void Draw() override;
	int GetHeight();
	int GetWidth();
	int GetDestRectHeight();
	int GetDestRectWidth();
	void GenerateRemainderRectangles();
	int GetVal(int row, int column);
	void ChangeVal(int row, int col, int val);
	void Init() override;
	const int screen_width = 1000;
	const int screen_height = 600;
private:
	SDL_Rect dest;
	SDL_Rect src;
	SDL_Rect remainder_width;
	SDL_Rect remainder_height;
	SDL_Texture* wall;
	SDL_Texture* space;
	SDL_Texture* finish;
	SDL_Texture* solution;
	MazeGenerator *generator;
	int **map;
	int map_width;
	int map_height;

};




