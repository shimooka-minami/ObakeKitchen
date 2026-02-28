/**
 * UIScore.cpp
 * スコアを計算する
 */
#include "stdafx.h"
#include "UIScore.h"
#include "UIBase.h"
#include "util/CRC32.h"
//#include "SpriteAnimation.h"


UIScore::UIScore()
{
}


UIScore::~UIScore()
{
	delete m_uiCanvas;
	delete m_uiAddScoreCanvas;
}


bool UIScore::Start()
{
	m_uiCanvas = new UICanvas();

	// @todo for test // 背景
	auto* uiBack = m_uiCanvas->CreateUI<UIIcon>(0);
	uiBack->Initialize("Assets/modelData/UI/back.dds", 400.0f, 120.0f);
	uiBack->m_transform.m_localPosition = Vector3(-750.0f, -440.0f, 0.0f);

	m_uiDigit = m_uiCanvas->CreateUI<UIDigit>(1);
	m_uiDigit->Initialize("Assets/modelData/UI/suji", 4, 0, 50.0f, 50.0f, Vector3(-650.0f, -450.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// コイン
	auto* uiCoin = m_uiCanvas->CreateUI<UIIcon>(2);
	uiCoin->Initialize("Assets/modelData/UI/coin.dds", 80.0f, 80.0f);
	uiCoin->m_transform.m_localPosition = Vector3(-880.0f, -450.0f, 0.0f);
	
	m_uiDigit->SetNumber(0);

	// 追加されるスコア表示のUIを作る
	m_uiAddScoreCanvas = new UICanvas();
	m_uiAddScoreDigit = m_uiAddScoreCanvas->CreateUI<UIDigit>(3);
	m_uiAddScoreDigit->Initialize("Assets/modelData/UI/suji", 3, 0, 50.0f, 50.0f, Vector3(-650.0f, -350.0f, 0.0f), Vector3::One, Quaternion::Identity);
	m_uiAddScoreDigit->SetNumber(0);
	// UIアニメーション追加
	{
		auto translateAnimation = std::make_unique<UITranslateAniamtion>();
		translateAnimation->SetParameter(Vector3(-650.0f, -400.0f, 0.0f), Vector3(-650.0f, -350.0f, 0.0f), 0.8f, EasingType::EaseIn, LoopMode::Once);
		m_uiAddScoreDigit->AddAnimation(Hash32("m_uiAddScoreDigitTranslateAnimation"), std::move(translateAnimation));
		m_uiAddScoreDigit->StopSpriteAnimation();
	}
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 0.0f), 0.8f, EasingType::EaseIn, LoopMode::Once);
		m_uiAddScoreDigit->AddAnimation(Hash32("m_uiAddScoreDigitColorAnimation"), std::move(colorAnimation));
		m_uiAddScoreDigit->StopSpriteAnimation();
	}
	m_uiAddScoreDigit->isDraw = false;

	return true;
}


void UIScore::Update()
{
	//// @todo for play
	//if (g_pad[0]->IsTrigger(enButtonY))
	//{
	//	m_requestAddScore = 100;
	//}

	if (m_requestAddScore != 0) {
		m_uiAddScoreDigit->isDraw = true;
		m_addScore = m_requestAddScore;
		m_uiAddScoreDigit->ResetAnimation();
		m_uiAddScoreDigit->PlayAnimation();
	}

	if (!m_uiAddScoreDigit->IsPlayAniamtion())
	{
		m_uiAddScoreDigit->isDraw = false;
	}

	// スコアを設定
	m_uiDigit->SetNumber(m_score);
	// 追加スコアの設定
	m_uiAddScoreDigit->SetNumber(m_addScore);

	m_uiCanvas->Update();
	m_uiAddScoreCanvas->Update();
}


void UIScore::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
	m_uiAddScoreCanvas->Render(rc);
}