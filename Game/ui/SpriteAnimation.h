/**
 * SpriteAnimation.h
 * SpriteRenderをアニメーションさせる機能群
 */
#pragma once


 /** 基底クラス */
class SpriteAnimationBase
{
	//protected:
	// enum EnAnimationStep
	// {
	//  enAnimationStep_Min,
	//  enAnimationStep_Max
	// };
	//

protected:
	SpriteRender* m_render = nullptr;
	float m_elapsedTime = 0.0;
	std::vector<float> m_targetTimeList;    // ターゲットタイムがいっぱい入ってくる
	int m_targetIndex = 0;					// ターゲットインデックス
	bool m_isLoop = false;					// ループするかどうか
	bool m_isCompleted = false;				// 処理が完了したか
	bool m_isPlay = false;					// 再生するかどうか


public:
	SpriteAnimationBase(SpriteRender* render, const bool isLoop, std::vector<float> targetTimeList)
		: m_render(render)
		, m_isLoop(isLoop)
		, m_targetTimeList(targetTimeList)
	{
	}

	/** 純粋仮想関数 */
	virtual void Update() = 0;

	template <typename T>
	void UpdateCore(std::vector<T> targetList, const std::function<void(const float, const T&, const T&)> func);

	virtual bool CanUpdate();

	void Play()
	{
		// 再生するかどうかフラグをtrueにする
		m_isPlay = true;
		m_isCompleted = false;
		m_elapsedTime = 0.0f;
		m_targetIndex = 0;

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

	std::vector<Vector2> m_targetScaleList;   // ターゲットスケールがいっぱい入ってくる


public:
	ScaleSpriteAnimation(SpriteRender* render, const bool isLoop, std::vector<float> targetTimeList, std::vector<Vector2> targetScaleList)
		: SpriteAnimationBase(render, isLoop, targetTimeList)
		, m_targetScaleList(targetScaleList)
	{
		K2_ASSERT(m_targetScaleList.size() > 0, "値をいれてください\n");
		K2_ASSERT(m_targetScaleList.size() - 1 == m_targetTimeList.size(), "それぞれの配列設定を見直してください。\n");
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
	std::vector<Vector4> m_targetColorList;


public:
	ColorSpriteAnimation(SpriteRender* render, const bool isLoop, std::vector<float> targetTimeList, std::vector<Vector4> targetColorList)
		: SpriteAnimationBase(render, isLoop, targetTimeList)
		, m_targetColorList(targetColorList)
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
	std::vector<Vector3> m_targetTranslateList;
public:
	TranslateSpriteAnimation(SpriteRender* render, const bool isLoop, std::vector<float> targetTimeList, std::vector<Vector3> targetTranslateList)
		: SpriteAnimationBase(render, isLoop, targetTimeList)
		, m_targetTranslateList(targetTranslateList)

	{
	}


	void Update() override;
};





/***********************************************/


/**
 * 上下左右を起点としてオフセット位置で行うのアニメーション
 */
class TranslateOffsetSpriteAnimation : public SpriteAnimationBase
{
private:
	std::vector<Vector3> m_targetOffsetList;
	Transform* m_ownerTransform = nullptr;


public:
	TranslateOffsetSpriteAnimation(SpriteRender* render, const bool isLoop, std::vector<float> targetTimeList, std::vector<Vector3> targetOffsetList, Transform* ownerTransform)
		: SpriteAnimationBase(render, isLoop, targetTimeList)
		, m_targetOffsetList(targetOffsetList)
		, m_ownerTransform(ownerTransform)

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

	std::vector<Quaternion> m_targetRotationList;


public:
	RotationSpriteAnimation(SpriteRender* render, const bool isLoop, std::vector<float> targetTimeList, std::vector<Quaternion> targetRotationList)
		: SpriteAnimationBase(render, isLoop, targetTimeList)
		, m_targetRotationList(targetRotationList)
	{
	}


	void Update() override;
};

