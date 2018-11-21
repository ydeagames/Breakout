#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

GameObject::GameObject(const std::string& name, const std::string& tag, const std::string& layer)
	: name(name)
	, tag(tag)
	, layer(layer)
	, components(nullptr)
	, destroyed(false)
{
}

void GameObject::Initialize()
{
	components = std::make_unique<ComponentContainer>(shared_from_this());
	AddComponent<Transform>(std::make_shared<Transform>());
}

std::shared_ptr<Transform> GameObject::transform()
{
	return GetComponent<Transform>();
}

void GameObject::Start()
{
	components->Start();
}

void GameObject::Update()
{
	components->Update();
}

void GameObject::Render()
{
	components->Render();
}

void GameObject::Destroy()
{
	destroyed = true;
}

bool GameObject::IsDestroyed()
{
	return destroyed;
}

std::shared_ptr<GameObject> GameObject::CreatePrefab(const std::string& name, const std::string& tag, const std::string& layer)
{
	auto obj = std::shared_ptr<GameObject>(new GameObject(name, tag, layer));
	obj->Initialize();
	return obj;
}

std::shared_ptr<GameObject> GameObject::Create(const std::string& name, const std::string& tag, const std::string& layer)
{
	auto object = CreatePrefab(name);
	SceneManager::GetInstance().AddObject(object);
	return object;
}

std::shared_ptr<GameObject> GameObject::Find(const std::string& name)
{
	auto range = SceneManager::GetInstance().GetActiveScene()->objects.equal_range(name);
	for (auto it = range.first; it != range.second; ++it)
	{
		if (!it->second->IsDestroyed())
			return it->second;
	}
	return nullptr;
}

std::shared_ptr<GameObject> GameObject::FindWithTag(const std::string& tag)
{
	auto& mmap = SceneManager::GetInstance().GetActiveScene()->tags;
	auto range = mmap.equal_range(tag);
	for (auto it = range.first; it != range.second;)
	{
		auto obj = it->second.lock();
		if (obj && !obj->IsDestroyed())
			return obj;
		else
		{
			it = mmap.erase(it);
			continue;
		}
		++it;
	}
	return nullptr;
}

std::vector<std::shared_ptr<GameObject>> GameObject::FindGameObjectsWithTag(const std::string& tag)
{
	std::vector<std::shared_ptr<GameObject>> result;
	auto& mmap = SceneManager::GetInstance().GetActiveScene()->tags;
	auto range = mmap.equal_range(tag);
	for (auto it = range.first; it != range.second;)
	{
		auto obj = it->second.lock();
		if (obj && !obj->IsDestroyed())
			result.push_back(obj);
		else
		{
			it = mmap.erase(it);
			continue;
		}
		++it;
	}
	return result;
}

std::vector<std::shared_ptr<GameObject>> GameObject::FindGameObjectsWithLayer(const std::string& layer)
{
	std::vector<std::shared_ptr<GameObject>> result;
	auto& mmap = SceneManager::GetInstance().GetActiveScene()->layers;
	auto range = mmap.equal_range(layer);
	for (auto it = range.first; it != range.second;)
	{
		auto obj = it->second.lock();
		if (obj && !obj->IsDestroyed())
			result.push_back(obj);
		else
		{
			it = mmap.erase(it);
			continue;
		}
		++it;
	}
	return result;
}

std::shared_ptr<GameObject> GameObject::Instantiate(const std::shared_ptr<GameObject>& originalObject)
{
	if (originalObject->IsDestroyed())
		throw std::invalid_argument("Cannot instantiate destroyed object");
	auto object = Create(originalObject->name + "(Clone)");
	*object->components = *originalObject->components;
	return object;
}
