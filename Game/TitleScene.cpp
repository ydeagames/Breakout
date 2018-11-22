#include "TitleScene.h"
#include "GameMain.h"

// <シーン>

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
	title->AddNewComponent<TextRenderer>("360°ブロック崩し");

	auto text1 = GameObject::Create();
	text1->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 10 };
	text1->AddNewComponent<TextRenderer>("矢印キーやWASDキーでパドル移動！");
	auto text2 = GameObject::Create();
	text2->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 25 };
	text2->AddNewComponent<TextRenderer>("マウス横移動やQEキーでパドル回転！");
	auto text3 = GameObject::Create();
	text3->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 40 };
	text3->AddNewComponent<TextRenderer>("パドルがブロックに触れると即死");
	auto text4 = GameObject::Create();
	text4->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 55 };
	text4->AddNewComponent<TextRenderer>("30秒以内にスコアを稼げ！");
	auto text5 = GameObject::Create();
	text5->transform()->position = SCREEN.GetCenter() + Vec2{ -150, 70 };
	text5->AddNewComponent<TextRenderer>("クリックかスペースキーでスタート！");

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
