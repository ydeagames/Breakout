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

	scene_manager.AddScene<TitleScene>(SceneID::SCENE_TITLE);
	scene_manager.AddScene<PlayScene>(SceneID::SCENE_PLAY);

	scene_manager.SetStartScene(SceneID::SCENE_PLAY);
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

	InputManager::GetInstance().Update();

	SceneManager::GetInstance().UpdateActiveScene();
}

// ゲームの描画処理
void Game::Render(void)
{
	DrawFormatString(10, 10, Colors::White, "FPS = %f", m_frame_timer->GetFrameRate());

	SceneManager::GetInstance().RenderActiveScene();
}
