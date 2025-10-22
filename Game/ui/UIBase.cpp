/**
 * UIBase.cpp
 * UIの基本的な処理をするクラス群
 */
#include "stdafx.h"
#include "UIBase.h"



 // ============================================
 // 画像を使うUI関連
 // ============================================


UIImage::UIImage()
{
}


UIImage::~UIImage()
{
}

bool UIImage::Start()
{
	return true;
}


void UIImage::Update()
{
}


void UIImage::Render(RenderContext& rc)
{
}

/************************************/

UIGauge::UIGauge()
{
}


UIGauge::~UIGauge()
{
}

bool UIGauge::Start()
{
	return true;
}


void UIGauge::Update()
{
}


void UIGauge::Render(RenderContext& rc)
{
}


/************************************/


UIIcon::UIIcon()
{
}

UIIcon::~UIIcon()
{
}

bool UIIcon::Start()
{
	return true;
}


void UIIcon::Update()
{
	m_transform.UpdateTransform();
	m_spriteRender.SetPosition(m_transform.m_position);
	m_spriteRender.SetScale(m_transform.m_scale);
	m_spriteRender.SetRotation(m_transform.m_rotation);
	m_spriteRender.Update();
}


void UIIcon::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}

void UIIcon::Initialize(const char* assetName, const float width, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation)
{
	m_transform.m_localPosition = position;
	m_transform.m_localScale = scale;
	m_transform.m_localRotation = rotation;

	m_spriteRender.Init(assetName, width, height);
	m_spriteRender.SetPosition(position);
	m_spriteRender.SetScale(scale);
	m_spriteRender.SetRotation(rotation);
	m_spriteRender.Update();
}


/************************************/


UICanvas::UICanvas()
{
}


UICanvas::~UICanvas()
{
}


bool UICanvas::Start()
{
	return true;
}


void UICanvas::Update()
{
	m_transform.UpdateTransform();

	for (auto* ui : m_uiList) {
		ui->Update();
	}
}


void UICanvas::Render(RenderContext& rc)
{
	for (auto* ui : m_uiList) {
		ui->Render(rc);
	}
}