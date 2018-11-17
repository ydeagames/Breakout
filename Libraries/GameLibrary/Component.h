#pragma once

class GameObject;
class Component
{
public:
	GameObject* gameObject;

public:
	virtual ~Component() {}

public:
	virtual void Start() {}
	virtual void Update() {}
	virtual void Render() {}
};