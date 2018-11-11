#include "ComponentContainer.h"

void ComponentContainer::Update()
{
	for (auto entry : components)
		entry.second->Update();
}

void ComponentContainer::Render()
{
	for (auto entry : components)
		entry.second->Render();
}
