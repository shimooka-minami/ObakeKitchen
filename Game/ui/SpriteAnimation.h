/**
 * SpriteAnimation.h
 * SpriteRenderをアニメーションさせる機能群
 */
#pragma once


/** 基底クラス */
class SpriteAnimationBase
{
protected:
	enum EnAnimationStep
	{
		enAnimationStep_Min,
		enAnimationStep_Max
	};


protected:
	SpriteRender* m_render = nullptr;
	float m_elapsedTime = 0.0;
	float m_targetTime = 0.0f;
	EnAnimationStep m_currentStep;

public:
	SpriteAnimationBase(SpriteRender* render, const float targetTime)
		: m_render(render)
		, m_targetTime(targetTime)
	{
	}

	/** 純粋仮想関数 */
	virtual void Update() = 0;
};


/********************************************/




/**
 * 大きさを変えるアニメーション
 */
class ScaleSpriteAnimation : public SpriteAnimationBase
{
private:
	Vector2 m_baseScale = Vector2::Zero;
	Vector2 m_targetScale = Vector2::Zero;


public:
	ScaleSpriteAnimation(SpriteRender* render, const float targetTime, const Vector2 baseScale, const Vector2 targetScale)
		: SpriteAnimationBase(render, targetTime)
		, m_baseScale(baseScale)
		, m_targetScale(targetScale)
	{
	}


	void Update() override;
};




/*********************************************/


/**
 * 色を変えるアニメーション
 */
class ColorSpriteAnimation : public SpriteAnimationBase
{
private:
	Vector4 m_baseColor = Vector4::White;
	Vector4 m_targetColor = Vector4::White;


public:
	ColorSpriteAnimation(SpriteRender* render, const float targetTime, const Vector4 baseColor, const Vector4 targetColor)
		: SpriteAnimationBase(render, targetTime)
		, m_baseColor(baseColor)
		, m_targetColor(targetColor)
	{
	}


	void Update() override;
};




/***********************************************/


/**
 * 透明度を変えるアニメーション
 */
class AlphaSpriteAnimation : public SpriteAnimationBase
{
private:
	float m_baseAlpha = 0.0f;
	float m_targetAlpha = 0.0f;

	
public:
	AlphaSpriteAnimation(SpriteRender* render, const float targetTime, const float baseAlpha, const float targetAlpha)
		: SpriteAnimationBase(render,targetTime)
		, m_baseAlpha(baseAlpha)
		, m_targetAlpha(targetAlpha)
	{
	}


	void Update() override;
};