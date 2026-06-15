#pragma once

#include "Scene.h"
#include "singleton.h"

class SceneManager
{
#pragma region 変数
private:
	SCENE m_currentScene;
	std::unique_ptr<Scene> m_scene;

	SCENE m_nextScene;              // ★ 追加
	SceneBase* m_loadingTarget;     // ★ 追加
	bool m_isLoading = false;       // ★ 追加
	bool m_loaded = false;   // ★ 追加

public:
	// シーン共通で使用
	//int score;	
#pragma endregion

#pragma region 関数
private:

public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void ChangeScene();

	std::string GetSceneName(SCENE _scene) { return m_scene->GetSceneName(_scene); }
	std::vector<std::string>& GetSceneNameAll() { return m_scene->GetSceneNameAll(); }
	SceneBase* GetCurrentScene()
	{
		return m_scene->GetScene(m_currentScene);
	}

	// 以下、Loading用
	void ChangeSceneWithLoading(SCENE next);
	void CommitLoadedScene();
	bool IsLoading() const { return m_isLoading; }

#pragma endregion
};

#define SCENE_MANAGER Singleton<SceneManager>::GetInstance()
