#include "Engine/Component.h"
#include "Engine/GameObject.h"

void Component::linkObject(GameObject obj)
{
	gameObject = &obj;
}