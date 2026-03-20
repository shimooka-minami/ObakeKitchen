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

namespace
{
	const float RESULT_SCORE_STAR1 = 200.0f;
	const float RESULT_SCORE_STAR2 = 400.0f;
	const float RESULT_SCORE_STAR3 = 600.0f;
}


ResultScene::ResultScene()
{
	if (!Score::IsAvailable()) {
		Score::CreateInstance();
		// @todo for test
		Score::GetInstance()->AddScore(600);
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

	m_playScheduler = std::make_unique<TaskSchedulerSystem>();

	m_uiCanvas = new UICanvas;

	// 背景
	auto* uiBackGround = m_uiCanvas->CreateUI<UIIcon>(0);
	uiBackGround->Initialize("Assets/modelData/UI/result/result_back.dds", 1920.0f, 1080.0f);
	uiBackGround->m_transform.m_localPosition = Vector3::Zero;


	// ステージクリア
	//auto* uiStageClear = m_uiCanvas->CreateUI<UIIcon>(1);
	//uiStageClear->Initialize("Assets/modelData/UI/result/stage_clear.dds", 800.0f, 99.0f);
	//uiStageClear->m_transform.m_localPosition = Vector3(-560.0f, 450.0f, 0.0f);
	//// ステージクリアのアニメーション
	//{
	//	// test
	//	auto translateAnimation = std::make_unique<UITranslateAniamtion>();
	//	translateAnimation->SetParameter(Vector3(-1500.0f, 450.0f, 0.0f), Vector3(-560.0f, 450.0f, 0.0f), 0.5f, EasingType::Linear, LoopMode::Once);
	//	uiStageClear->AddAnimation(Hash32("uiStageClearTranslateAnimation"),std::move(translateAnimation));
	//	uiStageClear->PlayAnimation();
	//}

	// スコア表示用背景
	//auto* uiBackScore = m_uiCanvas->CreateUI<UIIcon>(2);
	//uiBackScore->Initialize("Assets/modelData/UI/result/score_back.dds", 950.0f, 750.0f);
	//uiBackScore->m_transform.m_localPosition = Vector3(0.0f, -25.0f, 0.0f);
	//
	//// おばけ 左
	//auto* uiGhostLeft = m_uiCanvas->CreateUI<UIIcon>(3);
	//uiGhostLeft->Initialize("Assets/modelData/UI/result/obake_left.dds", 350.0f, 328.0f);
	//uiGhostLeft->m_transform.m_localPosition = Vector3(-725.0f, -200.0f, 0.0f);
	//// おはけ左のアニメーション
	//{
	//	auto* render = uiGhostLeft->GetSpriteRender();
	//	std::vector<Vector3> targetTranslateList = { Vector3(-725.0f, -200.0f, 0.0f), Vector3(-725.0, 0.0f, 0.0f), Vector3(-725.0f, -200.0f, 0.0f) };
	//	std::vector<float> timeList = { 1.8f,1.8f };

	//	auto translateAnimation = std::make_unique<UITranslateAniamtion>();
	//	translateAnimation->SetParameter(Vector3(-725.0f, -200.0f, 0.0f), Vector3(-725.0f, 0.0f, 0.0f), 1.8f, EasingType::EaseIn, LoopMode::Loop);
	//	uiGhostLeft->AddAnimation(Hash32("uiGhostLeftTranslateAnimation"),std::move(translateAnimation));
	//	//uiGhostLeft->PlayAnimation();

	//	/*TranslateSpriteAnimation* translateSpriteAnimation = new TranslateSpriteAnimation(render, true, timeList, targetTranslateList );
	//	uiGhostLeft->AddSpriteAnimation(translateSpriteAnimation);
	//	uiGhostLeft->PlaySpriteAnimation();*/
	//}
	// おばけ 右
	//auto* uiGhostRight = m_uiCanvas->CreateUI<UIIcon>(3);
	//uiGhostRight->Initialize("Assets/modelData/UI/result/obake_right.dds", 350.0f, 328.0f);
	//uiGhostRight->m_transform.m_localPosition = Vector3(725.0f, 200.0f, 0.0f);
	//// おはけ右のアニメーション
	//{
	//	auto* render = uiGhostRight->GetSpriteRender();
	//	std::vector<Vector3> targetTranslateList = { Vector3(725.0f, 200.0f, 0.0f), Vector3(725.0, 0.0f, 0.0f), Vector3(725.0f, 200.0f, 0.0f) };
	//	std::vector<float> timeList = { 1.8f,1.8f };

	//	auto translateAnimation = std::make_unique<UITranslateAniamtion>();
	//	translateAnimation->SetParameter(Vector3(725.0f, 200.0f, 0.0f), Vector3(725.0, 0.0f, 0.0f), 1.8f, EasingType::EaseIn, LoopMode::PingPong);
	//	uiGhostRight->AddAnimation(Hash32("uiGhostRightTranslateAnimation"),std::move(translateAnimation));
	//	uiGhostRight->PlayAnimation();
	//}

	// 星の窪み1
	auto* uiBackStarA = m_uiCanvas->CreateUI<UIIcon>(1);
	uiBackStarA->Initialize("Assets/modelData/UI/result/star_back.dds", 250.0f, 250.0f);
	uiBackStarA->m_transform.m_localPosition = Vector3(-100.0f, 150.0f, 0.0f);
	// 星の窪み2
	auto* uiBackStarB = m_uiCanvas->CreateUI<UIIcon>(2);
	uiBackStarB->Initialize("Assets/modelData/UI/result/star_back.dds", 250.0f, 250.0f);
	uiBackStarB->m_transform.m_localPosition = Vector3(200.0f, 150.0f, 0.0f);
	// 星の窪み3
	auto* uiBackStarC = m_uiCanvas->CreateUI<UIIcon>(3);
	uiBackStarC->Initialize("Assets/modelData/UI/result/star_back.dds", 250.0f, 250.0f);
	uiBackStarC->m_transform.m_localPosition = Vector3(500.0f, 150.0f, 0.0f);

	// エフェクト
	m_starEffectList[0] = m_uiCanvas->CreateUI<UIIcon>(4);
	m_starEffectList[0]->Initialize("Assets/modelData/UI/result/star_effect.dds", 290.0f, 290.0f);
	m_starEffectList[0]->m_transform.m_localPosition = Vector3(-100.0f, 150.0f, 0.0f);
	m_starEffectList[0]->isDraw = false;
	// アニメーション
	{
		const int score = Score::GetInstance()->GetScore();
		if (score >= RESULT_SCORE_STAR1) {
			m_playScheduler->AddTimer(2.3f, [&]()
				{
					m_starEffectList[0]->isDraw = true;
					auto colorAnimation = std::make_unique<UIColorAnimation>();
					colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::Linear, LoopMode::PingPong);
					m_starEffectList[0]->AddAnimation(Hash32("m_starEffectList[0]ColorAnimation"), std::move(colorAnimation));
					m_starEffectList[0]->PlayAnimation();
				}, false);
		}
	}
	// 星1
	m_starList[0] = m_uiCanvas->CreateUI<UIIcon>(5);
	m_starList[0]->Initialize("Assets/modelData/UI/result/star.dds", 250.0f, 250.0f);
	m_starList[0]->m_transform.m_localPosition = Vector3(-100.0f, 150.0f, 0.0f);
	m_starList[0]->isDraw = false;
	// 星のアニメーション
	{
		const int score = Score::GetInstance()->GetScore();
		if (score >= RESULT_SCORE_STAR1) {
			m_playScheduler->AddTimer(0.6f, [&]()
				{
					auto scaleAnimation = std::make_unique<UIScaleAnimation>();
					scaleAnimation->SetParameter(Vector3(0.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f), 0.25f, EasingType::EaseIn, LoopMode::Once);
					m_starList[0]->AddAnimation(Hash32("m_starList[0]ScaleAnimation"), std::move(scaleAnimation));
					m_starList[0]->isDraw = true;
					m_starList[0]->PlayAnimation();
				});
			m_playScheduler->AddTimer(0.9f, [&]()
				{
					m_starList[0]->RemoveAnimation(Hash32("m_starList[0]ScaleAnimation"));
					auto scaleAnimation = std::make_unique<UIScaleAnimation>();
					scaleAnimation->SetParameter(Vector3(2.0f, 2.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), 0.3f, EasingType::EaseOut, LoopMode::Once);
					m_starList[0]->AddAnimation(Hash32("m_starList[0]ScaleAnimation"), std::move(scaleAnimation));
					m_starList[0]->PlayAnimation();
				}, false);
		}
	}
	
	// エフェクト
	m_starEffectList[1] = m_uiCanvas->CreateUI<UIIcon>(6);
	m_starEffectList[1]->Initialize("Assets/modelData/UI/result/star_effect.dds", 290.0f, 290.0f);
	m_starEffectList[1]->m_transform.m_localPosition = Vector3(200.0f, 150.0f, 0.0f);
	m_starEffectList[1]->isDraw = false;
	// アニメーション
	{
		const int score = Score::GetInstance()->GetScore();
		if (score >= RESULT_SCORE_STAR2) {
			m_playScheduler->AddTimer(2.3f, [&]()
				{
					m_starEffectList[1]->isDraw = true;
					auto colorAnimation = std::make_unique<UIColorAnimation>();
					colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::Linear, LoopMode::PingPong);
					m_starEffectList[1]->AddAnimation(Hash32("m_starEffectList[1]ColorAnimation"), std::move(colorAnimation));
					m_starEffectList[1]->PlayAnimation();
				}, false);
		}
	}
	// 星2
	m_starList[1] = m_uiCanvas->CreateUI<UIIcon>(7);
	m_starList[1]->Initialize("Assets/modelData/UI/result/star.dds", 250.0f, 250.0f);
	m_starList[1]->m_transform.m_localPosition = Vector3(200.0f, 150.0f, 0.0f);
	m_starList[1]->isDraw = false;
	// 星のアニメーション
	{
		const int score = Score::GetInstance()->GetScore();
		if (score >= RESULT_SCORE_STAR2) {
			m_playScheduler->AddTimer(1.2f, [&]()
				{
					auto scaleAnimation = std::make_unique<UIScaleAnimation>();
					scaleAnimation->SetParameter(Vector3(0.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f), 0.25f, EasingType::EaseIn, LoopMode::Once);
					m_starList[1]->AddAnimation(Hash32("m_starList[1]ScaleAnimation"), std::move(scaleAnimation));
					m_starList[1]->isDraw = true;
					m_starList[1]->PlayAnimation();
				});
			m_playScheduler->AddTimer(1.5f, [&]()
				{
					m_starList[1]->RemoveAnimation(Hash32("m_starList[1]ScaleAnimation"));
					auto scaleAnimation = std::make_unique<UIScaleAnimation>();
					scaleAnimation->SetParameter(Vector3(2.0f, 2.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), 0.3f, EasingType::EaseOut, LoopMode::Once);
					m_starList[1]->AddAnimation(Hash32("m_starList[1]ScaleAnimation"), std::move(scaleAnimation));
					m_starList[1]->PlayAnimation();
				}, false);
		}
	}

	// エフェクト
	m_starEffectList[2] = m_uiCanvas->CreateUI<UIIcon>(8);
	m_starEffectList[2]->Initialize("Assets/modelData/UI/result/star_effect.dds", 290.0f, 290.0f);
	m_starEffectList[2]->m_transform.m_localPosition = Vector3(500.0f, 150.0f, 0.0f);
	m_starEffectList[2]->isDraw = false;
	// アニメーション
	{
		const int score = Score::GetInstance()->GetScore();
		if (score >= RESULT_SCORE_STAR3) {
			m_playScheduler->AddTimer(2.3f, [&]()
				{
					m_starEffectList[2]->isDraw = true;
					auto colorAnimation = std::make_unique<UIColorAnimation>();
					colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::Linear, LoopMode::PingPong);
					m_starEffectList[2]->AddAnimation(Hash32("m_starEffectList[2]ColorAnimation"), std::move(colorAnimation));
					m_starEffectList[2]->PlayAnimation();
				}, false);
		}
	}
	// 星3
	m_starList[2] = m_uiCanvas->CreateUI<UIIcon>(9);
	m_starList[2]->Initialize("Assets/modelData/UI/result/star.dds", 250.0f, 250.0f);
	m_starList[2]->m_transform.m_localPosition = Vector3(500.0f, 150.0f, 0.0f);
	m_starList[2]->isDraw = false;
	// 星のアニメーション
	{
		const int score = Score::GetInstance()->GetScore();
		if (score >= RESULT_SCORE_STAR3) {
			m_playScheduler->AddTimer(1.8f, [&]()
				{
					auto scaleAnimation = std::make_unique<UIScaleAnimation>();
					scaleAnimation->SetParameter(Vector3(0.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 0.0f), 0.25f, EasingType::EaseIn, LoopMode::Once);
					m_starList[2]->AddAnimation(Hash32("m_starList[1]ScaleAnimation"), std::move(scaleAnimation));
					m_starList[2]->isDraw = true;
					m_starList[2]->PlayAnimation();
				});
			m_playScheduler->AddTimer(2.1f, [&]()
				{
					m_starList[2]->RemoveAnimation(Hash32("m_starList[1]ScaleAnimation"));
					auto scaleAnimation = std::make_unique<UIScaleAnimation>();
					scaleAnimation->SetParameter(Vector3(2.0f, 2.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), 0.3f, EasingType::EaseOut, LoopMode::Once);
					m_starList[2]->AddAnimation(Hash32("m_starList[1]ScaleAnimation"), std::move(scaleAnimation));
					m_starList[2]->PlayAnimation();
				}, false);
		}
	}

	// リザルトスコアテキスト
	m_uiText = m_uiCanvas->CreateUI<UIIcon>(10);
	m_uiText->Initialize("Assets/modelData/UI/score_text.dds", 300.0f, 44.0f);
	m_uiText->m_transform.m_localPosition = Vector3(-50.0f, -250.0f, 0.0f);
	m_uiText->isDraw = false;
	{
		m_playScheduler->AddTimer(2.5f, [&]()
			{
				m_uiText->isDraw = true;
				auto colorAnimation = std::make_unique<UIColorAnimation>();
				colorAnimation->SetParameter(Vector4(0.0f, 0.0f, 0.0f, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, EasingType::EaseOut, LoopMode::Once);
				m_uiText->AddAnimation(Hash32("m_uiTextColorAnimation"), std::move(colorAnimation));
				m_uiText->PlayAnimation();
			}, false);		
	}

	// スコアの数字
	m_uiDigit = m_uiCanvas->CreateUI<UIDigit>(11);
	m_uiDigit->Initialize("Assets/modelData/UI/suji", 4, 0, 80.0f, 80.0f, Vector3(570.0f, -250.0f, 0.0f), Vector3::One, Quaternion::Identity);
	m_uiDigit->SetNumber(Score::GetInstance()->GetScore());
	m_uiDigit->isDraw = false;
	// UIアニメーション追加
	{
		m_playScheduler->AddTimer(2.5f, [&]()
			{
				m_uiDigit->isDraw = true;
				auto& spriteRenderList = m_uiDigit->GetSpriteRenderList();
				for (int i = 0; i < spriteRenderList.size(); ++i) {
					auto* render = spriteRenderList[i];
					render->SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
					auto colorAnimation = std::make_unique<UIColorAnimation>();
					colorAnimation->SetParameter(Vector4(0.0f, 0.0f, 0.0f, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, EasingType::EaseOut, LoopMode::Once);
					m_uiDigit->AddAnimation(Hash32("m_uiDigitColorAnimation") + i, std::move(colorAnimation));
					m_uiDigit->PlayAnimation();
				}
			}, false);
	}

	// もどる
	m_backObake = m_uiCanvas->CreateUI<UIIcon>(12);
	m_backObake->Initialize("Assets/modelData/menu/back_obake.dds", 250.0f, 250.0f);
	m_backObake->m_transform.m_localPosition = Vector3(-750.0f, -320.0f, 0.0f);
	m_backObake->isDraw = false;
	// アニメーション
	{
		m_playScheduler->AddTimer(2.8f, [&]()
			{
				m_backObake->isDraw = true;
				auto colorAnimation = std::make_unique<UIColorAnimation>();
				colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, EasingType::Linear, LoopMode::Once);
				m_backObake->AddAnimation(Hash32("m_backObakeColorAnimation"), std::move(colorAnimation));
				m_backObake->PlayAnimation();
			}, false);
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
	
	m_playScheduler->Update(g_gameTime->GetFrameDeltaTime());

	m_uiDigit->PlayAnimation();
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