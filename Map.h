#pragma once
#ifndef Map_hpp
#define Map_hpp


#include "game.h"

class Map {
	public:
		Map();
		void LoadMap(int arr[20][25]);
		void DrawMap();
	private:
		SDL_Rect dest;
		SDL_Rect src;
		SDL_Texture* dirt;
		SDL_Texture* grass;
		SDL_Texture* water;
		int map[20][25];

};

#endif;