#pragma once

#include "SDL.h"
#include "PositionComponent.h"
#include "ECS.h"
#include "TextureManager.h"
#include "game.h"
class PlayerComponent : public Component {
private:
	PositionComponent *position;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:
	PlayerComponent() = default;
	PlayerComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}
	void init() override {
		position = &entity->getComponent<PositionComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 32;
		
	}
	void update() override {
			destRect.x = position->x();
			destRect.y = position->y();
		
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}


};


