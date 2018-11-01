#include "Paddle.h"

Paddle::Paddle(const Vec2& default_position, const InputButton& key_left, const InputButton& key_right) :
	m_position(default_position),
	m_key_left(key_left),
	m_key_right(key_right)
{
}

Paddle::~Paddle()
{
}

void Paddle::Update()
{
	m_velocity = {};
	if (m_key_left.GetButton())
		m_velocity.x += -8;
	if (m_key_right.GetButton())
		m_velocity.x += 8;
	m_position += m_velocity;
}

void Paddle::Render()
{
	DrawBoxAA(m_position.x - 40, m_position.y - 8, m_position.x + 40, m_position.y + 8, Colors::Yellow, true);
}