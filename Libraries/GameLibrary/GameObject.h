#pragma once
#include "ComponentContainer.h"
#include "Transform.h"
#include <typeindex>

class GameObject final
{
public:
	const std::string name;

private:
	ComponentContainer components;
	bool destroyed;

public:
	std::shared_ptr<Transform> transform();

private:
	GameObject(const std::string& name);
	GameObject(const GameObject &) = delete;
	GameObject& operator=(const GameObject &) = delete;
	GameObject(GameObject &&) = delete;
	GameObject& operator=(GameObject &&) = delete;

public:
	template<class T>
	void AddComponent(const std::shared_ptr<T>& component)
	{
		components.AddComponent(component);
	}

	template<class T>
	std::shared_ptr<T> GetComponent()
	{
		return components.GetComponent<T>();
	}

	template<class T>
	std::vector<std::shared_ptr<T>> GetComponents()
	{
		return components.GetComponents<T>();
	}

	template<class T>
	bool HasComponent()
	{
		return components.HasComponent();
	}

public:
	void Update();
	void Render();

	void Destroy();
	bool IsDestroyed();

public:
	static std::shared_ptr<GameObject> CreatePrefab(std::string name = "New Game Object");
	static std::weak_ptr<GameObject> Create(std::string name = "New Game Object");
	static std::weak_ptr<GameObject> Find(std::string name);
	static std::weak_ptr<GameObject> Instantiate(const std::shared_ptr<GameObject>& originalObject);
};

