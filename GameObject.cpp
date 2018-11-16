#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y) {
	xpos = x;
	ypos = y;
	obj_text = TextureManager::LoadTexture(texturesheet);
}

void GameObject::Update() {
	xpos++;
	ypos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos/5;
	destRect.y = ypos/5;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, obj_text, &srcRect, &destRect);
}