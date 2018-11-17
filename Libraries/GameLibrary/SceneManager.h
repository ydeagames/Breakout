﻿#pragma once

// シーンID
enum class SceneID
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_PLAY,
};

class Scene;

// <シーン管理>
class SceneManager final : public Singleton<SceneManager>
{
	// エイリアス宣言
	using FactoryMethod = std::shared_ptr<Scene>(*)();

private:
	std::shared_ptr<Scene>	m_active_scene;     // 活動中のシーン
	SceneID					m_next_scene_id;    // 変更予定のシーンのID
	std::unordered_map<SceneID, FactoryMethod> m_scene_factory_methods;    // 各シーンのファクトリメソッド

private:
	std::queue<std::pair<std::string, std::shared_ptr<GameObject>>> addingObjects;

private:
	SceneManager();
	friend class Singleton<SceneManager>;

public:
	void AddScene(SceneID scene_id, FactoryMethod factory_method);    // シーンの追加
	void SetStartScene(SceneID scene_id);    // 開始シーンの設定

	void UpdateActiveScene();    // 活動中のシーンの更新
	void RenderActiveScene();    // 活動中のシーンの描画

	void RequestScene(SceneID scene_id);    // シーン変更の要求

	std::shared_ptr<Scene> GetActiveScene();

	void AddObject(const std::shared_ptr<GameObject>& object);

private:
	void ChangeScene(SceneID scene_id);    // シーン変更
};

// マクロの定義
//#define TheSceneManager SceneManager::GetInstance()