#pragma once
#include "MeshRenderer.h"
#include <type_traits>

// Forward declare includes to avoid circular dependencies
class Component;
class Transform;

class GameObject
{
public:
	static std::vector<GameObject*> GameObjects;

	Transform* transform;

	GameObject();
	template <typename... Components>
	GameObject(Components... components)
	{
		initializeComponents(components...);
	}
	~GameObject();

	void update();
private:
	// Constructor helper
	template <typename Comp, typename... Components>
	void initializeComponents(Comp comp, Components... comps)
	{
		static_assert(std::is_base_of<Component, Comp>::value, "component must inherit from Component");
		comp.linkObject(this);
		initializeComponents(comps...);
	}
	void initializeComponents() {}
};