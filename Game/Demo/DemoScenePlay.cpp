#include "DemoScenePlay.h"

DemoScenePlay::DemoScenePlay()
	: Scene()
{
	// �C�x���g�I�u�W�F�N�g
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
	label->AddNewComponent<TextRenderer>("�v���C�V�[�� (�E�L�[��Title)");
}

DemoScenePlay::~DemoScenePlay()
{
}
