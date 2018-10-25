#pragma once

// �O���t�B�b�N�n���h��   
using HGRP = int;
// �T�E���h�n���h��
using HSND = int;
// �t�H���g�n���h��
using HFNT = int;
// �l�b�g���[�N�n���h�� 
using HNET = int;

// <�F�R�[�h(�W���J���[16�F)>
enum ColorCode : unsigned int
{
	COLOR_BLACK   = 0xFF000000,    // ���F
	COLOR_NAVY    = 0xFF000080,    // �Z���F
	COLOR_GREEN   = 0xFF008000,    // �ΐF
	COLOR_TEAL    = 0xFF008080,    // �ΐF
	COLOR_MAROON  = 0xFF800000,    // �}���[���F
	COLOR_PURPLE  = 0xFF800080,    // ���F
	COLOR_OLIVE   = 0xFF808000,    // �I���[�u�F
	COLOR_GRAY    = 0xFF808080,    // �D�F
	COLOR_SILVER  = 0xFFC0C0C0,    // ��F
	COLOR_BLUE    = 0xFF0000FF,    // �F
	COLOR_LIME    = 0xFF00FF00,    // ���C���O���[���F
	COLOR_AQUA    = 0xFF00FFFF,    // ���F
	COLOR_RED     = 0xFFFF0000,    // �ԐF
	COLOR_FUCHSIA = 0xFFFF00FF,    // �Ԏ��F
	COLOR_YELLOW  = 0xFFFFFF00,    // ���F
	COLOR_WHITE   = 0xFFFFFFFF,    // ���F
};

// <�}�`�`��֘A>
namespace DrawUtils
{
	// �j����`��
	int DrawDashedLine(int x1, int y1, int x2, int y2, unsigned int color, int length, int thickness = 1);

	// �j����`��(�A���`�G�C���A�X���ʕt��)
	int DrawDashedLineAA(float x1, float y1, float x2, float y2, unsigned int color, float length, float thickness = 1.0f);

	// �J�v�Z����`��
	int DrawCapsule(int x1, int y1, int x2, int y2, int r, unsigned int color, int thickness = 1);

	// �J�v�Z����`��(�A���`�G�C���A�X���ʕt��)
	int DrawCapsuleAA(float x1, float y1, float x2, float y2, float r, unsigned int color, float thickness = 1.0f);
}