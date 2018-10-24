#include "GameMain.h"
#include <cmath>

// <GameƒNƒ‰ƒX>

// ƒQ[ƒ€‚Ì‰Šú‰»ˆ—
Game::Game() :
	m_frame_timer(nullptr),
	m_joypad(nullptr)
{
	m_frame_timer = new FrameTimer;
	m_joypad = new JoypadInput;
	m_pos = { SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2 };
	m_vel = { 0, 0 };
}

// ƒQ[ƒ€‚ÌI—¹ˆ—
Game::~Game()
{
	delete m_frame_timer;
	delete m_joypad;
}

// ƒQ[ƒ€‚ÌXVˆ—
void Game::Update(void)
{
	m_frame_timer->Update();
	m_joypad->Update();

	m_vel.y = 0;
	if (m_joypad->GetButton(PAD_INPUT_UP))
		m_vel.y -= 1;
	if (m_joypad->GetButton(PAD_INPUT_DOWN))
		m_vel.y += 1;
	m_vel.x = 0;
	if (m_joypad->GetButton(PAD_INPUT_LEFT))
		m_vel.x -= 1;
	if (m_joypad->GetButton(PAD_INPUT_RIGHT))
		m_vel.x += 1;

	float length = std::sqrtf(m_vel.x*m_vel.x + m_vel.y*m_vel.y);
	if (length > 0)
	{
		m_vel.x *= SPEED / length;
		m_vel.y *= SPEED / length;
	}

	m_pos.x += m_vel.x;
	m_pos.y += m_vel.y;
}

// ƒQ[ƒ€‚Ì•`‰æˆ—
void Game::Render(void)
{
	DrawFormatString(10, 10, COLOR_WHITE, "FPS = %f", m_frame_timer->GetFrameRate());
	DrawCircleAA(m_pos.x, m_pos.y, 20, 32, COLOR_WHITE, true);
}
