/**
 * UITimer.cpp
 * 制限時間の表示
 */
#include "stdafx.h"
#include "UITimer.h"
#include "UIBase.h"

#include "core/TimeKeeper.h"

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
	auto* uiBackground = m_uiCanvas->CreateUI<UIIcon>();
	uiBackground->Initialize("Assets/modelData/UI/limitTime.dds", 128.0f, 30.0f, Vector3(-200.0f,0.0f,0.0f),Vector3::One, Quaternion::Identity);

	// 数字
	m_uiDigit = m_uiCanvas->CreateUI<UIDigit>();
	m_uiDigit->Initialize("Assets/modelData/UI/suji", 3, 0, 50.0f, 50.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// 砂時計
	m_uiHourGlass = m_uiCanvas->CreateUI<UIIcon>();
	m_uiHourGlass->Initialize("Assets/modelData/UI/timer.dds", 80.0f, 80.0f, Vector3(50.0f, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// UIアニメーションの追加
	{
		auto* render = m_uiHourGlass->GetSpriteRender();
		Quaternion start;
		start.SetRotationDegZ(30.0f);
		Quaternion end;
		end.SetRotationDegZ(-30.0f);
		RotationSpriteAnimation* rotationSpriteAnimation = new RotationSpriteAnimation(render, 0.1f, true, start, end);
		m_uiHourGlass->AddSpriteAnimation(rotationSpriteAnimation);
	}

	// @todo for test
	//auto* uiDigit = m_uiCanvas->CreateUI<UIDigit>();
	//uiDigit->Initialize("Assets/modelData/UI/suji", 5, 0, 50.0f, 50.0f, Vector3(-400.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	m_uiDigit->SetNumber(0);

	// 右から3番目の桁(=targetDigit = 3) を":"に変更
	//uiDigit->SetCustomChar(3, "coron.dds");


	if (!m_timeKeeper)
	{
		m_timeKeeper = new TimeKeeper();
	}

	
	return true;
}


void UITimer::Update()
{
	// @todo for test
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_uiHourGlass->PlaySpriteAnimation();
	}
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		m_uiHourGlass->StopSpriteAnimation();
	}

	// タイムを設定
	m_uiDigit->SetNumber(static_cast<int>(m_timer));

	// 
	if (m_timer <= 30.0f)
	{
		if (!m_isTimeLimit)
		{
			m_isTimeLimit = true;
			
			auto& spriteRenderList = m_uiDigit->GetSpriteRenderList();
			for (int i = 0; i < spriteRenderList.size(); ++i)
			{
				auto* render = spriteRenderList[i];
				render->SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
				ColorSpriteAnimation* alphaSpriteAnimation = new ColorSpriteAnimation(render, 1.0f, true, Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f));
				m_uiDigit->AddSpriteAnimation(alphaSpriteAnimation);
			}
			m_uiHourGlass->PlaySpriteAnimation();
			m_uiDigit->PlaySpriteAnimation();
		}
	}


	

	m_uiCanvas->Update();
}


void UITimer::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}