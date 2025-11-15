#include "stdafx.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "sound/SoundManager.h"

#include "ui/UIBase.h"



ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
	SoundManager::Get().StopBGM();
}


bool ResultScene::Start()
{
	//m_spriteRender.Init("Assets/modelData/UI/result.dds",1920.0f,1080.0f);

	m_uiCanvas = new UICanvas;

	// 背景
	auto* uiBackGround = m_uiCanvas->CreateUI<UIIcon>();
	uiBackGround->Initialize("Assets/modelData/UI/result/Back.dds", 1920.0f, 1080.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

	// ステージクリア
	auto* uiStageClear = m_uiCanvas->CreateUI<UIIcon>();
	uiStageClear->Initialize("Assets/modelData/UI/result/stage_clear.dds", 800.0f, 99.0f, Vector3(-560.0f,450.0f,0.0f), Vector3::One, Quaternion::Identity);
	// ステージクリアのアニメーション
	{
		auto* render = uiStageClear->GetSpriteRender();
		std::vector<Vector3> targetTranslateList = { Vector3(-1500.0f, 450.0f, 0.0f), Vector3(-560.0f, 450.0f, 0.0f) };
		std::vector<float> timeList = { 0.5f };
 		TranslateSpriteAnimation* translateSpriteAnimation = new TranslateSpriteAnimation(render, false, timeList, targetTranslateList);
		uiStageClear->AddSpriteAnimation(translateSpriteAnimation);
		uiStageClear->PlaySpriteAnimation();
	}

	// スコア表示用背景
	auto* uiBackScore = m_uiCanvas->CreateUI<UIIcon>();
	uiBackScore->Initialize("Assets/modelData/UI/result/score_back.dds", 950.0f, 750.0f, Vector3(0.0f, -25.0f, 0.0f), Vector3::One, Quaternion::Identity);
	
	// おばけ 左
	auto* uiGhostLeft = m_uiCanvas->CreateUI<UIIcon>();
	uiGhostLeft->Initialize("Assets/modelData/UI/result/obake_left.dds", 350.0f, 328.0f, Vector3(-725.0f, -200.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// おはけ左のアニメーション
	{
		auto* render = uiGhostLeft->GetSpriteRender();
		std::vector<Vector3> targetTranslateList = { Vector3(-725.0f, -200.0f, 0.0f), Vector3(-725.0, 0.0f, 0.0f), Vector3(-725.0f, -200.0f, 0.0f) };
		std::vector<float> timeList = { 1.3f,1.3f };
		TranslateSpriteAnimation* translateSpriteAnimation = new TranslateSpriteAnimation(render, true, timeList, targetTranslateList );
		uiGhostLeft->AddSpriteAnimation(translateSpriteAnimation);
		uiGhostLeft->PlaySpriteAnimation();
	}
	// おばけ 右
	auto* uiGhostRight = m_uiCanvas->CreateUI<UIIcon>();
	uiGhostRight->Initialize("Assets/modelData/UI/result/obake_right.dds", 350.0f, 328.0f, Vector3(725.0f, 200.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// おはけ右のアニメーション
	{
		auto* render = uiGhostRight->GetSpriteRender();
		std::vector<Vector3> targetTranslateList = { Vector3(725.0f, 200.0f, 0.0f), Vector3(725.0, 0.0f, 0.0f), Vector3(725.0f, 200.0f, 0.0f) };
		std::vector<float> timeList = { 1.3f,1.3f };
		TranslateSpriteAnimation* translateSpriteAnimation = new TranslateSpriteAnimation(render, true, timeList, targetTranslateList);
		uiGhostRight->AddSpriteAnimation(translateSpriteAnimation);
		uiGhostRight->PlaySpriteAnimation();
	}

	// 星の窪み
	auto* uiBackStar = m_uiCanvas->CreateUI<UIIcon>();
	uiBackStar->Initialize("Assets/modelData/UI/result/star_back.dds", 250.0f, 250.0f, Vector3(0.0f, 150.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// 星
	auto* uiStar = m_uiCanvas->CreateUI<UIIcon>();
	uiStar->Initialize("Assets/modelData/UI/result/star.dds", 250.0f, 250.0f, Vector3(0.0f, 150.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// 星のアニメーション
	{
		auto* render = uiStar->GetSpriteRender();
		std::vector<Vector2> scaleList = { Vector2(0.0f,0.0f), Vector2(2.0f,2.0f), Vector2(1.0f,1.0f) };
		std::vector<float> timeList = { 0.2f, 0.2f };
		ScaleSpriteAnimation* scaleSpriteAnimation = new ScaleSpriteAnimation(render, false, timeList, scaleList);
		uiStar->AddSpriteAnimation(scaleSpriteAnimation);
		uiStar->PlaySpriteAnimation();
	}


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
	//m_spriteRender.Update();

	m_uiCanvas->Update();
}


void ResultScene::Render(RenderContext& rc)
{
	//m_spriteRender.Draw(rc);
	m_uiCanvas->Render(rc);
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