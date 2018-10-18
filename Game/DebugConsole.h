#pragma once

#include "GameObject.h"
#include "GameTimer.h"
#include <deque>

// 構造体の宣言 ============================================================

// <デバッグコンソール>
typedef struct
{
	char msg[64];
	GameTimer timer;
} DebugConsoleLine;

// <デバッグコンソール>
typedef struct
{
	GameObject area;	// エリア
	HFNT font;			// フォント
	float line_height;	// 位置行の高さ
	std::deque<DebugConsoleLine> lines;
} DebugConsole;

// 定数の定義 ==============================================================

// 関数の宣言 ==============================================================

// <<デバッグコンソール> --------------------------------------------------

// <デバッグコンソール作成>
DebugConsole DebugConsole_Create(GameObject area, HFNT font, float line_height);

// <デバッグコンソールログ>
void DebugConsole_Log(DebugConsole* console, char* log);

// <デバッグコンソールログフォーマット>
void DebugConsole_LogF(DebugConsole* console, char* format, ...);

// <デバッグコンソール描画>
void DebugConsole_Render(DebugConsole* console);
