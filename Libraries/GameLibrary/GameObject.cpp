#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

GameObject::GameObject(const std::string& name)
	: name(name)
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

std::shared_ptr<GameObject> GameObject::CreatePrefab(std::string name)
{
	auto obj = std::shared_ptr<GameObject>(new GameObject(name));
	obj->Initialize();
	return obj;
}

std::weak_ptr<GameObject> GameObject::Create(std::string name)
{
	auto object = CreatePrefab(name);
	SceneManager::GetInstance().AddObject(object);
	return object;
}

std::weak_ptr<GameObject> GameObject::Find(std::string name)
{
	return SceneManager::GetInstance().GetActiveScene()->objects.find(name)->second;
}

std::weak_ptr<GameObject> GameObject::Instantiate(const std::shared_ptr<GameObject>& originalObject)
{
	if (originalObject->IsDestroyed())
		throw std::invalid_argument("Cannot instantiate destroyed object");
	auto object = Create(originalObject->name + "(Clone)");
	*object.lock()->components = *originalObject->components;
	return object;
}
