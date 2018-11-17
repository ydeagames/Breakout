#pragma once

// <シーン>
class Scene
{
public:
	std::unordered_multimap<std::string, std::shared_ptr<GameObject>> objects;

public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	void Update();
	void Render();
};
