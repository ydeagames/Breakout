#pragma once

// <シーン>
class Scene
{
public:
	std::unordered_multimap<std::string, std::shared_ptr<GameObject>> objects;
	std::unordered_multimap<std::string, std::weak_ptr<GameObject>> tags;
	std::unordered_multimap<std::string, std::weak_ptr<GameObject>> layers;

public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	void Update();
	void Render();
};
