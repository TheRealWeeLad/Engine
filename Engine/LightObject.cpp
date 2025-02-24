#include "LightObject.h"

std::vector<LightObject*> LightObject::LightObjects{};
glm::vec3 LightObject::LightColor{ 1,1,1 };

LightObject::LightObject(glm::vec3 color) : GameObject()
{
	lightColor = color;
	LightObjects.push_back(this);
}
LightObject::LightObject(glm::vec3 color, glm::vec3 position) : GameObject(position)
{
	lightColor = color;
	LightObjects.push_back(this);
}
LightObject::~LightObject()
{
	LightObjects.erase(std::find(LightObjects.begin(), LightObjects.end(), this));
}

void LightObject::CalculateLighting()
{
	// Reset color every frame
	LightColor = { 1, 1, 1 };
	for (int i = 0; i < LightObjects.size(); i++)
	{
		LightColor *= LightObjects[i]->lightColor;
	}
}