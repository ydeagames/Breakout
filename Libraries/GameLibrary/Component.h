#pragma once
#include <typeindex>

class Component
{

};

class ComponentContainer
{
private:
	std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

public:
	template<class T>
	void AddComponent(const T& component)
	{
		components[typeid(T)] = std::make_unique<T>(component);
	}

	template<class T>
	const T& GetComponent()
	{
		return *dynamic_cast<T>(components[typeid(T)]);
	}
};
