/**
 * UIInteractOnPlateIcon.h
 * 皿の上に食材を置くときに出るアイコン
 */

#include "stdafx.h"
#include "UIInteractIcon.h"
#include "UIBase.h"
#include <util/CRC32.h>
#include "UIInteractOnPlateIcon.h"

namespace
{
	constexpr float OFFSET_Y = 20.0f;
}

UIInteractOnPlateIcon::UIInteractOnPlateIcon()
{

}

UIInteractOnPlateIcon::~UIInteractOnPlateIcon()
{

}

bool UIInteractOnPlateIcon::Start()
{
	return true;
}

void UIInteractOnPlateIcon::Update()
{
	m_aButton->isDraw = m_isDrawAButton;

	Vector2 screenPosition;
	g_camera3D->CalcScreenPositionFromWorldPosition(screenPosition, m_position);
	m_uiCanvas->m_transform.m_localPosition = Vector3(screenPosition.x, screenPosition.y + OFFSET_Y, 0.0f);
	m_uiCanvas->Update();
}

void UIInteractOnPlateIcon::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}

void UIInteractOnPlateIcon::Initialize()
{
	// Aボタン
	m_uiCanvas = std::make_unique<UICanvas>();
	m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, 0.0f, 0.0f);

	m_aButton = m_uiCanvas->CreateUI<UIIcon>(0);
	m_aButton->Initialize("Assets/modelData/UI/inGame/abutton.dds", 30.0f, 30.0f);

	m_uiCanvas->Update();
}