/**
 * UIScore.cpp
 * スコアを計算する
 */
#include "stdafx.h"
#include "UIScore.h"
#include "UIBase.h"
#include "SpriteAnimation.h"


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
	auto* uiBack = m_uiCanvas->CreateUI<UIIcon>();
	uiBack->Initialize("Assets/modelData/UI/back.dds", 400.0f, 120.0f, Vector3(-750.0f, -440.0f, 0.0f), Vector3::One, Quaternion::Identity);

	m_uiDigit = m_uiCanvas->CreateUI<UIDigit>();
	m_uiDigit->Initialize("Assets/modelData/UI/suji", 4, 0, 50.0f, 50.0f, Vector3(-650.0f, -450.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// コイン
	auto* uiCoin = m_uiCanvas->CreateUI<UIIcon>();
	uiCoin->Initialize("Assets/modelData/UI/coin.dds", 80.0f, 80.0f, Vector3(-880.0f, -450.0f, 0.0f), Vector3::One, Quaternion::Identity);

	


	// @todo for test
	//auto* uiDigit = m_uiCanvas->CreateUI<UIDigit>();
	//uiDigit->Initialize("Assets/modelData/UI/suji", 5, 0, 50.0f, 50.0f, Vector3(-400.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	m_uiDigit->SetNumber(0);

	// 右から3番目の桁(=targetDigit = 3) を":"に変更
	//uiDigit->SetCustomChar(3, "coron.dds");

	// 追加されるスコア表示のUIを作る
	m_uiAddScoreCanvas = new UICanvas();
	m_uiAddScoreDigit = m_uiAddScoreCanvas->CreateUI<UIDigit>();
	m_uiAddScoreDigit->Initialize("Assets/modelData/UI/suji", 3, 0, 50.0f, 50.0f, Vector3(-650.0f, -350.0f, 0.0f), Vector3::One, Quaternion::Identity);
	m_uiAddScoreDigit->SetNumber(0);
	// UIアニメーション追加
	{
		auto& spriteRenderList = m_uiAddScoreDigit->GetSpriteRenderList();
		for (int i = 0; i < spriteRenderList.size(); ++i) {
			auto* render = spriteRenderList[i];
			render->SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
			TranslateSpriteAnimation* translateSpriteAnimation = new TranslateSpriteAnimation(render, 1.0f, false, Vector3(-650.0f - (50.0f * i), -400.0f, 0.0f), Vector3(-650.0f - (50.0f * i), -350.0f, 0.0f));
			m_uiAddScoreDigit->AddSpriteAnimation(translateSpriteAnimation);
			ColorSpriteAnimation* alphaSpriteAnimation = new ColorSpriteAnimation(render, 1.0f, false, Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 0.0f));
			m_uiAddScoreDigit->AddSpriteAnimation(alphaSpriteAnimation);
		}
	}

	return true;
}


void UIScore::Update()
{
	if (m_requestAddScore != 0) {
		m_addScore = m_requestAddScore;
		m_uiAddScoreDigit->PlaySpriteAnimation();
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