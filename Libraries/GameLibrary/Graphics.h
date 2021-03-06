#pragma once
#include "Vec2.h"
#include "Shape.h"

namespace Graphics
{
	// <ベクトルを描画>
	int DrawVector(const Vec2& vector, const Vec2& base, Color color, float Thickness = 1.f);

	// 回転直方体
	int DrawBoxRotate(const Box& box, unsigned int Color, int FillFlag, float LineThickness = 1.0f);
}