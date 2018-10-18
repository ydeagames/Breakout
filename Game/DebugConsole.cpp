#include "DebugConsole.h"
#include "GameUtils.h"

// 定数の定義 ==============================================================

#define LINE_TIME 5.f
#define LINE_TIME_FADE 2.f

// 構造体の宣言 ============================================================

// 関数の定義 ==============================================================

// <<デバッグコンソール行> ------------------------------------------------

// <デバッグコンソール行作成>
static DebugConsoleLine DebugConsoleLine_Create(void)
{
	GameTimer timer = GameTimer_Create();
	GameTimer_SetRemaining(&timer, LINE_TIME);
	GameTimer_Resume(&timer);
	return{ "", timer };
}

// <<デバッグコンソール> --------------------------------------------------

// <デバッグコンソール作成>
DebugConsole DebugConsole_Create(GameObject area, HFNT font, float line_height)
{
	return{ area, font, line_height, {} };
}

// <デバッグコンソールログ>
void DebugConsole_Log(DebugConsole* console, char* log)
{
	DebugConsoleLine line = DebugConsoleLine_Create();
	snprintf(line.msg, 64, "%.*s", 64, log);
	console->lines.push_front(line);
}

// <デバッグコンソールログフォーマット>
void DebugConsole_LogF(DebugConsole* console, char* format, ...)
{
	DebugConsoleLine line = DebugConsoleLine_Create();
	va_list ap;
	va_start(ap, format);
	vsnprintf(line.msg, 64, format, ap);
	va_end(ap);
	console->lines.push_front(line);
}

// <デバッグコンソール描画>
void DebugConsole_Render(DebugConsole* console)
{
	float y = 0;
	for (auto itr = console->lines.begin(); itr != console->lines.end();)
	{
		if (console->area.size.y < y + console->line_height)
			break;

		if (!GameTimer_IsFinished(&itr->timer))
		{
			float opacity = GetMinF(LINE_TIME_FADE, GameTimer_GetRemaining(&itr->timer)) / LINE_TIME_FADE;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(opacity * 255));
			DrawFormatStringFToHandle(GameObject_GetX(&console->area, LEFT), GameObject_GetY(&console->area, BOTTOM, -console->line_height - y), console->area.sprite.color, console->font, itr->msg);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			++itr;
		}
		else
			itr = console->lines.erase(itr);

		y += console->line_height;
	}
}
