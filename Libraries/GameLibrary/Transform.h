#pragma once
#include "Vec2.h"

class Transform final
{
public:
	Vec2 position;				// <�e�N�X�`��>
	float rotation;				// <��]>
	float scale;				// <�X�P�[��>

public:
	Transform(const Vec2& position, float rotation, float scale);

	Transform();
};
