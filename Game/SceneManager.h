#pragma once

// シーンID
enum SceneID
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_PLAY,

	NUM_SCENES
};

class Scene;

// <シーン管理>
class SceneManager
{
	// エイリアス宣言
	using FactoryMethod = Scene*(*)();

	// 静的メンバ関数の宣言
	public:
		static SceneManager* GetInstance();    // シーン管理オブジェクトの取得

	// データメンバの宣言
	private:
		Scene*        m_active_scene;     // 活動中のシーン
		SceneID       m_next_scene_id;    // 変更予定のシーンのID
		FactoryMethod m_scene_factory_methods[NUM_SCENES];    // 各シーンのファクトリメソッド

	// メンバ関数の宣言
	private:
		// コンストラクタ
		SceneManager();

	public:
		// デストラクタ
		virtual ~SceneManager();

	public:
		// 操作
		void AddScene(SceneID scene_id, FactoryMethod factory_method);    // シーンの追加
		void SetStartScene(SceneID scene_id);    // 開始シーンの設定

		void UpdateActiveScene();    // 活動中のシーンの更新
		void RenderActiveScene();    // 活動中のシーンの描画

		void RequestScene(SceneID scene_id);    // シーン変更の要求


	private:
		// 内部実装
		void ChangeScene(SceneID scene_id);    // シーン変更


		// 複製の禁止
		SceneManager(const SceneManager&) = delete;               // コピーコンストラクタの削除
		SceneManager& operator=(const SceneManager&) = delete;    // 代入演算子の削除
		SceneManager(SceneManager&&) = delete;                    // ムーブコンストラクタの削除
		SceneManager& operator=(SceneManager&&) = delete;         // ムーブ代入演算子の削除
};

// マクロの定義
//#define TheSceneManager SceneManager::GetInstance()