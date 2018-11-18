#include "DemoSceneLogo.h"

DemoSceneLogo::DemoSceneLogo()
	: Scene()
{
	// イベントオブジェクト
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

	// ラベルオブジェクト
	auto label = GameObject::Create("Label");
	label->transform()->position.y += 50;
	label->AddNewComponent<TextRenderer>("ロゴシーン (3秒経過→Play, 左キー→Title)");
}

DemoSceneLogo::~DemoSceneLogo()
{
}
