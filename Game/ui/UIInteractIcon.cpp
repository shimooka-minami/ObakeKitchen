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

	// 始めの位置
	const Vector3 START_VEC = { 0.0f, -0.5f, 0.0f };

	// 終わりの位置
	const Vector3 END_VEC = { 0.0f, 0.5f, 0.0f };
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
	m_aButton->isDraw = m_isDrawAButton;

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
	// インタラクトアイコン
	std::string path;
	std::string pathB;
	// 吹き出し
	std::string backPath;
	std::string backPathB;
	// Aボタン
	std::string buttonPath;

	if (type == enInteractType_Cooking)
	{
		path = "Assets/modelData/UI/inGame/knife.dds";
		backPath = "Assets/modelData/UI/inGame/hukidashi.dds";
		buttonPath = "Assets/modelData/UI/inGame/abutton.dds";
	}
	else if (type == enInteractType_Delivery)
	{
		path = "Assets/modelData/UI/inGame/nouhin.dds";
		backPath = "Assets/modelData/UI/inGame/hukidashi.dds";
		buttonPath = "Assets/modelData/UI/inGame/abutton.dds";
	}
	else if (type == enInteractType_Plate)
	{
		path = "Assets/modelData/UI/inGame/plate.dds";
		backPath = "Assets/modelData/UI/inGame/hukidashi.dds";
		buttonPath = "Assets/modelData/UI/inGame/abutton.dds";
	}

	m_uiCanvas = std::make_unique<UICanvas>();
	m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, 0.0f, 0.0f);

	// 吹き出しとアイコンで同じアニメーション設定にする
	std::vector<Vector3> targetTranslateList = { Vector3(0.0f,70.0f,0.0f), Vector3(0.0f,100.0f,0.0f), Vector3(0.0f,70.0f,0.0f) };
	std::vector<float> timeList = { 1.8f, 1.8f };

	// 吹き出し
	Vector3 backGroundPosition = type == enInteractType_Cooking ? Vector3::Zero : Vector3(100.0f, 0.0f, 0.0f);
	auto* backGround = m_uiCanvas->CreateUI<UIIcon>();
	backGround->Initialize(backPath.c_str(), 100.0f, 100.0f, backGroundPosition, Vector3::One, Quaternion::Identity);
	{
		/*auto* render = backGround->GetSpriteRender();
		TranslateOffsetSpriteAnimation* translateSpriteAnimation = new TranslateOffsetSpriteAnimation(render, true, timeList, targetTranslateList, &backGround->m_transform);
		backGround->AddSpriteAnimation(translateSpriteAnimation);
		backGround->PlaySpriteAnimation();*/

		auto translateAnimation = std::make_unique<UIOffsetVector3Animation>();
		translateAnimation->SetParameter(START_VEC, END_VEC, 2.0f, EasingType::Linear, LoopMode::PingPong);
		backGround->SetUIAnimation(std::move(translateAnimation));
		backGround->PlayAnimation();
	}

	// インタラクトアイコン
	Vector3 interactPosition = type == enInteractType_Cooking ? Vector3(-5.0f, 3.0f, 0.0f) : Vector3(100.0f, 5.0f, 0.0f);
	auto* interactIcon = m_uiCanvas->CreateUI<UIIcon>();
	interactIcon->Initialize(path.c_str(), 55.0f, 55.0f, interactPosition, Vector3::One, Quaternion::Identity);
	{
		/*auto* render = interactIcon->GetSpriteRender();
		TranslateOffsetSpriteAnimation* translateSpriteAnimation = new TranslateOffsetSpriteAnimation(render, true, timeList, targetTranslateList, &interactIcon->m_transform);
		interactIcon->AddSpriteAnimation(translateSpriteAnimation);
		interactIcon->PlaySpriteAnimation();*/

		auto translateAnimation = std::make_unique<UIOffsetVector3Animation>();
		translateAnimation->SetParameter(START_VEC, END_VEC, 2.0f, EasingType::Linear, LoopMode::PingPong);
		interactIcon->SetUIAnimation(std::move(translateAnimation));
		interactIcon->PlayAnimation();
	}

	// Aボタン
	Vector3 buttonPosition = type == enInteractType_Cooking ? Vector3(35.0f, -33.0f, 0.0f) : Vector3(135.0f, -33.0f, 0.0f);
	m_aButton = m_uiCanvas->CreateUI<UIIcon>();
	m_aButton->Initialize(buttonPath.c_str(), 30.0f, 30.0f, buttonPosition, Vector3::One, Quaternion::Identity);
	{
		/*auto* render = m_aButton->GetSpriteRender();
		TranslateOffsetSpriteAnimation* translateSpriteAnimation = new TranslateOffsetSpriteAnimation(render, true, timeList, targetTranslateList, &m_aButton->m_transform);
		m_aButton->AddSpriteAnimation(translateSpriteAnimation);
		m_aButton->PlaySpriteAnimation();*/

		auto translateAnimation = std::make_unique<UIOffsetVector3Animation>();
		translateAnimation->SetParameter(START_VEC, END_VEC, 2.0f, EasingType::Linear, LoopMode::PingPong);
		m_aButton->SetUIAnimation(std::move(translateAnimation));
		m_aButton->PlayAnimation();
	}
	
	m_position = position;
}