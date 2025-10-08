#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"


namespace
{
	constexpr float MAX_SPRITE_WIDTH = 1920.0f;
	constexpr float MAX_SPRITE_HIGHT = 1080.0f;
}


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}


bool TitleScene::Start()
{
	m_spriteRender.Init("Assets/modelData/title/title.dds", MAX_SPRITE_WIDTH, MAX_SPRITE_HIGHT);
	return true;
}


void TitleScene::Update()
{
	m_spriteRender.Update();
}


void TitleScene::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}


bool TitleScene::RequestScene(uint32_t& id)
{
	if (g_pad[0]->IsPress(enButtonA)) {
		id = GameScene::ID();
		return true;
	}
	return false;
}