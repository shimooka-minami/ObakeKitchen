///**
// * UIInteractIcon.cpp
// * 調理場と納品場のアイコン
// */
//#include "stdafx.h"
//#include "UIInteractIcon.h"
//#include "UIBase.h"
//
//
//namespace
//{
//	constexpr float OFFSET_Y = 50.0f;
//}
//
//
//UIInteractIcon::UIInteractIcon()
//{
//}
//
//
//UIInteractIcon::~UIInteractIcon()
//{
//}
//
//
//bool UIInteractIcon::Start()
//{
//	// 初期化はInitializeでするので、ここではしない
//	return true;
//}
//
//
//void UIInteractIcon::Update()
//{
//	Vector2 screenPosition;
//	g_camera3D->CalcScreenPositionFromWorldPosition(screenPosition, m_position);
//	m_uiCanvas->m_transform.m_localPosition = Vector3(screenPosition.x, screenPosition.y + OFFSET_Y, 0.0f);
//	m_uiCanvas->Update();
//}
//
//
//void UIInteractIcon::Render(RenderContext& rc)
//{
//	m_uiCanvas->Render(rc);
//}
//
//
//void UIInteractIcon::Initialize(const EnInteractType type, const Vector3& position)
//{
//	std::string path;
//
//	if (type == enInteractType_Cooking)
//	{
//		path = "Assets/modelData/UI/inGame/knife.dds";
//	}
//	else if (type == enInteractType_Delivery)
//	{
//		path = "Assets/modelData/UI/inGame/nouhin.dds";
//	}
//
//	m_uiCanvas = new UICanvas();
//	m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, 0.0f, 0.0f);
//
//	// 吹き出しとアイコンで同じアニメーション設定にする
//	std::vector<Vector3> targetTranslateList = { position + Vector3(0.0f,0.0f,0.0f), position + Vector3(0.0f,100.0f,0.0f), position + Vector3(0.0f,0.0f,0.0f) };
//	std::vector<float> timeList = { 1.5f,1.5f };
//
//	// 吹き出し
//	auto* backGround = m_uiCanvas->CreateUI<UIIcon>();
//	backGround->Initialize("Assets/modelData/UI/inGame/hukidashi.dds", 100.0f, 100.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
//	{
//		auto* render = backGround->GetSpriteRender();
//		TranslateSpriteAnimation* translateSpriteAnimation = new TranslateSpriteAnimation(render, true, timeList, targetTranslateList);
//		backGround->AddSpriteAnimation(translateSpriteAnimation);
//		backGround->PlaySpriteAnimation();
//	}
//	// アイコン
//	auto* interactIcon = m_uiCanvas->CreateUI<UIIcon>();
//	interactIcon->Initialize(path.c_str(), 50.0f, 50.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
//	{
//		auto* render = interactIcon->GetSpriteRender();
//		TranslateSpriteAnimation* translateSpriteAnimation = new TranslateSpriteAnimation(render, true, timeList, targetTranslateList);
//		interactIcon->AddSpriteAnimation(translateSpriteAnimation);
//		interactIcon->PlaySpriteAnimation();
//	}
//
//	m_position = position;
//}




/**
 * UIInteractIcon.cpp
 * 調理場と納品場のアイコン
 */
#include "stdafx.h"
#include "UIInteractIcon.h"
#include "UIBase.h"


namespace
{
	constexpr float OFFSET_Y = 50.0f;
}


UIInteractIcon::UIInteractIcon()
{
}


UIInteractIcon::~UIInteractIcon()
{
}


bool UIInteractIcon::Start()
{
	// 初期化はInitializeでするので、ここではしない
	return true;
}


void UIInteractIcon::Update()
{
	Vector2 screenPosition;
	g_camera3D->CalcScreenPositionFromWorldPosition(screenPosition, m_position);
	m_uiCanvas->m_transform.m_localPosition = Vector3(screenPosition.x, screenPosition.y + OFFSET_Y, 0.0f);
	m_uiCanvas->Update();
}


void UIInteractIcon::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}


void UIInteractIcon::Initialize(const EnInteractType type, const Vector3& position)
{
	std::string path;

	if (type == enInteractType_Cooking)
	{
		path = "Assets/modelData/UI/inGame/knife.dds";
	}
	else if (type == enInteractType_Delivery)
	{
		path = "Assets/modelData/UI/inGame/nouhin.dds";
	}

	m_uiCanvas = new UICanvas();
	m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, 0.0f, 0.0f);

	// 吹き出しとアイコンで同じアニメーション設定にする
	std::vector<Vector3> targetTranslateList = { Vector3(0.0f,70.0f,0.0f), Vector3(0.0f,100.0f,0.0f), Vector3(0.0f,70.0f,0.0f) };
	std::vector<float> timeList = { 1.8f, 1.8f };

	auto* backGround = m_uiCanvas->CreateUI<UIIcon>();
	backGround->Initialize("Assets/modelData/UI/inGame/hukidashi.dds", 100.0f, 100.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
	{
		auto* render = backGround->GetSpriteRender();
		TranslateOffsetSpriteAnimation* translateSpriteAnimation = new TranslateOffsetSpriteAnimation(render, true, timeList, targetTranslateList, &backGround->m_transform);
		backGround->AddSpriteAnimation(translateSpriteAnimation);
		backGround->PlaySpriteAnimation();
	}

	auto* interactIcon = m_uiCanvas->CreateUI<UIIcon>();
	interactIcon->Initialize(path.c_str(), 50.0f, 50.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
	{
		auto* render = interactIcon->GetSpriteRender();
		TranslateOffsetSpriteAnimation* translateSpriteAnimation = new TranslateOffsetSpriteAnimation(render, true, timeList, targetTranslateList, &interactIcon->m_transform);
		interactIcon->AddSpriteAnimation(translateSpriteAnimation);
		interactIcon->PlaySpriteAnimation();
	}

	m_position = position;
}