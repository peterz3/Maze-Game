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
	int height;
	int width;

public:
	PlayerComponent() = default;
	PlayerComponent(const char* path, int player_height, int player_width) {
		texture = TextureManager::LoadTexture(path);
		height = player_height;
		width = player_width;
	}
	void init() override {
		position = &entity->getComponent<PositionComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = width;
		destRect.h = height;

	}
	void update() override {
		destRect.x = width * position->x();
		destRect.y = height * position->y();

	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}


};
