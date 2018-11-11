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
	auto t = gameObject->transform();
	Dimension box = { Vec2{}, Vec2{ 1, 1 } };
	box.pos += t->position;
	box.size *= t->scale;

	// TODO “§–¾“x
	if (material.base_transparency > 0)
		DrawBoxAA(box.GetX(HorizontalSide::LEFT), box.GetY(VerticalSide::TOP), box.GetX(HorizontalSide::RIGHT), box.GetY(VerticalSide::BOTTOM), material.base_color, true);
	if (material.edge_transparency > 0)
		DrawBoxAA(box.GetX(HorizontalSide::LEFT), box.GetY(VerticalSide::TOP), box.GetX(HorizontalSide::RIGHT), box.GetY(VerticalSide::BOTTOM), material.edge_color, false, material.edge_thickness);
}

void CircleRenderer::Render()
{
	auto t = gameObject->transform();
	Dimension box = { Vec2{}, Vec2{ 1, 1 } };
	box.pos += t->position;
	box.size *= t->scale;

	// TODO “§–¾“x
	if (material.base_transparency > 0)
		DrawOvalAA(box.GetX(HorizontalSide::LEFT), box.GetY(VerticalSide::TOP), box.GetX(HorizontalSide::RIGHT), box.GetY(VerticalSide::BOTTOM), material.base_color, true);
	if (material.edge_transparency > 0)
		DrawOvalAA(box.GetX(HorizontalSide::LEFT), box.GetY(VerticalSide::TOP), box.GetX(HorizontalSide::RIGHT), box.GetY(VerticalSide::BOTTOM), material.edge_color, false, material.edge_thickness);
}

void LineRenderer::Render()
{
}
