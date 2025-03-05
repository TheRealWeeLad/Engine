#include "Transform.h"

using namespace Engine;

/* CONSTRUCTOR */
Transform::Transform()
{
	position = { 0, 0, 0 };
	rotation = IDENTITY_QUAT;
}

/* METHODS */
void Transform::update()
{
	// TODO
}

void Transform::translate(glm::vec3 translation)
{
	position += translation;
}