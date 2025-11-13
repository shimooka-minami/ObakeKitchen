#include "stdafx.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "sound/SoundManager.h"


ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
	SoundManager::Get().StopBGM();
}


bool ResultScene::Start()
{
	m_spriteRender.Init("Assets/modelData/UI/result.dds",1920.0f,1080.0f);
	return true;
}


void ResultScene::Update()
{
	if (!isRequestNext) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			SoundManager::Get().PlaySE(enSoundKind_Button);
			isRequestNext = true;
		}
	}
	m_spriteRender.Update();
}


void ResultScene::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}


bool ResultScene::RequestScene(uint32_t& id, float& waitTime)
{
	if (isRequestNext) {
		id = TitleScene::ID();
		waitTime = 3.0f;
		return true;
	}
	return false;
}