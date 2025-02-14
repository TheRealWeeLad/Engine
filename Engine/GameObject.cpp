#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include <iostream>

/* STATIC */
std::vector<GameObject*> GameObject::GameObjects{};

/* CONSTRUCTOR */
GameObject::GameObject()
{
	Transform t{};
	transform = &t;
	components = {};
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
		if (components[i]) components[i]->update();
	}
}
void GameObject::UpdateAll(float time)
{
	for (int i = 0; i < GameObjects.size(); i++)
	{
		GameObjects[i]->update();
	}
}

/* PRIVATE */