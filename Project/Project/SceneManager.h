#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "noncopyable.h"
#include "SceneID.h"

//====================
// 前方宣言
//====================
class IScene;

class SceneManager : NonCopyable
{
	static inline std::unique_ptr<IScene> m_currentScene{};
	static inline SceneID m_currentID = SceneID::None;
	static inline SceneID m_nextID = SceneID::None;

public:
	static void RequestScene(const SceneID id);

	static SceneID GetCurrentSceneID()
	{
		return m_currentID;
	}

	static IScene* GetCurrentScene()
	{
		return m_currentScene.get();
	}

	//====================
	// ライフサイクル
	//====================
	static void Init();
	static void UnInit();
	static void Update(uint64_t deltatime);
	static void Draw(uint64_t deltatime);

};