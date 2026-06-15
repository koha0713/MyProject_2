#include "SceneManager.h"

#include <memory>

void SceneManager::Init()
{
	// シーンを設定
	m_scene = std::make_unique<Scene>();
	m_currentScene = m_scene->GetStartScene();

	// 初期シーンの初期化処理
	m_scene->GetScene(m_currentScene)->Init();
}

void SceneManager::UnInit()
{
	// 最終シーンの後処理
	if (m_scene->GetScene(m_currentScene)->IsInitialized())
	{
		m_scene->GetScene(m_currentScene)->UnInit();
	}
}

void SceneManager::Update()
{
	if (m_isLoading)
	{
		// 裏Init（1回だけ）
		if (!m_loadingTarget->IsInitialized())
		{
			m_loadingTarget->Init();
		}
		else
		{
			CommitLoadedScene();
		}
	}

	m_scene->GetScene(m_currentScene)->Update();
}

void SceneManager::Draw()
{
	// 頂点情報設定から描画まで		
	m_scene->GetScene(m_currentScene)->Draw();
}

// 各シーンからシーン変更通知を受け取った
void SceneManager::ChangeScene()
{
	SCENE next = (SCENE)m_scene->GetScene(m_currentScene)->GetNextScene();
	if (next == SCENE_NONE) return;

	// 現シーンの終了処理
	m_scene->GetScene(m_currentScene)->UnInit();

	// 次シーンに切り替え
	m_currentScene = next;

	// シーン開始
	m_scene->GetScene(m_currentScene)->Init();

}

// 以下、Loading用
void SceneManager::ChangeSceneWithLoading(SCENE next)
{
	if (m_isLoading) return;

	m_nextScene = next;
	m_isLoading = true;

	// 表示は Loading に切り替え
	m_scene->GetScene(m_currentScene)->UnInit();
	m_currentScene = SCENE_LOADING;
	m_scene->GetScene(m_currentScene)->Init();

	// 裏で初期化するSceneを取得
	m_loadingTarget = m_scene->GetScene(next);
}

void SceneManager::CommitLoadedScene()
{
	if (!m_isLoading || !m_loadingTarget) return;

	// Loadingを終了
	m_scene->GetScene(m_currentScene)->UnInit();

	// 本Sceneへ
	m_currentScene = m_nextScene;

	m_isLoading = false;
	m_loadingTarget = nullptr;
}
