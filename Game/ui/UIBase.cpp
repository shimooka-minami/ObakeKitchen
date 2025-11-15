/**
 * UIBase.cpp
 * UIの基本的な処理をするクラス群
 */
#include "stdafx.h"
#include "UIBase.h"
#include "SpriteAnimation.h"


void UIBase::PlaySpriteAnimation()
{
	for (auto* animation : m_spriteAnimationList)
	{
		animation->Play();
	}
}


void UIBase::StopSpriteAnimation()
{
	for (auto* animation : m_spriteAnimationList)
	{
		animation->Stop();
	}
}




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
	// @todo for test
	float m_uiGargeMid = 0.0f;

	m_transform.UpdateTransform();
	m_spriteRender.SetPosition(m_transform.m_position);
	m_spriteRender.SetScale(m_transform.m_scale);
	m_spriteRender.SetRotation(m_transform.m_rotation);
	m_spriteRender.Update();
}


void UIGauge::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}


void UIGauge::Initialize(const char* assetName, const float width, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation)
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

	for (auto* animation : m_spriteAnimationList) {
		animation->Update();
	}
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




/********************************/


UIDigit::UIDigit()
{
}


UIDigit::~UIDigit()
{
}


bool UIDigit::Start()
{
	return true;
}


void UIDigit::Update()
{
	if (m_number != m_requestNumber) {
		m_number = m_requestNumber;
		for (int i = 0; i < m_digit; ++i) {
			UpdateNumber(i+1, m_number);
		}
	}


	m_transform.UpdateTransform();
	for (int i = 0; i < m_renderList.size(); ++i)
	{
		auto* spriteRender = m_renderList[i];
		UpdatePosition(i);
		spriteRender->SetScale(m_transform.m_scale);
		spriteRender->SetRotation(m_transform.m_rotation);
		spriteRender->Update();
	}

	for (auto* animation : m_spriteAnimationList) {
		animation->Update();
	}
}


void UIDigit::Render(RenderContext& rc)
{
	for (SpriteRender* spriteRender : m_renderList)
	{
		spriteRender->Draw(rc);
	}
}

void UIDigit::Initialize(const char* assetName, const int digit, const int number, const float widht, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation)
{
	m_assetPath = assetName;
	m_digit = digit;
	m_number = number;
	w = widht;
	h = height;

	m_transform.m_localPosition = position;
	m_transform.m_localScale = scale;
	m_transform.m_localRotation = rotation;

	for (int i = 0; i < digit; i++)
	{
		//SpriteRender* spriteRender = new SpriteRender;
		////spriteRender->Init(assetName, widht, height);
		//spriteRender->SetPosition(position);
		//spriteRender->SetScale(scale);
		//spriteRender->SetRotation(rotation);
		//m_renderList.push_back(spriteRender);
		UpdateNumber(i+1, m_number);	// 桁なので＋１する
	}
}


// @todo for test
//void UIDigit::SetCustomChar(int targetDigit, const std::string& assetPath)
//{
//	K2_ASSERT(targetDigit >= 1, "桁指定が間違えています。\n");
//
//	int targetIndex = targetDigit - 1;
//	if (targetIndex >= m_renderList.size())
//	{
//		return; // 範囲外
//	}
//
//	SpriteRender* render = m_renderList[targetIndex];
//	std::string assetName = m_assetPath + "/" + assetPath; // coron.dds
//	render->Init(assetName.c_str(), w, h);
//}

void UIDigit::UpdateNumber(const int targetDigit, const int number)
{
	// NOTE: targetDigitは1以上の値になっている
	K2_ASSERT(targetDigit >= 1, "桁指定が間違えています。\n");

	// いらない
	const int targetRenderIndex = targetDigit - 1;
	SpriteRender* nextRender = nullptr;
	// 次のやつをつくる
	if (targetRenderIndex < m_renderList.size()) {
		nextRender = m_renderList[targetRenderIndex];
	} else {
		nextRender = new SpriteRender();
		m_renderList.push_back(nextRender);
	}

	// 対象の桁の数字
	const int targetDigitNumber = GetDigit(targetDigit);
	// Assets/modelData/UI/suji + "0.dds" ここを変更できるようにする
	std::string assetNname = m_assetPath + "/0.dds";
	// Assets/modelData/UI/suji/0.dds
	// 数字の部分を桁の数字で変える
	assetNname[assetNname.size() - 5] = '0' + targetDigitNumber;
	nextRender->Init(assetNname.c_str(), w, h);
}


void UIDigit::UpdatePosition(const int index)
{
	SpriteRender* render = m_renderList[index];
	Vector3 position = m_transform.m_position;
	position.x -= w * index;
	render->SetPosition(position);
}


int UIDigit::GetDigit(int digit)
{
	// NOTE: targetDigitは1以上の値になっている
	K2_ASSERT(digit >= 1, "桁指定が間違えています。\n");
	digit -= 1;
	int divisor = static_cast<int>(pow(10, digit));
	return (m_number / divisor) % 10;
}




/************************************/


UICanvas::UICanvas()
{
	m_uiList.clear();
}


UICanvas::~UICanvas()
{
	for(auto* ui : m_uiList) {
		// トランスフォームの親子関係を解除
		m_transform.RemoveChild(&ui->m_transform);
		// キャンバス上にあるUIを削除
		delete ui;
		ui = nullptr;
	}
	m_uiList.clear();
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