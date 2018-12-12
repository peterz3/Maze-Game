#pragma once

#include "SDL.h"
#include "position_component.h"
#include "ECS.h"
#include "texture_manager.h"
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

	PlayerComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void Init() override {
		position = &entity->GetComponent<PositionComponent>();
		Map *map = &entity->GetComponent<Map>();
		height = map->GetDestRectHeight();
		width = map->GetDestRectWidth();
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = width;
		destRect.h = height;

	}

	void Update() override {
		destRect.x = width * position->x();
		destRect.y = height * position->y();
		

	}

	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}


};
