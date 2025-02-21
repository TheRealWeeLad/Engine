#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Identity.h"

class Component;

class Transform
{
public:
	glm::vec3 position;
	glm::quat rotation;

	Transform();

	void update();
	void translate(glm::vec3 translation);
};