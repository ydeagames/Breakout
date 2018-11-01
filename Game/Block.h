#pragma once

class Block
{
private:
	static const Color COLORS[4];

private:
	Vec2 pos;
	Vec2 size;
	int color;

public:
	Block(Vec2 pos, Vec2 size, int color = Colors::White);
	~Block();

	void Render();
};

