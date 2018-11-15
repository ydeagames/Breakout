#include "ComponentContainer.h"

void ComponentContainer::Update()
{
	for (auto entry : components)
		if (entry.second)
			entry.second->Update();
}

void ComponentContainer::Render()
{
	for (auto entry : components)
		if (entry.second)
			entry.second->Render();
}
