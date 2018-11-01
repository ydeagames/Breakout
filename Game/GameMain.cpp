#include "GameMain.h"
#include <cmath>
#include "Paddle.h"
#include "Block.h"

// <Gameクラス>

const int Game::STAGE_DATA[3][8] = 
{
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3 },
};

// ゲームの初期化処理
Game::Game() :
	m_frame_timer(new FrameTimer),
	m_input(new InputManager),
	m_paddle(nullptr)
{
	m_paddle = new Paddle({ static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_BOTTOM) - 20.f },
		m_input->GetInput<JoypadInput>("Joypad")->GetInputButton(PAD_INPUT_LEFT),
		m_input->joypad->GetInputButton(PAD_INPUT_RIGHT));

	const float width = SCREEN_WIDTH / 8;
	const float height = width / 4;

	for (int iy = 0; iy < 3; iy++)
	{
		for (int ix = 0; ix < 8; ix++)
		{
			int type = STAGE_DATA[iy][ix];
			if (type != 0)
			{
				m_blocks.emplace_back(
					Vec2{ ix * width + width / 2, iy * height + height / 2 },
					Vec2{ width, height }, type);
			}
		}
	}
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
	DrawFormatString(10, 10, Colors::White, "FPS = %f", m_frame_timer->GetFrameRate());
	m_paddle->Render();

	for (auto itr = m_blocks.begin(); itr != m_blocks.end(); ++itr) {
		itr->Render();
	}
}
