/**
 * UITimer.cpp
 * 制限時間の表示
 */
#include "stdafx.h"
#include "UITimer.h"
#include "UIBase.h"


UITimer::UITimer()
{
}


UITimer::~UITimer()
{
}


bool UITimer::Start()
{
	m_uiCanvas = new UICanvas();
	m_uiCanvas->m_transform.m_localPosition = Vector3(400.0f, -300.0f, 0.0f);
	auto* uiBackground = m_uiCanvas->CreateUI<UIIcon>();
	uiBackground->Initialize("Assets/modelData/UI/limitTime.dds", 128.0f, 30.0f, Vector3(-200.0f,0.0f,0.0f),Vector3::One, Quaternion::Identity);
	m_uiDigit = m_uiCanvas->CreateUI<UIDigit>();
	m_uiDigit->Initialize("Assets/modelData/UI/suji", 3, 0, 50.0f, 50.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// @todo for test
	//auto* uiDigit = m_uiCanvas->CreateUI<UIDigit>();
	//uiDigit->Initialize("Assets/modelData/UI/suji", 5, 0, 50.0f, 50.0f, Vector3(-400.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	m_uiDigit->SetNumber(0);

	// 右から3番目の桁(=targetDigit = 3) を":"に変更
	//uiDigit->SetCustomChar(3, "coron.dds");

	
	return true;
}


void UITimer::Update()
{
	// スコアを設定
	m_uiDigit->SetNumber(static_cast<int>(m_timer));

	m_uiCanvas->Update();
}


void UITimer::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}