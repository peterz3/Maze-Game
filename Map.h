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
	private:
		SDL_Rect dest;
		SDL_Rect src;
		SDL_Texture* dirt;
		SDL_Texture* grass;
		SDL_Texture* water;
		int map[20][25];
		int map_width;
		int map_height;

};

