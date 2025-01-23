#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Component.h"

class Transform
{
public:
	glm::vec3 position;
	glm::quat rotation;

	void update();
};