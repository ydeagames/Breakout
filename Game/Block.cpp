#include "Block.h"

Block::Block(Vec2 pos, Vec2 size, int color) :
	pos(pos),
	size(size),
	color(color)
{
}

Block::~Block()
{
}

void Block::Render()
{
	DrawBox(pos.x - size.x / 2, pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2, color, false);
}