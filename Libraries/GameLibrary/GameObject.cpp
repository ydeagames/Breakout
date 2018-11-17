#include "GameObject.h"


GameObject::GameObject()
	: destroyed(false)
{
	AddComponent<Transform>(std::make_shared<Transform>());
}

std::shared_ptr<Transform> GameObject::transform()
{
	return GetComponent<Transform>();
}

void GameObject::Update()
{
	components.Update();
}

void GameObject::Render()
{
	components.Render();
}

void GameObject::Destroy()
{
	destroyed = true;
}

bool GameObject::IsDestroyed()
{
	return destroyed;
}
