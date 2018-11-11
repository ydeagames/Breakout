#pragma once
#include "Vec2.h"

class Transform final
{
public:
	Vec2 position;				// <テクスチャ>
	float rotation;				// <回転>
	float scale;				// <スケール>

public:
	Transform(const Vec2& position, float rotation, float scale);

	Transform();
};
