#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include <iostream>

/* STATIC */
std::vector<GameObject*> GameObject::GameObjects{};

/* CONSTRUCTOR */
GameObject::GameObject()
{
	transform = {};
	renderer = {};
	GameObjects.push_back(this);
}
GameObject::~GameObject()
{
	GameObjects.erase(std::find(GameObjects.begin(), GameObjects.end(), this));
}

/* METHODS */
void GameObject::update()
{
	transform->update();
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->update();
	}
	renderer->update();
}
void GameObject::UpdateAll()
{
	for (int i = 0; i < GameObjects.size(); i++)
	{
		GameObjects[i]->update();
	}
}
void GameObject::addComponent(Component c)
{
	components.push_back(&c);
	c.linkObject(this);
}

/* PRIVATE */