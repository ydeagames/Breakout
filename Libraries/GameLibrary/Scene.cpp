#include "Scene.h"

void Scene::Update()
{
	for (auto& object : objects)
		object.second->Start();
	for (auto itr = objects.begin(); itr != objects.end();)
	{
		itr->second->Update();
		if (itr->second->IsDestroyed())
		{
			itr = objects.erase(itr);
			continue;
		}
		++itr;
	}
}

void Scene::Render()
{
	for (auto& object : objects)
		object.second->Render();
}
