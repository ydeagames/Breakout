#pragma once
class Ball
{
private:
	Dimension rect;
	Vec2 vel;


public:
	Ball(Dimension rect);

public:
	void Update();
	void Render();
};

