#pragma once
#include "Component.h"
#include "Shape.h"

class Collision final : public Component
{
public:
	std::unique_ptr<Shape> shape;
	bool trigger;

public:
	Collision(std::unique_ptr<Shape>&& shape, bool trigger = false)
		: shape(std::move(shape))
		, trigger(trigger) {}
};
