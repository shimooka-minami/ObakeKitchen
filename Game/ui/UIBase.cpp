/**
 * UIBase.cpp
 * UIBaseを作る
 */
#include "stdafx.h"
#include "UIBase.h"

//
//namespace
//{
//	constexpr float BER_SPRITE_WIDTH = 500.0f;
//	constexpr float BER_SPRITE_HIGHT = 100.0f;
//
//	struct UIBerSprite
//	{
//		std::string assetPath;
//		Vector3 position;
//		float width;
//		float hight;
//
//		UIBerSprite(const std::string& path, const Vector3& pos, const float width, const float hight)
//			: assetPath(path)
//			, position(pos)
//			, width(width)
//			, hight(hight)
//		{
//		}
//	};
//
//	static const UIBerSprite UIBerSpriteList[enUIBerSpriteKind_Max] = {
//		UIBerSprite("Assets/modelData/UI/Ber/ber.dds",Vector3::Zero,BER_SPRITE_WIDTH,BER_SPRITE_HIGHT),
//		UIBerSprite("Assets/modelData/UI/Ber/ber_mid.dds",Vector3::Zero,BER_SPRITE_WIDTH,BER_SPRITE_HIGHT),
//		UIBerSprite("Assets/modelData/UI/Ber/ber.dds_waku",Vector3::Zero,BER_SPRITE_WIDTH,BER_SPRITE_HIGHT),
//	};
//	
//}
//
//
//bool ProgrresUIBer::Start()
//{
//	// 画像を読み込んで画面に出す準備
//	for (int i = 0; i < enUIBerSpriteKind_Max; i++)
//	{
//		const auto& info = UIBerSpriteList[i];
//		m_spriteRender[i].Init(info.assetPath.c_str(), info.width, info.hight);
//		m_spriteRender[i].SetPosition(info.position);
//	}
//
//	m_buttonAnimation = std::make_unique<ProgrresUIBer>(&m_spriteRender[enUIBerSpriteKind_Ber], 3.0f, Vector2(1.0f, 1.0f), 0.0f);
//
//	return true;
//}
//
//
//void ProgrresUIBer::Update()
//{
//	m_buttonAnimation->Update();
//
//	UIBerAnim();
//
//	for (int i = 0; i < enUIBerSpriteKind_Max; i++)
//	{
//		m_spriteRender[i].Update();
//	}
//}
//
//
//void ProgrresUIBer::UIBerAnim()
//{
//	const float deltaTime = g_gameTime->GetFrameDeltaTime();
//
//	Vector2 targetProgrresBer;
//	Vector2 baseProgrresBer;
//
//	const float computePercent = m_elapsedTime / m_targetTime;
//
//	Vector2 computeProgrresBer = baseProgrresBer;
//	computeProgrresBer.Lerp(computePercent, baseProgrresBer, targetProgrresBer);
//
//	m_render->SetScale(Vector3(computeProgrresBer.x, 1.0f, 1.0f));
//
//	m_elapsedTime += deltaTime;
//}
//
//
//void ProgrresUIBer::Render(RenderContext& rc)
//{
//	for (int i = 0; i < enUIBerSpriteKind_Max; i++)
//	{
//		m_spriteRender[i].Draw(rc);
//	}
//}


//void ProgressBer::Update()
//{
//	
//}