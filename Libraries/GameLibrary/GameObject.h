#pragma once
#include "ComponentContainer.h"
#include "Transform.h"
#include <typeindex>

class GameObject final
{
private:
	ComponentContainer components;

public:
	std::shared_ptr<Transform> transform();

public:
	GameObject();

public:
	template<class T>
	void AddComponent(const std::shared_ptr<T>& component)
	{
		if (component)
			component->gameObject = this;
		components.AddComponent(component);
	}

	template<class T>
	std::shared_ptr<T> GetComponent()
	{
		return components.GetComponent<T>();
	}

	template<class T>
	bool HasComponent()
	{
		return components.HasComponent();
	}

public:
	void Update();
	void Render();
};

