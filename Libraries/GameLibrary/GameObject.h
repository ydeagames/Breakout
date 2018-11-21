#pragma once
#include "ComponentContainer.h"
#include "Transform.h"
#include <typeindex>

class GameObject final : public std::enable_shared_from_this<GameObject>
{
public:
	const std::string name;
	const std::string tag;
	const std::string layer;

private:
	std::unique_ptr<ComponentContainer> components;
	bool destroyed;

public:
	std::shared_ptr<Transform> transform();

private:
	GameObject(const std::string& name, const std::string& tag, const std::string& layer);
	GameObject(const GameObject &) = delete;
	GameObject& operator=(const GameObject &) = delete;
	GameObject(GameObject &&) = delete;
	GameObject& operator=(GameObject &&) = delete;
	void Initialize();

public:
	template<class T>
	void AddComponent(const std::shared_ptr<T>& component)
	{
		components->AddComponent(component);
	}

	template<class T, typename... Args>
	void AddNewComponent(Args&&... args)
	{
		AddComponent<T>(std::make_shared<T>(std::forward<Args>(args)...));
	}

	template<class T>
	std::shared_ptr<T> GetComponent()
	{
		return components->GetComponent<T>();
	}

	template<class T>
	std::vector<std::shared_ptr<T>> GetComponents()
	{
		return components->GetComponents<T>();
	}

	template<class T>
	bool HasComponent()
	{
		return components->HasComponent();
	}

public:
	void Start();
	void Update();
	void Render();

	void Destroy();
	bool IsDestroyed();

public:
	static std::shared_ptr<GameObject> CreatePrefab(const std::string& name = "New Game Object", const std::string& tag = "Untagged", const std::string& layer = "Default");
	static std::shared_ptr<GameObject> Create(const std::string& name = "New Game Object", const std::string& tag = "Untagged", const std::string& layer = "Default");
	static std::shared_ptr<GameObject> Find(const std::string& name);
	static std::shared_ptr<GameObject> FindWithTag(const std::string & tag);
	static std::vector<std::shared_ptr<GameObject>> FindGameObjectsWithTag(const std::string & tag);
	static std::vector<std::shared_ptr<GameObject>> FindGameObjectsWithLayer(const std::string & tag);
	static std::shared_ptr<GameObject> Instantiate(const std::shared_ptr<GameObject>& originalObject);
};

