#include "Game\GameMain.h"
#include "Resources\Icon\Icon.h"

// �v���O�����̃G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���g�p�����̌x���΍�
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

#if defined(_DEBUG)
	// �������[���[�N���o�@�\�̃Z�b�g�A�b�v
	SetUpMemoryLeakDetector();
#endif

	// �f�o�b�O���p���O�t�@�C���̏o�̗͂}��
	SetOutApplicationLogValidFlag(FALSE);

	// �N�����[�h�̐ݒ�
#if defined(_DEBUG)
// �E�C���h�E���[�h�Ŏ��s
	ChangeWindowMode(TRUE);
	// �E�C���h�E�^�C�g���̐ݒ�
	SetMainWindowText(GAME_TITLE);
	// �E�C���h�E�A�C�R���̐ݒ�
	SetWindowIconID(IDI_ICON1);
#else
// �t���X�N���[���Ŏ��s
	ChangeWindowMode(FALSE);
#endif

	// ������Ԃ̉�ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	// DX���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// �`���𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[���̏���

	// �Q�[���̏���������
	Game* game = new Game;

	while (!ProcessMessage() && !CheckHitKey(EXIT_KEY))
	{
		// �Q�[���̍X�V����
		game->Update();
		// �Q�[���̕`�揈��
		game->Render();

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
		// ����ʂ̏���
		ClearDrawScreen();
	}

	// �Q�[���̏I������
	delete game;

	// DX���C�u�����̏I������
	DxLib_End();

	return 0;
}
