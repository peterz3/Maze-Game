#pragma once

#include "texture_manager.h"
#include "game.h"
#include "SDL_image.h"
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface *tempSurface = IMG_Load(texture);
	std::cout << IMG_GetError();
	SDL_Texture	*tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}