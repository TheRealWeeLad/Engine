#pragma once
#include "Transform.h"
#include "MeshRenderer.h"
#include "Component.h"
#include <type_traits>
#include <unordered_set>

class GameObject
{
public:
	static std::vector<GameObject*> GameObjects;

	std::unordered_set<Component> components;
	Transform transform;

	GameObject();
	template <typename... Components>
	GameObject(Components... components)
	{
		initializeComponents(components...);
	}
	~GameObject();

	void update();
	void addComponent(Component comp);
	template<typename Comp>
	Component* addComponent();

	template<typename Comp>
	Component getComponent();

	void removeComponent(Component comp);
private:
	// Constructor helper
	template <typename Comp, typename... Components>
	void initializeComponents(Comp comp, Components... comps)
	{
		static_assert(std::is_base_of<Component, Comp>::value, "component must inherit from Component");
		components.insert(comp);
		initializeComponents(comps...);
	}
	void initializeComponents() {}
};