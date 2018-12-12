#pragma once
#include "ECS.h"

void Entity::AddGroup(Group mGroup)
{
	group_bitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}


void Entity::Update() {
	for (auto& c : components) c->Update();
}


void Entity::Draw() {
	for (auto& c : components) c->Draw();
}


bool Entity::HasGroup(Group mGroup) {
	return group_bitset[mGroup];
}


void Entity::DelGroup(Group mGroup) {
	group_bitset[mGroup] = false;
}


void Manager::Update() {
	for (auto& e : entities) e->Update();
}


void Manager::Draw() {
	for (auto& e : entities) e->Draw();
}


void Manager::Refresh()
{
	for (auto i(0u); i < max_groups; i++)
	{
		auto& v(grouped_entities[i]);
		v.erase(
			std::remove_if(std::begin(v), std::end(v),
				[i](Entity* mEntity)
		{
			return !mEntity->IsActive() || !mEntity->HasGroup(i);
		}),
			std::end(v));
	}

	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity> &mEntity)
	{
		return !mEntity->IsActive();
	}),
		std::end(entities));
}


std::vector<Entity*> &Manager::GetGroup(Group mGroup)
{
	return grouped_entities[mGroup];
}


Entity& Manager::AddEntity()
{
	Entity *e = new Entity(*this);
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));
	return *e;
}
