#include "GameMain.h"
#include <cmath>
#include "TitleScene.h"
#include "PlayScene.h"

// <GameƒNƒ‰ƒX>

// ƒQ[ƒ€‚Ì‰Šú‰»ˆ—
Game::Game() :
	m_frame_timer(new FrameTimer)
{
	SceneManager& scene_manager = SceneManager::GetInstance();

	scene_manager.AddScene(SceneID::SCENE_TITLE, TitleScene::Create);
	scene_manager.AddScene(SceneID::SCENE_TITLE, PlayScene::Create);

	scene_manager.SetStartScene(SceneID::SCENE_TITLE);
}

// ƒQ[ƒ€‚ÌI—¹ˆ—
Game::~Game()
{
	delete m_frame_timer;
}

// ƒQ[ƒ€‚ÌXVˆ—
void Game::Update(void)
{
	m_frame_timer->Update();
}

// ƒQ[ƒ€‚Ì•`‰æˆ—
void Game::Render(void)
{
	DrawFormatString(10, 10, Colors::White, "FPS = %f", m_frame_timer->GetFrameRate());
}
