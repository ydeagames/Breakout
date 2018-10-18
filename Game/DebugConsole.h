#pragma once

#include "GameObject.h"
#include "GameTimer.h"
#include <deque>

// �\���̂̐錾 ============================================================

// <�f�o�b�O�R���\�[��>
typedef struct
{
	char msg[64];
	GameTimer timer;
} DebugConsoleLine;

// <�f�o�b�O�R���\�[��>
typedef struct
{
	GameObject area;	// �G���A
	HFNT font;			// �t�H���g
	float line_height;	// �ʒu�s�̍���
	std::deque<DebugConsoleLine> lines;
} DebugConsole;

// �萔�̒�` ==============================================================

// �֐��̐錾 ==============================================================

// <<�f�o�b�O�R���\�[��> --------------------------------------------------

// <�f�o�b�O�R���\�[���쐬>
DebugConsole DebugConsole_Create(GameObject area, HFNT font, float line_height);

// <�f�o�b�O�R���\�[�����O>
void DebugConsole_Log(DebugConsole* console, char* log);

// <�f�o�b�O�R���\�[�����O�t�H�[�}�b�g>
void DebugConsole_LogF(DebugConsole* console, char* format, ...);

// <�f�o�b�O�R���\�[���`��>
void DebugConsole_Render(DebugConsole* console);
