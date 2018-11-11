#include "GameObject.h"


GameObject::GameObject()
{
	AddComponent<Transform>(std::make_shared<Transform>());
}

std::shared_ptr<Transform> GameObject::transform()
{
	return GetComponent<Transform>();
}
