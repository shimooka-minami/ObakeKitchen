/**
 * SpriteAnimation.cpp
 * SpriteRenderをアニメーションさせる機能群
 */
#include "stdafx.h"
#include "SpriteAnimation.h"


template <typename T>
void SpriteAnimationBase::UpdateCore(std::vector<T> targetList, const std::function<void(const float, const T&, const T&)> func)
{
	const float deltaTime = g_gameTime->GetFrameDeltaTime();
	m_elapsedTime += deltaTime;

	// Step1
	// Index=0
	T valueStart = targetList[m_targetIndex];      // 値[0]
	T valueEnd = targetList[m_targetIndex + 1];    // 値[1]
	// 現在の時間何秒まで
	float targetTime = m_targetTimeList[m_targetIndex];  // 2秒(0～2秒)

	// 現在のアニメーション経過時間のパーセント
	const float computePercent = m_elapsedTime / targetTime;

	// 初期値から目標値までをなめらかに変化にRenderに設定を外から設定されるラムダ式でする
	func(computePercent, valueStart, valueEnd);
	m_render->Update();

	// 今の時間が指定した時間を超えたら
	if (m_elapsedTime >= targetTime) {
		m_targetIndex++;
		m_elapsedTime = 0.0f;

		// currentIndex(2) = 2
		if (m_targetIndex == m_targetTimeList.size()) {
			// 完了
			m_isCompleted = true;
			m_targetIndex = 0;
		}
	}

}


bool SpriteAnimationBase::CanUpdate()
{
	// 繰り返し実行するか
	if (!m_isLoop && m_isCompleted)
	{
		return false;
	}
	// 再生するかがtrueじゃなければ実行しない
	if (!m_isPlay)
	{
		return false;
	}
	return true;
}


void ScaleSpriteAnimation::Update()
{
	if (!CanUpdate()) {
		return;
	}

	UpdateCore<Vector2>(m_targetScaleList, [&](const float percent, const Vector2& startValue, const Vector2& endValue)
		{
			Vector2 value = nsK2EngineLow::Math::Lerp(percent, startValue, endValue);
			m_render->SetScale(Vector3(value.x, value.y, 0.0f));
		});

	//const float deltaTime = g_gameTime->GetFrameDeltaTime();
	//m_elapsedTime += deltaTime;

	//// Step1
	//// Index=0
	//Vector2 valueStart = m_targetScaleList[m_targetIndex];  // 値[0]
	//Vector2 valueEnd = m_targetScaleList[m_targetIndex + 1]; // 値[1]
	//// 現在の時間何秒まで
	//float targetTime = m_targetTimeList[m_targetIndex];   // 2秒(0～2秒)

	//// 現在のアニメーション経過時間のパーセント
	//const float computePercent = m_elapsedTime / targetTime;

	//// 初期値から目標値までをなめらかに変化
	//Vector2 computeScale;
	//computeScale.Lerp(computePercent, valueStart, valueEnd);

	//// 大きさを設定する
	//m_render->SetScale(Vector3(computeScale.x, computeScale.y, 1.0f));
	//m_render->Update();

	//// 今の時間が指定した時間を超えたら
	//if (m_elapsedTime >= targetTime) {
	// m_targetIndex++;
	// m_elapsedTime = 0.0f;

	// // currentIndex(2) = 2
	// if (m_targetIndex == m_targetTimeList.size()) {
	//  // 完了
	//  m_isCompleted = true;
	// }
	//}


	//// Step2
	//// Index=1
	//Vector2 valueStart = m_targetScaleList[m_targetIndex];  // 値[1]
	//Vector2 valueEnd = m_targetScaleList[m_targetIndex + 1]; // 値[2]
	//// 何秒かけて
	//float targetTime = m_targetTimeList[m_targetIndex];   // 1秒(2秒～3秒)

	//// 今の時間が指定した時間を超えたら
	//if (m_elapsedTime >= targetTime) {
	// m_targetIndex++;
	//}

	//



	//Vector2 targetScale;
	//Vector2 baseScale;
	//// ステップの切り替わりで拡縮
	//switch (m_currentStep)
	//{
	// case enAnimationStep_Min:
	// {
	//  targetScale = m_targetScale;
	//  baseScale = m_baseScale;
	//  break;
	// }
	// case enAnimationStep_Max:
	// {
	//  targetScale = m_baseScale;
	//  baseScale = m_targetScale;
	//  break;
	// }
	//}


	//// 一定時間経過したら往復
	//m_elapsedTime += deltaTime;
	//if (m_elapsedTime >= m_targetTime) {
	// m_elapsedTime = 0.0f;
	// // 三項演算子を使ったif文
	// // 今の状態(Step)がMaxだった場合->Min。そうでない場合->Max
	// // 例文)condition ? value_if_true : value_if_false;
	// m_currentStep = m_currentStep == enAnimationStep_Max ? enAnimationStep_Min : enAnimationStep_Max;

	// // 完了
	// m_isCompleted = true;
	//}
}




/*********************************************/


void ColorSpriteAnimation::Update()
{
	if (!CanUpdate()) {
		return;
	}
	UpdateCore<Vector4>(m_targetColorList, [&](const float percent, const Vector4& startValue, const Vector4& endValue)
	{
		Vector4 value = nsK2EngineLow::Math::Lerp(percent, startValue, endValue);
		m_render->SetMulColor(value);
	});
}




/***********************************************/


void TranslateSpriteAnimation::Update()
{
	if (!CanUpdate()) {
		return;
	}

	UpdateCore<Vector3>(m_targetTranslateList, [&](const float percent, const Vector3& startValue, const Vector3& endValue)
	{
		Vector3 value = nsK2EngineLow::Math::Lerp(percent, startValue, endValue);
		m_render->SetPosition(value);
	});
}




/***********************************************/


void TranslateOffsetSpriteAnimation::Update()
{
	if (!CanUpdate()) {
		return;
	}

	UpdateCore<Vector3>(m_targetOffsetList, [&](const float percent, const Vector3& startValue, const Vector3& endValue)
	{
		Vector3 value = nsK2EngineLow::Math::Lerp(percent, startValue, endValue);
		Vector3 computePosition = m_ownerTransform->m_position + value; // オフセット位置を足す
		m_render->SetPosition(computePosition);
	});
}




/*************************************************/


void RotationSpriteAnimation::Update()
{
	if (!CanUpdate()) {
		return;
	}
	UpdateCore<Quaternion>(m_targetRotationList, [&](const float percent, const Quaternion& startValue, const Quaternion& endValue)
	{
		Quaternion value = nsK2EngineLow::Math::Lerp(percent, startValue, endValue);
		m_render->SetRotation(value);
	});
}