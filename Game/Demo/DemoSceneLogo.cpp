#include "DemoSceneLogo.h"

DemoSceneLogo::DemoSceneLogo()
	: Scene()
{
	// �C�x���g�I�u�W�F�N�g
	auto evnt = GameObject::Create("Event");
	class TimerScript : public Component
	{
	private:
		Timer timer;

	public:
		void Start()
		{
			timer = Timer{}.SetRemaining(3).Resume();
		}

		void Update()
		{
			if (timer.IsFinished())
				SceneManager::GetInstance().RequestScene(SceneID::PLAY);
		}
	};
	evnt->AddNewComponent<TimerScript>();
	class ClickScript : public Component
	{
	public:
		void Update()
		{
			if (InputManager::GetInstance().key->GetButtonDown(KEY_INPUT_LEFT))
				SceneManager::GetInstance().RequestScene(SceneID::TITLE);
		}
	};
	evnt->AddNewComponent<ClickScript>();

	// ���x���I�u�W�F�N�g
	auto label = GameObject::Create("Label");
	label->transform()->position.y += 50;
	label->AddNewComponent<TextRenderer>("���S�V�[�� (3�b�o�߁�Play, ���L�[��Title)");
}

DemoSceneLogo::~DemoSceneLogo()
{
}
