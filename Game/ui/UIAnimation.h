/**
 * UIAnimation.h
 * UIAnimationをアニメーションさせる機能群
 */
#pragma once
#include "Util/Curve.h"

class UIBase;

template <typename T> 
using UIAnimationApplyFunc = std::function<void(const T&)>;

class UIAnimationBase
{
protected:
	UIBase* m_ui = nullptr;


public:
	UIAnimationBase() {}
	~UIAnimationBase() {}

	virtual void Update() = 0;
	virtual void Play() = 0;
	virtual bool IsPlay() = 0;

	void SetUI(UIBase* ui) { m_ui = ui; }
};


/** 2Dアニメーション */
class  UIVector2Animation : public UIAnimationBase
{
private:
	Vector2Curve m_curve;
	/** カーブ用のパラメーター */
	Vector2 m_start = Vector2::Zero;
	Vector2 m_end = Vector2::Zero;
	float m_timeSec = 0.0f;
	EasingType m_type = EasingType::Linear;
	LoopMode m_loopMode = LoopMode::Once;

	UIAnimationApplyFunc<Vector2> m_applyFunc;


public:
	UIVector2Animation();
	~UIVector2Animation();

	/** 更新 */
	void Update() override
	{
		m_curve.Update(g_gameTime->GetFrameDeltaTime());
		m_applyFunc(m_curve.GetCurrentValue());
	}

	/** 再生 */
	void Play() override
	{
		m_curve.Play(m_start, m_end, m_timeSec, m_type, m_loopMode);
	}

	/** 再生してるか */
	bool IsPlay() override
	{
		return m_curve.IsPlaying();
	}

	/** UIアニメーションの情報を設定 */
	void SetParameter(Vector2 start, Vector2 end, float timeSec, EasingType type, LoopMode loopMode)
	{
		m_start = start;
		m_end = end;
		m_timeSec = timeSec;
		m_type = type;
		m_loopMode = loopMode;
		m_curve.Play(start, end, timeSec, type, loopMode);
	}

	/** アニメーション中の現在の値を取得 */
	Vector2 GetCurrentValue()
	{
		return m_curve.GetCurrentValue();
	}

	/** アニメーション後の情報を適用する関数を設定 */
	void SetFunc(const UIAnimationApplyFunc<Vector2>& func)
	{
		m_applyFunc = func;
	}
};




/***************************************/


/** Vector3のアニメーション(position, scale~~) */
class UIVector3Animation : public UIAnimationBase
{
protected:
	Vector3Curve m_curve;
	/** カーブ用のパラメーター */
	Vector3 m_start = Vector3::Zero;
	Vector3 m_end = Vector3::Zero;
	float m_timeSec = 0.0f;
	EasingType m_type = EasingType::Linear;
	LoopMode m_loopMode = LoopMode::Once;

	UIAnimationApplyFunc<Vector3> m_applyFunc;


public:
	UIVector3Animation() {}
	~UIVector3Animation() {}

	void Update() override
	{
		m_curve.Update(g_gameTime->GetFrameDeltaTime());
		m_applyFunc(m_curve.GetCurrentValue());
	}

	void Play() override
	{
		m_curve.Play(m_start, m_end, m_timeSec, m_type, m_loopMode);
	}

	bool IsPlay() override
	{
		return m_curve.IsPlaying();
	}

	void SetParameter(Vector3 start, Vector3 end, float timeSec, EasingType type, LoopMode loopMode)
	{
		m_start = start;
		m_end = end;
		m_timeSec = timeSec;
		m_type = type;
		m_loopMode = loopMode;
		m_curve.Play(start, end, timeSec, type, loopMode);
	}

	Vector3 GetCurrentValue()
	{
		return m_curve.GetCurrentValue();
	}

	void SetFunc(const UIAnimationApplyFunc<Vector3>& func)
	{
		m_applyFunc = func;
	}
};




/*****************************************/


/** Vector4のアニメーション(color~~) */
class UIVector4Animation : public UIAnimationBase
{
protected:
	Vector4Curve m_curve;
	/** カーブ用のパラメーター */
	Vector4 m_start = Vector4::White;
	Vector4 m_end = Vector4::White;
	float m_timeSec = 0.0f;
	EasingType m_type = EasingType::Linear;
	LoopMode m_loopMode = LoopMode::Once;

	UIAnimationApplyFunc<Vector4> m_applyFunc;

public:
	UIVector4Animation() {}
	~UIVector4Animation() {}
	
	void Update() override
	{
		m_curve.Update(g_gameTime->GetFrameDeltaTime());
		m_applyFunc(m_curve.GetCurrentValue());
	}

	void Play() override
	{
		m_curve.Play(m_start, m_end, m_timeSec, m_type, m_loopMode);
	}

	bool IsPlay() override
	{
		return m_curve.IsPlaying();
	}

	void SetParameter(Vector4 start, Vector4 end, float timeSec, EasingType type, LoopMode loopMode)
	{
		m_start = start;
		m_end= end;
		m_timeSec = timeSec;
		m_type = type;
		m_loopMode = loopMode;
		m_curve.Play(start, end, timeSec, type, loopMode);
	}


	Vector4 GetCurrendtValue()
	{
		return m_curve.GetCurrentValue();
	}

	void SetFunc(const UIAnimationApplyFunc<Vector4>& func)
	{
		m_applyFunc = func;
	}
};


class UIQuaternionAnimation : public UIAnimationBase
{
protected:
	QuaternionCurve m_curve;
	/** カーブ用のパラメーター */
	Quaternion m_start = Quaternion::Identity;
	Quaternion m_end = Quaternion::Identity;
	float m_timeSec = 0.0f;
	EasingType m_type = EasingType::Linear;
	LoopMode m_loopMode = LoopMode::Once;

	UIAnimationApplyFunc<Quaternion> m_applyFunc;

public:
	UIQuaternionAnimation() {}
	~UIQuaternionAnimation() {}

	void Update() override
	{
		m_curve.Update(g_gameTime->GetFrameDeltaTime());
		m_applyFunc(m_curve.GetCurrentValue());
	}

	void Play() override
	{
		m_curve.Play(m_start, m_end, m_timeSec, m_type, m_loopMode);
	}

	bool IsPlay() override
	{
		return m_curve.IsPlaying();
	}

	void SetParameter(Quaternion start, Quaternion end, float timeSec, EasingType type, LoopMode loopMode)
	{
		m_start = start;
		m_end = end;
		m_timeSec = timeSec;
		m_type = type;
		m_loopMode = loopMode;
		m_curve.Play(start, end, timeSec, type, loopMode);
	}


	Quaternion GetCurrendtValue()
	{
		return m_curve.GetCurrentValue();
	}

	void SetFunc(const UIAnimationApplyFunc<Quaternion>& func)
	{
		m_applyFunc = func;
	}
};


/** 色変更 */
class UIColorAnimation : public UIVector4Animation
{
public:
	UIColorAnimation();
	~UIColorAnimation() {}

	void Update() override
	{
		m_curve.Update(g_gameTime->GetFrameDeltaTime());
		m_applyFunc(m_curve.GetCurrentValue());
	}
};

/** 大きさ変更 */
class UIScaleAnimation : public UIVector3Animation
{
public:
	UIScaleAnimation();
	~UIScaleAnimation() {}

	void Update() override
	{
		m_curve.Update(g_gameTime->GetFrameDeltaTime());
		m_applyFunc(m_curve.GetCurrentValue());
	}
};

/** 座標変更 */
class UITranslateAniamtion : public UIVector3Animation
{
public:
	UITranslateAniamtion();
	~UITranslateAniamtion() {}

	void Update() override
	{
		m_curve.Update(g_gameTime->GetFrameDeltaTime());
		m_applyFunc(m_curve.GetCurrentValue());
	}
};

/** 元座標との差分変更 */
class UIOffsetAnimation : public UIVector3Animation
{
public:
	UIOffsetAnimation();
	~UIOffsetAnimation() {}

	void Update() override
	{
		m_curve.Update(g_gameTime->GetFrameDeltaTime());
		m_applyFunc(m_curve.GetCurrentValue());
	}
};

/** 回転変更 */
class UIRotationAnimation : public UIQuaternionAnimation
{
public:
	UIRotationAnimation();
	~UIRotationAnimation() {}

	void Update() override
	{
		m_curve.Update(g_gameTime->GetFrameDeltaTime());
		m_applyFunc(m_curve.GetCurrentValue());
	}

};