/**
 * UITimer.cpp
 * 制限時間の表示
 */
#include "stdafx.h"
#include "UITimer.h"
#include "UIBase.h"

#include "core/TimeKeeper.h"
#include <util/CRC32.h>

UITimer::UITimer()
{
}


UITimer::~UITimer()
{
}


bool UITimer::Start()
{
	m_uiCanvas = new UICanvas();
	m_uiCanvas->m_transform.m_localPosition = Vector3(800.0f, -450.0f, 0.0f);

	// 制限時間
	auto* uiBackground = m_uiCanvas->CreateUI<UIIcon>(0);
	uiBackground->Initialize("Assets/modelData/UI/limitTime.dds", 128.0f, 30.0f);
	uiBackground->m_transform.m_localPosition = Vector3(-200.0f, 0.0f, 0.0f);

	// 数字
	m_uiDigit = m_uiCanvas->CreateUI<UIDigit>(1);
	m_uiDigit->Initialize("Assets/modelData/UI/suji", 3, 0, 50.0f, 50.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, EasingType::Linear, LoopMode::PingPong);
		m_uiDigit->AddAnimation(Hash32("m_uiDigitColorAnimation"), std::move(colorAnimation));
		m_uiDigit->StopSpriteAnimation();
	}

	// 砂時計
	m_uiHourGlass = m_uiCanvas->CreateUI<UIIcon>(2);
	m_uiHourGlass->Initialize("Assets/modelData/UI/timer.dds", 80.0f, 80.0f);
	m_uiHourGlass->m_transform.m_localPosition = Vector3(50.0f, 0.0f, 0.0f);
	m_uiHourGlass->m_transform.m_localRotation.SetRotationDegZ(30.0f);
	// UIアニメーションの追加
	{		
		auto rotationAnimation = std::make_unique<UIRotationAnimation>();
		rotationAnimation->SetParameter(30.0f, -30.0f, 0.1f, EasingType::Linear, LoopMode::Loop);
		m_uiHourGlass->AddAnimation(Hash32("m_uiHourGlassRotationAnimation"),std::move(rotationAnimation));
		m_uiHourGlass->StopSpriteAnimation();
	}

	m_uiDigit->SetNumber(0);

	if (!m_timeKeeper)
	{
		m_timeKeeper = new TimeKeeper();
	}

	
	return true;
}


void UITimer::Update()
{
	// タイムを設定
	m_uiDigit->SetNumber(static_cast<int>(m_timer));

	// 
	if (m_timer <= 30.0f)
	{
		if (!m_isTimeLimit)
		{
			m_isTimeLimit = true;
			
			m_uiHourGlass->PlayAnimation();
			m_uiDigit->PlayAnimation();
		}
	}

	m_uiCanvas->Update();
}


void UITimer::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}