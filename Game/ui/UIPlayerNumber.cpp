/**
 * UIPlayerNumber.cpp
 * プレイヤーのアイコン
 */
#include "stdafx.h"
#include "UIPlayerNumber.h"
#include "UIBase.h"


namespace
{
	constexpr float OFFSET_Y = 50.0f;
}


UIPlayerNumber::UIPlayerNumber()
{
}


UIPlayerNumber::~UIPlayerNumber()
{
}


bool UIPlayerNumber::Start()
{
	// 初期化はInitializeでするので、ここではしない
	return true;
}


void UIPlayerNumber::Update()
{
	Vector2 screenPosition;
	g_camera3D->CalcScreenPositionFromWorldPosition(screenPosition, m_position);
	m_uiCanvas->m_transform.m_localPosition = Vector3(screenPosition.x, screenPosition.y + OFFSET_Y, 0.0f);
	m_uiCanvas->Update();
}


void UIPlayerNumber::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}


void UIPlayerNumber::Initialize(const int number)
{
	m_playerNumber = number;

	std::string path = "Assets/modelData/UI/Player/1P.dds";
	path[path.size() - 6] = '0' + number;
	// コントローラーが接続されてない場合は0
	if (number <= 0)
	{
		// npcの文字を表示
		path = "Assets/modelData/UI/Player/npc.dds";
	}

	m_uiCanvas = new UICanvas();
	m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, 0.0f, 0.0f);
	auto* icon = m_uiCanvas->CreateUI<UIIcon>(0);
	icon->Initialize(path.c_str(), 50.0f, 50.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
}