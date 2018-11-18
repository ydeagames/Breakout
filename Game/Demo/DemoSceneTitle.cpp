#include "DemoSceneTitle.h"

DemoSceneTitle::DemoSceneTitle()
	: Scene()
{
	// �C�x���g�I�u�W�F�N�g
	auto evnt = GameObject::Create("Event");
	// TODO �p���^���e�̕���GetComponent�ł���悤��
	class TimerScript : public Component
	{
	private:
		Timer timer;

	public:
		void Start()
		{
			timer = Timer{}.SetRemaining(2).Resume();
		}

		void Update()
		{
			if (timer.IsFinished())
				SceneManager::GetInstance().RequestScene(SceneID::LOGO);
		}
	};
	evnt->AddNewComponent<TimerScript>();

	auto label = GameObject::Create("Label");
	label->transform()->position.y += 50;
	label->AddNewComponent<TextRenderer>("�^�C�g���V�[�� (2�b�o�߁�Logo)");
}

DemoSceneTitle::~DemoSceneTitle()
{
}
