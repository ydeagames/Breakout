#include "ComponentContainer.h"

ComponentContainer& ComponentContainer::operator=(const ComponentContainer & container)
{
	components.clear();
	for (auto& entry : container.components)
	{
		entry.second->gameObject = nullptr;
		components.insert(std::make_pair(entry.first, entry.second));
	}
	return *this;
}

void ComponentContainer::Update()
{
	for (auto& entry : components)
		if (entry.second && entry.second->gameObject != gameObject)
		{
			entry.second->gameObject = gameObject;
			entry.second->Start();
		}

	for (auto& entry : components)
		if (entry.second)
			entry.second->Update();
}

void ComponentContainer::Render()
{
	for (auto& entry : components)
		if (entry.second)
			entry.second->Render();
}
