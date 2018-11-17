#include "GameMain.h"
#include <cmath>
#include "TitleScene.h"
#include "PlayScene.h"

// <Gameクラス>

// ゲームの初期化処理
Game::Game() :
	m_frame_timer(new FrameTimer)
{
	SceneManager& scene_manager = SceneManager::GetInstance();

	scene_manager.AddScene(SceneID::SCENE_TITLE, TitleScene::Create);
	scene_manager.AddScene(SceneID::SCENE_TITLE, PlayScene::Create);

	scene_manager.SetStartScene(SceneID::SCENE_TITLE);
}

// ゲームの終了処理
Game::~Game()
{
	delete m_frame_timer;
}

// ゲームの更新処理
void Game::Update(void)
{
	m_frame_timer->Update();
}

// ゲームの描画処理
void Game::Render(void)
{
	DrawFormatString(10, 10, Colors::White, "FPS = %f", m_frame_timer->GetFrameRate());
}
