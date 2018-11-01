#include "Block.h"

const Color Block::COLORS[4] =
{
	Colors::Black,
	Colors::Red,
	Colors::Green,
	Colors::Blue,
};

Block::Block(Vec2 pos, Vec2 size, int type) :
	pos(pos),
	size(size),
	color(COLORS[type])
{
}

Block::~Block()
{
}

void Block::Render()
{
	DrawBoxAA(pos.x - size.x / 2, pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2, color, false);
}