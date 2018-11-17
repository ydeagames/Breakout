#pragma once
#include <typeindex>

class GameObject;

class ComponentContainer
{
private:
	GameObject* gameObject;
	std::unordered_multimap<std::type_index, std::shared_ptr<Component>> components;

public:
	ComponentContainer(GameObject* gameObject)
		: gameObject(gameObject) {};
	ComponentContainer() = delete;

private:
	ComponentContainer(const ComponentContainer &) = delete;
	ComponentContainer(ComponentContainer &&) = delete;
	ComponentContainer& operator=(ComponentContainer &&) = delete;

public:
	ComponentContainer& operator=(const ComponentContainer& container);

public:
	template<class T>
	void AddComponent(const std::shared_ptr<T>& component)
	{
		components.insert(std::make_pair<std::type_index, std::shared_ptr<Component>>(typeid(T), component));
	}

	template<class T>
	std::shared_ptr<T> GetComponent()
	{
		return std::dynamic_pointer_cast<T>(components.find(typeid(T))->second);
	}

	template<class T>
	std::vector<std::shared_ptr<T>> GetComponents()
	{
		auto range = components.equal_range(typeid(T));
		return std::vector<std::shared_ptr<T>>(range.first, range.second);
	}

	template<class T>
	bool HasComponent()
	{
		return components.count(typeid(T)) > 0;
	}

public:
	void Update();
	void Render();
};
