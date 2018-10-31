#pragma once

class Block
{
private:
	Vec2 pos;
	Vec2 size;
	int color;
public:
	Block(Vec2 pos, Vec2 size, int color = COLOR_WHITE);
	Block();
	~Block();

	void Render();
};

