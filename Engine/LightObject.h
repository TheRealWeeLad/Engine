#pragma once
#include "GameObject.h"

class LightObject :
    public GameObject
{
public:
    static std::vector<LightObject*> LightObjects;
    static glm::vec3 LightColor;
    glm::vec3 lightColor;

    LightObject(glm::vec3 color);
    LightObject(glm::vec3 color, glm::vec3 position);
    ~LightObject();

    static void CalculateLighting();
};

