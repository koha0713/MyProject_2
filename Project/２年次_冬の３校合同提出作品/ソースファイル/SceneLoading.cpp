#include "SceneLoading.h"
#include "SoundManager.h"

void SceneLoading::Init()
{
    DeleteObjectList();
    MakeObjectList("SceneLoading");
    m_isInitialized = true;
    SOUND_MANAGER.PlayBGM(SOUND_LABEL::BGM_RESULT);
}

void SceneLoading::UnInit()
{
    DeleteObjectList();
    m_isInitialized = false;
}

void SceneLoading::Update()
{
    // Loading’†‚Í‰½‚à‚µ‚È‚¢
}

void SceneLoading::Draw()
{
    DrawAllLayers(&m_Camera);
}
