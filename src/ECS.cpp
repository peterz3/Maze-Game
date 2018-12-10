#include "ECS.h"

void Entity::AddGroup(Group mGroup)
{
	group_bitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}