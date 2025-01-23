#pragma once

class GameObject;

class Component
{
public:
	GameObject* gameObject;

	virtual void update() {};
	void linkObject(GameObject obj);
};