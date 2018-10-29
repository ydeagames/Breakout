#include "GameMain.h"
#include <cmath>
#include "Paddle.h"

// <Gameクラス>

// ゲームの初期化処理
Game::Game() :
	m_frame_timer(new FrameTimer),
	m_input(new InputManager),
	m_paddle(nullptr)
{
	m_paddle = new Paddle({ static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_BOTTOM) - 20.f},
		m_input->GetInput<JoypadInput>("Joypad")->GetInputButton(PAD_INPUT_LEFT),
		m_input->joypad->GetInputButton(PAD_INPUT_RIGHT));
}

// ゲームの終了処理
Game::~Game()
{
	delete m_frame_timer;
	delete m_input;
	delete m_paddle;
}

// ゲームの更新処理
void Game::Update(void)
{
	m_frame_timer->Update();
	m_input->Update();
	m_paddle->Update();
}

// ゲームの描画処理
void Game::Render(void)
{
	DrawFormatString(10, 10, COLOR_WHITE, "FPS = %f", m_frame_timer->GetFrameRate());
	m_paddle->Render();
}
