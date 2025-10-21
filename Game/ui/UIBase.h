/**
 * UIBase.h
 * UIの基盤を作る
 */
#pragma once


#include "ui/SpriteAnimation.h"
//
//enum EnUIBerSpriteKind
//{
//	enUIBerSpriteKind_Back,
//	enUIBerSpriteKind_Ber,
//	enUIBerSpriteKind_Frame,
//	enUIBerSpriteKind_Max
//};
//
//
///**
// * UI:ゲージを増加させる
// */
//class ProgrresUIBer : public SpriteAnimationBase
//{
//private:
//	float m_baseProgrresBer = 0.0f;
//	float m_targetProgrresBer = 0.0f;
//
//
//private:
//	SpriteRender m_spriteRender[enUIBerSpriteKind_Max];
//	std::unique_ptr<SpriteAnimationBase> m_buttonAnimation;
//
//
//public:
//	ProgrresUIBer();
//	virtual ~ProgrresUIBer();
//
//	bool Start();
//	virtual void Update() override;
//	virtual void UIBerAnim(); //仮
//	void Render(RenderContext& rc);
//
//
//public:
//	ProgrresUIBer(SpriteRender* render, const float targetTime, const float baseProgrresBer, const float targetProgrresBer)
//		:SpriteAnimationBase(render, targetTime)
//		, m_baseProgrresBer(baseProgrresBer)
//		, m_targetProgrresBer(targetProgrresBer)
//	{
//	}
//};


/** 基底クラス */
//class UIBase
//{
//protected:
//	enum UIStep
//	{
//		UIStep_Min,
//		UIStep_Max
//	};
//
//protected:
//	SpriteRender* m_onwer = nullptr;
//	float m_elapsedTime = 0.0;
//	float m_targetTime = 0.0f;
//
//public:
//	virtual void Update() = 0;
//
//};
