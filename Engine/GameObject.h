#pragma once
#include "MeshRenderer.h"

// Forward declare includes to avoid circular dependencies
class Component;
class Transform;

class GameObject
{
public:
	static std::vector<GameObject*> GameObjects;
	std::vector<Component*> components;

	Transform* transform;
	MeshRenderer* renderer;

	GameObject();
	template <typename... Components>
	GameObject(Components... components) : GameObject()
	{
		initializeComponents(components...);
	}
	~GameObject();

	void update();
	static void UpdateAll();

	void addComponent(Component c);
	template<typename SomeComponent>
	SomeComponent* getComponent()
	{
		for (int i = 0; i < components.size(); i++)
		{
			Component* c{ components[i] };
			std::cout << c->ID << ' ' << SomeComponent::ID << std::endl;
			if (c->ID == SomeComponent::ID) return (SomeComponent*) c;
		}
		return nullptr;
	}
private:
	// Constructor helper
	template <typename Comp, typename... Components>
	void initializeComponents(Comp comp, Components... comps)
	{
		Component* c{ (Component*)&comp };
		c->linkObject(this);
		components.push_back(c);
		initializeComponents(comps...);
	}
	template <typename Comp>
	void initializeComponents(Comp comp)
	{
		Component* c{ (Component*)&comp };
		c->linkObject(this);
		components.push_back(c);
	}
};