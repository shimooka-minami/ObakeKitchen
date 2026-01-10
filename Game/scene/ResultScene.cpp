#include "stdafx.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "sound/SoundManager.h"

#include "ui/UIBase.h"
#include "ui/UiScore.h"
#include "ui/UIAnimation.h"

// @todo for test
#include "Util/Curve.h"

#include "score/Score.h"


ResultScene::ResultScene()
{
	if (!Score::IsAvailable()) {
		Score::CreateInstance();
		// @todo for test
		Score::GetInstance()->AddScore(1500);
	}
}


ResultScene::~ResultScene()
{
	SoundManager::Get().StopBGM();
	Score::DestroyInstance();
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
		/*auto* render = uiStageClear->GetSpriteRender();
		std::vector<Vector3> targetTranslateList = { Vector3(-1500.0f, 450.0f, 0.0f), Vector3(-560.0f, 450.0f, 0.0f) };
		std::vector<float> timeList = { 0.5f };*/
		
		// test
		auto translateAnimation = std::make_unique<UIVector3Animation>();
		translateAnimation->SetParameter(Vector3(-1500.0f, 450.0f, 0.0f), Vector3(-560.0f, 450.0f, 0.0f), 0.5f, EasingType::Linear, LoopMode::Loop);
		uiStageClear->SetUIAnimation(std::move(translateAnimation));
		uiStageClear->PlayAnimation();
		//translateAnimation->Update();

		/*UIVector3Animation* translateUIAnimation = new UIVector3Animation(render, false, timeList, targetTranslateList);
		uiStageClear->AddSpriteAnimation(translateSpriteAnimation);
		uiStageClear->PlaySpriteAnimation();*/
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
		std::vector<float> timeList = { 1.8f,1.8f };

		auto translateAnimation = std::make_unique<UIVector3Animation>();
		translateAnimation->SetParameter(Vector3(-1500.0f, 450.0f, 0.0f), Vector3(-560.0f, 450.0f, 0.0f), 1.8f, EasingType::EaseIn, LoopMode::Loop);
		uiGhostLeft->SetUIAnimation(std::move(translateAnimation));
		uiGhostLeft->PlayAnimation();

		/*TranslateSpriteAnimation* translateSpriteAnimation = new TranslateSpriteAnimation(render, true, timeList, targetTranslateList );
		uiGhostLeft->AddSpriteAnimation(translateSpriteAnimation);
		uiGhostLeft->PlaySpriteAnimation();*/
	}
	// おばけ 右
	auto* uiGhostRight = m_uiCanvas->CreateUI<UIIcon>();
	uiGhostRight->Initialize("Assets/modelData/UI/result/obake_right.dds", 350.0f, 328.0f, Vector3(725.0f, 200.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// おはけ右のアニメーション
	{
		auto* render = uiGhostRight->GetSpriteRender();
		std::vector<Vector3> targetTranslateList = { Vector3(725.0f, 200.0f, 0.0f), Vector3(725.0, 0.0f, 0.0f), Vector3(725.0f, 200.0f, 0.0f) };
		std::vector<float> timeList = { 1.8f,1.8f };

		auto translateAnimation = std::make_unique<UIVector3Animation>();
		translateAnimation->SetParameter(Vector3(725.0f, 200.0f, 0.0f), Vector3(725.0, 0.0f, 0.0f), 1.8f, EasingType::EaseIn, LoopMode::Loop);
		uiGhostRight->SetUIAnimation(std::move(translateAnimation));
		uiGhostRight->PlayAnimation();

		//TranslateSpriteAnimation* translateSpriteAnimation = new TranslateSpriteAnimation(render, true, timeList, targetTranslateList);
		//uiGhostRight->AddSpriteAnimation(translateSpriteAnimation);
		//uiGhostRight->PlaySpriteAnimation();
	}

	// 星の窪み1
	auto* uiBackStar = m_uiCanvas->CreateUI<UIIcon>();
	uiBackStar->Initialize("Assets/modelData/UI/result/star_back.dds", 250.0f, 250.0f, Vector3(-300.0f, 150.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// 星の窪み2
	uiBackStar = m_uiCanvas->CreateUI<UIIcon>();
	uiBackStar->Initialize("Assets/modelData/UI/result/star_back.dds", 250.0f, 250.0f, Vector3(0.0f, 150.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// 星の窪み3
	uiBackStar = m_uiCanvas->CreateUI<UIIcon>();
	uiBackStar->Initialize("Assets/modelData/UI/result/star_back.dds", 250.0f, 250.0f, Vector3(300.0f, 150.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// 星1
	m_starList[0] = m_uiCanvas->CreateUI<UIIcon>();
	m_starList[0]->Initialize("Assets/modelData/UI/result/star.dds", 250.0f, 250.0f, Vector3(-300.0f, 150.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// 星のアニメーション
	{
		auto* render = m_starList[0]->GetSpriteRender();
		std::vector<Vector2> scaleList = { Vector2(0.0f,0.0f), Vector2(0.0f,0.0f), Vector2(2.0f,2.0f), Vector2(1.0f,1.0f) };
		std::vector<float> timeList = { 1.0f, 0.2f, 0.2f };

		auto scaleAnimation = std::make_unique<UIVector2Animation>();
		scaleAnimation->SetParameter(Vector2(0.0f, 0.0f), Vector2(2.0f, 2.0f),1.0f, EasingType::Linear, LoopMode::Once);
		scaleAnimation->SetParameter(Vector2(2.0f, 2.0f), Vector2(1.0f, 1.0f), 0.2f, EasingType::Linear, LoopMode::Once);
		m_starList[0]->SetUIAnimation(std::move(scaleAnimation));
		m_starList[0]->PlayAnimation();

		/*ScaleSpriteAnimation* scaleSpriteAnimation = new ScaleSpriteAnimation(render, false, timeList, scaleList);
		m_starList[0]->AddSpriteAnimation(scaleSpriteAnimation);
		m_starList[0]->m_transform.m_localScale = Vector3::Zero;*/
	}
	// 星2
	m_starList[1] = m_uiCanvas->CreateUI<UIIcon>();
	m_starList[1]->Initialize("Assets/modelData/UI/result/star.dds", 250.0f, 250.0f, Vector3(0.0f, 150.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// 星のアニメーション
	{
		auto* render = m_starList[1]->GetSpriteRender();
		std::vector<Vector2> scaleList = { Vector2(0.0f,0.0f), Vector2(0.0f,0.0f), Vector2(2.0f,2.0f), Vector2(1.0f,1.0f) };
		std::vector<float> timeList = { 1.0f, 0.2f, 0.2f };

		auto scaleAnimation = std::make_unique<UIVector2Animation>();
		scaleAnimation->SetParameter(Vector2(0.0f, 0.0f), Vector2(2.0f, 2.0f), 1.0f, EasingType::Linear, LoopMode::Once);
		scaleAnimation->SetParameter(Vector2(2.0f, 2.0f), Vector2(1.0f, 1.0f), 0.2f, EasingType::Linear, LoopMode::Once);
		m_starList[1]->SetUIAnimation(std::move(scaleAnimation));
		m_starList[1]->PlayAnimation();

		/*auto* render = m_starList[1]->GetSpriteRender();
		std::vector<Vector2> scaleList = { Vector2(0.0f,0.0f), Vector2(0.0f,0.0f), Vector2(2.0f,2.0f), Vector2(1.0f,1.0f) };
		std::vector<float> timeList = { 1.3f, 0.2f, 0.2f };
		ScaleSpriteAnimation* scaleSpriteAnimation = new ScaleSpriteAnimation(render, false, timeList, scaleList);
		m_starList[1]->AddSpriteAnimation(scaleSpriteAnimation);
		m_starList[1]->m_transform.m_localScale = Vector3::Zero;*/
	}
	// 星3
	m_starList[2] = m_uiCanvas->CreateUI<UIIcon>();
	m_starList[2]->Initialize("Assets/modelData/UI/result/star.dds", 250.0f, 250.0f, Vector3(300.0f, 150.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// 星のアニメーション
	{
		auto* render = m_starList[2]->GetSpriteRender();
		std::vector<Vector2> scaleList = { Vector2(0.0f,0.0f), Vector2(0.0f,0.0f), Vector2(2.0f,2.0f), Vector2(1.0f,1.0f) };
		std::vector<float> timeList = { 1.0f, 0.2f, 0.2f };

		auto scaleAnimation = std::make_unique<UIVector2Animation>();
		scaleAnimation->SetParameter(Vector2(0.0f, 0.0f), Vector2(2.0f, 2.0f), 1.0f, EasingType::Linear, LoopMode::Once);
		scaleAnimation->SetParameter(Vector2(2.0f, 2.0f), Vector2(1.0f, 1.0f), 0.2f, EasingType::Linear, LoopMode::Once);
		m_starList[2]->SetUIAnimation(std::move(scaleAnimation));
		m_starList[2]->PlayAnimation();

		/*auto* render = m_starList[2]->GetSpriteRender();
		std::vector<Vector2> scaleList = { Vector2(0.0f,0.0f), Vector2(0.0f,0.0f), Vector2(2.0f,2.0f), Vector2(1.0f,1.0f) };
		std::vector<float> timeList = { 1.6f, 0.2f, 0.2f };
		ScaleSpriteAnimation* scaleSpriteAnimation = new ScaleSpriteAnimation(render, false, timeList, scaleList);
		m_starList[2]->AddSpriteAnimation(scaleSpriteAnimation);
		m_starList[2]->m_transform.m_localScale = Vector3::Zero*/;
	}

	// リザルトスコアテキスト
	auto* uiText = m_uiCanvas->CreateUI<UIIcon>();
	uiText->Initialize("Assets/modelData/UI/score_text.dds", 300.0f, 44.0f, Vector3(-250.0f, -150.0f, 0.0f), Vector3::One, Quaternion::Identity);
	{
		auto* render = uiText->GetSpriteRender();
		std::vector<Vector4> targetColorList = { Vector4(0.0f,0.0f,0.0f,0.0f),Vector4(0.0f,0.0f,0.0f,0.0f),Vector4(0.0f,0.0f,0.0f,1.0f) };
		std::vector<float> timeList = { 1.9f,1.0f };
		
		auto colorAnimation = std::make_unique<UIVector4Animation>();
		colorAnimation->SetParameter(Vector4(0.0f, 0.0f, 0.0f, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1.9f, EasingType::Linear, LoopMode::Once);
		uiText->SetUIAnimation(std::move(colorAnimation));
		uiText->PlayAnimation();


	/*	std::vector<float> timeList = { 1.9f, 0.1f };
		std::vector<Vector4> targetColorList = { Vector4(0.0f,0.0f,0.0f,0.0f), Vector4(0.0f, 0.0f, 0.0f, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f) };
		auto* render = uiText->GetSpriteRender();
		render->SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
		ColorSpriteAnimation* alphaSpriteAnimation = new ColorSpriteAnimation(render, false, timeList, targetColorList);
		uiText->AddSpriteAnimation(alphaSpriteAnimation);*/
	}
	//uiText->PlaySpriteAnimation();

	// スコアの数字
	auto* uiDigit = m_uiCanvas->CreateUI<UIDigit>();
	uiDigit->Initialize("Assets/modelData/UI/suji", 4, 0, 80.0f, 80.0f, Vector3(370.0f, -150.0f, 0.0f), Vector3::One, Quaternion::Identity);
	uiDigit->SetNumber(Score::GetInstance()->GetScore());
	// UIアニメーション追加
	{
		auto& spriteRenderList = uiDigit->GetSpriteRenderList();
		for (int i = 0; i < spriteRenderList.size(); ++i) {
			auto* render = spriteRenderList[i];
			render->SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
			auto colorAnimation = std::make_unique<UIVector4Animation>();
			colorAnimation->SetParameter(Vector4(0.0f, 0.0f, 0.0f, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1.9f, EasingType::Linear, LoopMode::Once);
			uiDigit->SetUIAnimation(std::move(colorAnimation));
		}
		uiDigit->PlayAnimation();

		/*std::vector<float> timeList = { 1.9f, 0.1f };
		std::vector<Vector4> targetColorList = {Vector4(0.0f,0.0f,0.0f,0.0f), Vector4(0.0f, 0.0f, 0.0f, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f) };
		auto& spriteRenderList = uiDigit->GetSpriteRenderList();
		for (int i = 0; i < spriteRenderList.size(); ++i) {
			auto* render = spriteRenderList[i];
			render->SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
			ColorSpriteAnimation* alphaSpriteAnimation = new ColorSpriteAnimation(render, false, timeList, targetColorList);
			uiDigit->AddSpriteAnimation(alphaSpriteAnimation);
		}
		uiDigit->PlaySpriteAnimation();*/
	}

	const int score = Score::GetInstance()->GetScore();
	// @todo for あとで外部パラメーターにする
	// 星1
	if (score >= 500) {
		//m_starList[0]->PlaySpriteAnimation();
		m_starList[0]->PlayAnimation();
		m_starList[0]->m_transform.m_localScale = Vector3::One;
	}
	// 星2
	if (score >= 1000) {
		//m_starList[1]->PlaySpriteAnimation();
		m_starList[1]->PlayAnimation();
		m_starList[1]->m_transform.m_localScale = Vector3::One;
	}
	// 星3
	if (score >= 1500) {
		//m_starList[2]->PlaySpriteAnimation();
		m_starList[2]->PlayAnimation();
		m_starList[2]->m_transform.m_localScale = Vector3::One;
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