#include "TitleScene.h"
#include "GameMain.h"

// <�V�[��>

TitleScene::TitleScene()
	: Scene()
{
	SetMouseDispFlag(true);

	auto obj = GameObject::Create();
	obj->transform()->position = SCREEN.Expand(-200).GetCenter();
	obj->transform()->scale = SCREEN.Expand(-200).GetSize();
	auto renderer = std::make_shared<BoxRenderer>();
	renderer->material = Material{}.SetBase(Colors::Blue, .2f).SetBorder(Colors::White, 1.f, .5f);
	obj->AddComponent<BoxRenderer>(renderer);

	auto title = GameObject::Create("Title");
	title->transform()->position = SCREEN.GetCenter() + Vec2{ -100, -30 };
	title->AddNewComponent<TextRenderer>("360���u���b�N����");

	auto text1 = GameObject::Create();
	text1->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 10 };
	text1->AddNewComponent<TextRenderer>("���L�[��WASD�L�[�Ńp�h���ړ��I");
	auto text2 = GameObject::Create();
	text2->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 25 };
	text2->AddNewComponent<TextRenderer>("�}�E�X���ړ���QE�L�[�Ńp�h����]�I");
	auto text3 = GameObject::Create();
	text3->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 40 };
	text3->AddNewComponent<TextRenderer>("�p�h�����u���b�N�ɐG���Ƒ���");
	auto text4 = GameObject::Create();
	text4->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 55 };
	text4->AddNewComponent<TextRenderer>("30�b�ȓ��ɃX�R�A���҂��I");
	auto text5 = GameObject::Create();
	text5->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 70 };
	text5->AddNewComponent<TextRenderer>("�N���b�N���X�y�[�X�L�[�ŃX�^�[�g�I");

	auto director = GameObject::Create("GameDirector");
	class GameDirector : public Component
	{
		void Update()
		{
			if (InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_1) || InputManager::GetInstance().key->GetButtonDown(KEY_INPUT_SPACE))
				SceneManager::GetInstance().RequestScene(SceneID::PLAY);
		}
	};
	director->AddNewComponent<GameDirector>();
}

TitleScene::~TitleScene()
{

}
