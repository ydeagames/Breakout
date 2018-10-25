#include "GameMain.h"
#include <cmath>

// <Game�N���X>

// �Q�[���̏���������
Game::Game() :
	m_frame_timer(nullptr),
	m_input(nullptr)
{
	m_frame_timer = new FrameTimer;
	m_input = new InputManager;
	m_pos = { SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2 };
	m_vel = { 0, 0 };
}

// �Q�[���̏I������
Game::~Game()
{
	delete m_frame_timer;
	delete m_input;
}

// �Q�[���̍X�V����
void Game::Update(void)
{
	m_frame_timer->Update();
	m_input->Update();

	m_vel.y = 0;
	if (m_input->joypad.GetButton(PAD_INPUT_UP))
		m_vel.y -= 1;
	if (m_input->joypad.GetButton(PAD_INPUT_DOWN))
		m_vel.y += 1;
	m_vel.x = 0;
	if (m_input->joypad.GetButton(PAD_INPUT_LEFT))
		m_vel.x -= 1;
	if (m_input->joypad.GetButton(PAD_INPUT_RIGHT))
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

// �Q�[���̕`�揈��
void Game::Render(void)
{
	DrawFormatString(10, 10, COLOR_WHITE, "FPS = %f", m_frame_timer->GetFrameRate());
	DrawCircleAA(m_pos.x, m_pos.y, 20, 32, COLOR_WHITE, true);
}
