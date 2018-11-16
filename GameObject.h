#pragma once
#include "game.h"

class GameObject{
	public:
		GameObject(const char* texturesheet, int x, int y);
		
		void Update();
		void Render();
	private:
		int xpos;
		int ypos;

		SDL_Texture* obj_text;
		SDL_Rect srcRect, destRect;
		SDL_Renderer* renderer;

};