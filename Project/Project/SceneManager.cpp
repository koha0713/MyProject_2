#include "SceneManager.h"
#include "SceneClassFactory.h"

static void ApplySceneChange(
	std::unique_ptr<IScene>& current,
	SceneID& currentID,
	SceneID& nextID)
{
	if (nextID == SceneID::None)
		return;

	// Œ»ÝScene”jŠü
	if (current)
	{
		current->UnInit();
		current.reset();
	}

	// VScene¶¬
	current =
		SceneClassFactory::GetInstance().Create(nextID);

	current->Init();

	currentID = nextID;
	nextID = SceneID::None;
}

void SceneManager::RequestScene(SceneID id)
{
	m_nextID = id;
}

void SceneManager::Init()
{

}

// “o˜^‚³‚ê‚Ä‚¢‚éƒV[ƒ“‚ð‘S‚Ä”jŠü‚·‚é
void SceneManager::UnInit()
{
	if (m_currentScene)
	{
		m_currentScene->UnInit();
		m_currentScene.reset();
	}

	m_currentID = SceneID::None;
	m_nextID = SceneID::None;
}

void SceneManager::Draw(uint64_t deltatime)
{
	if(m_currentScene)
		m_currentScene->Draw(deltatime);
}

void SceneManager::Update(uint64_t deltatime)
{
	ApplySceneChange(
		m_currentScene,
		m_currentID,
		m_nextID);

	if (m_currentScene)
		m_currentScene->Update(deltatime);
}