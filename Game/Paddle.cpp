#include "Paddle.h"

Paddle::Paddle(const Vec2& default_position, const InputButton& key_left, const InputButton& key_right) :
	m_position(default_position),
	m_velocity(),
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
		m_velocity.x += -1;
	if (m_key_right.GetButton())
		m_velocity.x += 1;
	m_position += m_velocity;
}

void Paddle::Render()
{
	DrawBoxAA(m_position.x - 10, m_position.y - 2, m_position.x + 10, m_position.y + 2, COLOR_YELLOW, true);
}