#include "stdafx.h"
#include "SceneManager.h"

#include "BootScene.h"
#include "StartupScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"

#include "core/Fade.h"


SceneManager* SceneManager::m_instance = nullptr;	// 初期化


SceneManager::SceneManager()
{
	// ブートシーン追加
	AddSceneMap<BootScene>();
	AddSceneMap<StartupScene>();
	AddSceneMap<TitleScene> ();
	AddSceneMap<GameScene>();
	AddSceneMap<ResultScene>();
}


SceneManager::~SceneManager()
{
}


void SceneManager::Update()
{
	if (m_currentScene) {
		m_currentScene->Update();
		if (m_currentScene->RequestScene(m_nextSceneId, m_waitTime)) {
			delete m_currentScene;
			m_currentScene = nullptr;

			Fade::Get().Enable();
			return;
		}
	}

	if (m_nextSceneId != INVALID_SCENE_ID) {
		m_elapsedTime += g_gameTime->GetFrameDeltaTime();
		if (m_elapsedTime >= m_waitTime) {
			CreateScene(m_nextSceneId);
			m_waitTime = 0.0f;
			m_elapsedTime = 0.0f;
			m_nextSceneId = INVALID_SCENE_ID;

			Fade::Get().Disable();
		}
	}
}


void SceneManager::Render(RenderContext& rc)
{
	if (m_currentScene) {
		m_currentScene->Render(rc);
	}
}


void SceneManager::CreateScene(const uint32_t id)
{
	auto it = m_sceneMap.find(id);
	if (it == m_sceneMap.end()) {
		K2_ASSERT(false, "新規シーンが追加されていません。\n");
	}
	auto& createSceneFunc = it->second;
	m_currentScene = createSceneFunc();
	m_currentScene->Start();
}




/*****************************************************/


SceneManagerObject::SceneManagerObject()
{
	SceneManager::CreateInstance();
}


SceneManagerObject::~SceneManagerObject()
{
	SceneManager::DestroyInstance();
}


bool SceneManagerObject::Start()
{
	// 最初のシーンを設定
	SceneManager::GetInstance()->CreateScene(BootScene::ID());
	return true;
}


void SceneManagerObject::Update()
{
	SceneManager::GetInstance()->Update();
}


void SceneManagerObject::Render(RenderContext& rc)
{
	SceneManager::GetInstance()->Render(rc);
}