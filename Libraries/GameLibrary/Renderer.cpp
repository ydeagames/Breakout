#include "Renderer.h"
#include "Shape.h"

Material& Material::SetBase(Color color, float transparency)
{
	base_color = color;
	base_transparency = transparency;
	return *this;
}

Material& Material::SetBorder(Color color, float transparency, float thickness)
{
	edge_color = color;
	edge_transparency = transparency;
	edge_thickness = thickness;
	return *this;
}

void BoxRenderer::Render()
{
	auto t = gameObject().transform();
	Bounds box = Bounds{ Vec2{}, Vec2{ 1, 1 } }.Transformed(*t);

	// TODO “§–¾“x
	if (material.base_transparency > 0)
		DrawBoxAA(box.GetX(HorizontalSide::LEFT), box.GetY(VerticalSide::TOP), box.GetX(HorizontalSide::RIGHT), box.GetY(VerticalSide::BOTTOM), material.base_color, true);
	if (material.edge_transparency > 0)
		DrawBoxAA(box.GetX(HorizontalSide::LEFT), box.GetY(VerticalSide::TOP), box.GetX(HorizontalSide::RIGHT), box.GetY(VerticalSide::BOTTOM), material.edge_color, false, material.edge_thickness);
}

void CircleRenderer::Render()
{
	auto t = gameObject().transform();
	Bounds box = Bounds{ Vec2{}, Vec2{ 1, 1 } }.Transformed(*t);

	// TODO “§–¾“x
	if (material.base_transparency > 0)
		DrawOvalAA(box.GetX(HorizontalSide::LEFT), box.GetY(VerticalSide::TOP), box.GetExtents().x, box.GetExtents().y, 32, material.base_color, true);
	if (material.edge_transparency > 0)
		DrawOvalAA(box.GetX(HorizontalSide::LEFT), box.GetY(VerticalSide::TOP), box.GetExtents().x, box.GetExtents().y, 32, material.edge_color, false, material.edge_thickness);
}

void LineRenderer::Render()
{
}

TextRenderer::TextRenderer(std::string text)
	: text(text)
{
}

void TextRenderer::Render()
{
	Vec2 pos = gameObject().transform()->position;
	DrawFormatStringF(pos.x, pos.y, Colors::White, text.c_str());
}