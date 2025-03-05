#include "Engine/Component.h"
#include "Engine/GameObject.h"

using namespace Engine;

void Component::linkObject(GameObject* obj)
{
	gameObject = obj;
}