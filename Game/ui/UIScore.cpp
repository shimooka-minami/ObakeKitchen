/**
 * UIScore.cpp
 * スコアを計算する
 */
#include "stdafx.h"
#include "UIScore.h"
#include "UIBase.h"


UIScore::UIScore()
{
}


UIScore::~UIScore()
{
}


bool UIScore::Start()
{
	m_uiCanvas = new UICanvas();
	m_uiDigit = m_uiCanvas->CreateUI<UIDigit>();
	m_uiDigit->Initialize("Assets/modelData/UI/suji", 5, 0, 50.0f, 50.0f, Vector3(-400.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// @todo for test
	//auto* uiDigit = m_uiCanvas->CreateUI<UIDigit>();
	//uiDigit->Initialize("Assets/modelData/UI/suji", 5, 0, 50.0f, 50.0f, Vector3(-400.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	m_uiDigit->SetNumber(0);

	// 右から3番目の桁(=targetDigit = 3) を":"に変更
	//uiDigit->SetCustomChar(3, "coron.dds");

	
	return true;
}


void UIScore::Update()
{
	// スコアを設定
	m_uiDigit->SetNumber(m_score);

	m_uiCanvas->Update();
}


void UIScore::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}