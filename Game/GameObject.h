#pragma once
#include <typeindex>

class GameObject
{
private:
	ComponentContainer components;

public:
	GameObject();
	~GameObject();

public:
	template<class T>
	void AddComponent(T&& component)
	{
		components.AddComponent(std::forward(component));
	}

	template<class T>
	const T& GetComponent()
	{
		return components.GetComponent();
	}
};

