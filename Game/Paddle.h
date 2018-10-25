#pragma once
class Paddle
{
private:
	Vec2 m_position;
	Vec2 m_velocity;
	InputButton m_key_left;
	InputButton m_key_right;
public:
	Paddle(const Vec2& default_position, const InputButton& key_left, const InputButton& key_right);
	~Paddle();

	void Update();
	void Render();
};

