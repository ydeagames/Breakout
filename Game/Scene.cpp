#include "Scene.h"

void Scene::Update()
{
	for (auto itr = objects.begin(); itr != objects.end();)
	{
		itr->Update();
		if (!itr->IsDestroyed())
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
		object.Render();
}