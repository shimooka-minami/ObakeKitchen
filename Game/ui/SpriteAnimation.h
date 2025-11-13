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
	bool m_isLoop = false;
	bool m_isCompleted = false;	// 処理が完了したか
	// 再生するかどうか
	bool m_isPlay = false;


public:
	SpriteAnimationBase(SpriteRender* render, const float targetTime, const bool isLoop)
		: m_render(render)
		, m_targetTime(targetTime)
		, m_isLoop(isLoop)
	{
	}

	/** 純粋仮想関数 */
	virtual void Update() = 0;


	void Play()
	{
		// 再生するかどうかフラグをtrueにする
		m_isPlay = true;
		m_isCompleted = false;
		m_currentStep = enAnimationStep_Min;
		m_elapsedTime = 0.0f;

	}
	void Stop()
	{
		// 再生するかどうかフラグをfalseにする
		m_isPlay = false;
	}
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
	ScaleSpriteAnimation(SpriteRender* render, const float targetTime, const bool isLoop, const Vector2 baseScale, const Vector2 targetScale)
		: SpriteAnimationBase(render, targetTime, isLoop)
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
	ColorSpriteAnimation(SpriteRender* render, const float targetTime, const bool isLoop, const Vector4 baseColor, const Vector4 targetColor)
		: SpriteAnimationBase(render, targetTime, isLoop)
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
	AlphaSpriteAnimation(SpriteRender* render, const float targetTime, const bool isLoop, const float baseAlpha, const float targetAlpha)
		: SpriteAnimationBase(render, targetTime, isLoop)
		, m_baseAlpha(baseAlpha)
		, m_targetAlpha(targetAlpha)
	{
	}


	void Update() override;
};




/***********************************************/


/**
 * 上下左右のアニメーション
 */
class TranslateSpriteAnimation : public SpriteAnimationBase
{
private:
	Vector3 m_basePosition = Vector3::Zero;
	Vector3 m_targetPosition = Vector3::Zero;


public:
	TranslateSpriteAnimation(SpriteRender* render, const float targetTime, const bool isLoop, const Vector3 basePosition, const Vector3 targetPosition)
		: SpriteAnimationBase(render, targetTime, isLoop)
		, m_basePosition(basePosition)
		, m_targetPosition(targetPosition)
	{
	}


	void Update() override;
};





/***********************************************/


/**
 * 回転のアニメーション
 */
class RotationSpriteAnimation : public SpriteAnimationBase
{
private:
	Quaternion m_baseRotation = Quaternion::Identity;
	Quaternion m_targetRotation = Quaternion::Identity;


public:
	RotationSpriteAnimation(SpriteRender* render, const float targetTime, const bool isLoop, const Quaternion baseRotation, const Quaternion targetRotation)
		: SpriteAnimationBase(render, targetTime, isLoop)
		, m_baseRotation(baseRotation)
		, m_targetRotation(targetRotation)
	{
	}

	
	void Update() override;
};

