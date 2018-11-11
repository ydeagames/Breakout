#include "GameObject.h"


GameObject::GameObject()
{
	transform = std::make_shared<Transform>();
	AddComponent<Transform>(transform);
}


GameObject::~GameObject()
{
}
