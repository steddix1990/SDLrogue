// w16016982	Stephen Dixon	KV6003

#include "GameObject.h"

GameObject::GameObject(ObjectType type) : TYPE(type)
{}

void GameObject::render()
{}

void GameObject::update()
{}

void GameObject::processCollision(GameObject* object)
{}

ObjectType GameObject::GetType() const
{
	return TYPE;
}

void GameObject::clean()
{}