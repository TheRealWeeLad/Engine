#pragma once
#include "MeshRenderer.h"
#include <array>

// Forward declare includes to avoid circular dependencies
class Component;
class Transform;

class GameObject
{
private:
	static const int MAX_NUM_COMPONENTS = 100;
public:
	static std::vector<GameObject*> GameObjects;
	// Array of components each located at index COMPONENT.ID
	std::array<Component*, MAX_NUM_COMPONENTS> components;

	Transform* transform;

	GameObject();
	~GameObject();

	void update();
	static void UpdateAll();

	template<typename SomeComponent>
	void addComponent(SomeComponent* c)
	{
		components[c->ID] = c;
	}

	template<typename SomeComponent>
	SomeComponent* getComponent()
	{
		return (SomeComponent*) components[SomeComponent::ID];
	}

	template<typename SomeComponent>
	void removeComponent()
	{
		components[SomeComponent::ID] = nullptr;
	}
};