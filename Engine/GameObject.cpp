#include "GameObject.h"
#include "Component.h"
#include "Transform.h"

/* STATIC */
std::vector<GameObject*> GameObject::GameObjects{};

/* CONSTRUCTOR */
GameObject::GameObject()
{
	transform = {};
	GameObjects.push_back(this);
}
GameObject::~GameObject()
{
	GameObjects.erase(std::find(GameObjects.begin(), GameObjects.end(), this));
}

/* METHODS */
void GameObject::update()
{
	// TODO
}

/* PRIVATE */