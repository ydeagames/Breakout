// @file   GameMain.h
//
// @brief  ゲーム関連のヘッダファイル
//
// @date   日付
//
// @author 制作者名

#pragma once
#include <vector>

// <システム>

// ゲームタイトル
const char* const GAME_TITLE = "Sample Game";

// <画面>

// 画面のサイズ[pixel]
const Vec2 SCREEN_SIZE = { 800, 800 };

// 画面
const Bounds SCREEN = { SCREEN_SIZE / 2, SCREEN_SIZE };

// <ゲーム>
class Game
{
private:
	FrameTimer* m_frame_timer;

public:
	Game();
	~Game();

	void Update(void);
	void Render(void);
};
