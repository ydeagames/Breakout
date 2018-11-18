#include "DemoScenePlay.h"

DemoScenePlay::DemoScenePlay()
	: Scene()
{
	// イベントオブジェクト
	auto evnt = GameObject::Create("Event");
	class ClickScript : public Component
	{
	public:
		void Update()
		{
			if (InputManager::GetInstance().key->GetButtonDown(KEY_INPUT_RIGHT))
				SceneManager::GetInstance().RequestScene(SceneID::LOGO);
		}
	};
	evnt->AddNewComponent<ClickScript>();

	auto label = GameObject::Create("Label");
	label->transform()->position.y += 50;
	label->AddNewComponent<TextRenderer>("プレイシーン (右キー→Title)");
}

DemoScenePlay::~DemoScenePlay()
{
}
