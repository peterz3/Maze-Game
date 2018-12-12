#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID GetNewComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = GetNewComponentTypeID();
	return typeID;
}

constexpr std::size_t max_components = 32;
constexpr std::size_t max_groups = 32;

using ComponentBitSet = std::bitset<max_components>;
using GroupBitset = std::bitset<max_groups>;

using ComponentArray = std::array<Component*, max_components>;

class Component
{
public:
	Entity* entity;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual ~Component() {}

};

class Entity
{
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray component_array;
	ComponentBitSet component_bitset;
	GroupBitset group_bitset;

public:
	Entity(Manager& mManager) : manager(mManager) {}

	void Update();

	void Draw();

	bool IsActive() const { return active; }

	void Destroy() { active = false; }

	bool HasGroup(Group mGroup);

	void AddGroup(Group mGroup);

	void DelGroup(Group mGroup);

	template <typename T> bool HasComponent() const
	{
		return component_bitset[GetComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component>uPtr{ c };
		components.emplace_back(std::move(uPtr));

		component_array[GetComponentTypeID<T>()] = c;
		component_bitset[GetComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template<typename T> T& GetComponent() const
	{
		auto ptr(component_array[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, max_groups> grouped_entities;
public:
	void Update();

	void Draw();

	void Refresh();

	void AddToGroup(Entity* mEntity, Group mGroup);

	std::vector<Entity*>& GetGroup(Group mGroup);

	Entity& AddEntity();
};