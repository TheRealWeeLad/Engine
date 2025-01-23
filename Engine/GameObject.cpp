#include "GameObject.h"

/* STATIC */
std::vector<GameObject*> GameObject::GameObjects{};

/* CONSTRUCTOR */
GameObject::GameObject()
{
	components = {};
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

void GameObject::addComponent(Component comp)
{
	components.insert(comp);
}
template<typename Comp>
Component* GameObject::addComponent()
{
	static_assert(std::is_base_of<Component, Comp>::value, "component must inherit from Component");
	Comp comp{};
	components.insert(comp);
	return &comp;
}

template<typename Comp>
Component GameObject::getComponent()
{
	static_assert(std::is_base_of<Component, Comp>::value, "component must inherit from Component");
	// TODO: IDFK
}

void GameObject::removeComponent(Component comp)
{
	// TODO: IDFK
}



/* PRIVATE */