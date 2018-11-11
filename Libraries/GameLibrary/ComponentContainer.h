#pragma once
#include <typeindex>

class ComponentContainer
{
private:
	std::unordered_map<std::type_index, std::shared_ptr<Component>> components;

public:
	template<class T>
	void AddComponent(const std::shared_ptr<T>& component)
	{
		if (!components[typeid(T)])
			components[typeid(T)] = component;
	}

	template<class T>
	std::shared_ptr<T> GetComponent()
	{
		return std::dynamic_pointer_cast<T>(components[typeid(T)]);
	}

	template<class T>
	bool HasComponent()
	{
		return components[typeid(T)];
	}
};
