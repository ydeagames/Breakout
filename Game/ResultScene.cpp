#include "ResultScene.h"
#include "GameMain.h"
#include "Score.h"

// <�V�[��>

ResultScene::ResultScene()
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

	if (Score::GetInstance().alive)
	{
		auto text1 = GameObject::Create();
		text1->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 10 };
		text1->AddNewComponent<TextRenderer>("�N���A");
		auto text2 = GameObject::Create();
		text2->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 25 };
		text2->AddNewComponent<TextRenderer>("�X�R�A: " + std::to_string(Score::GetInstance().score));
		auto text5 = GameObject::Create();
		text5->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 55 };
		text5->AddNewComponent<TextRenderer>("�N���b�N���X�y�[�X�L�[�Ń^�C�g���ցI");
	}
	else
	{
		auto text3 = GameObject::Create();
		text3->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 10 };
		text3->AddNewComponent<TextRenderer>("���S");
		auto text4 = GameObject::Create();
		text4->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 25 };
		text4->AddNewComponent<TextRenderer>("�c�莞��: " + std::to_string(Score::GetInstance().timer.GetRemaining()));
		auto text5 = GameObject::Create();
		text5->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 55 };
		text5->AddNewComponent<TextRenderer>("�N���b�N���X�y�[�X�L�[�Ń^�C�g���ցI");
	}

	auto director = GameObject::Create("GameDirector");
	class GameDirector : public Component
	{
		void Update()
		{
			if (InputManager::GetInstance().mouse->GetButtonDown(MOUSE_INPUT_1) || InputManager::GetInstance().key->GetButtonDown(KEY_INPUT_SPACE))
				SceneManager::GetInstance().RequestScene(SceneID::TITLE);
		}
	};
	director->AddNewComponent<GameDirector>();
}

ResultScene::~ResultScene()
{

}
