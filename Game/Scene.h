#pragma once

// <シーン>
class Scene
{
public:
	std::vector<GameObject> objects;

public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	void Update();
	void Render();

	void Add
};
