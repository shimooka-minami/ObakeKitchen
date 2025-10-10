/**
 * SpriteAnimation.cpp
 * SpriteRenderをアニメーションさせる機能群
 */
#include "stdafx.h"
#include "SpriteAnimation.h"


void ScaleSpriteAnimation::Update()
{
	const float deltaTime = g_gameTime->GetFrameDeltaTime();

	Vector2 targetScale;
	Vector2 baseScale;
	switch (m_currentStep)
	{
		case enAnimationStep_Min:
		{
			targetScale = m_targetScale;
			baseScale = m_baseScale;
			break;
		}
		case enAnimationStep_Max:
		{
			targetScale = m_baseScale;
			baseScale = m_targetScale;
			break;
		}
	}

	const float computePercent = m_elapsedTime / m_targetTime;

	Vector2 computeScale = baseScale;
	computeScale.Lerp(computePercent, baseScale, targetScale);

	m_render->SetScale(Vector3(computeScale.x, computeScale.y, 1.0f));

	m_elapsedTime += deltaTime;
	if (m_elapsedTime >= m_targetTime) {
		m_elapsedTime = 0.0f;
		// 三項演算子を使ったif文
		// 今の状態(Step)がMaxだった場合->Min。そうでない場合->Max
		// 例文)condition ? value_if_true : value_if_false;
		m_currentStep = m_currentStep == enAnimationStep_Max ? enAnimationStep_Min : enAnimationStep_Max;
	}
}




/*********************************************/


void ColorSpriteAnimation::Update()
{
	const float deltaTime = g_gameTime->GetFrameDeltaTime();

	Vector4 targetColor;
	Vector4 baseColor;

	switch (m_currentStep)
	{
		case enAnimationStep_Min:
		{
			targetColor = m_targetColor;
			baseColor = m_baseColor;
			break;
		}
		case enAnimationStep_Max:
		{
			targetColor = m_baseColor;
			baseColor = m_targetColor;
			break;
		}
	}

	const float computePercent = m_elapsedTime / m_targetTime;

	Vector4 computeColor = nsK2EngineLow::Math::Lerp<Vector4>(computePercent, baseColor, targetColor);

	m_render->SetMulColor(computeColor);

	m_elapsedTime += deltaTime;
	if (m_elapsedTime >= m_targetTime) {
		m_elapsedTime = 0;
		m_currentStep = m_currentStep == enAnimationStep_Min ? enAnimationStep_Max : enAnimationStep_Min;
	}
}




/***********************************************/


void AlphaSpriteAnimation::Update()
{
	const float deltaTime = g_gameTime->GetFrameDeltaTime();

	float targetAlpha;
	float baseAlpha;

	switch (m_currentStep)
	{
		case enAnimationStep_Min:
		{
			targetAlpha = m_targetAlpha;
			baseAlpha = m_baseAlpha;
			break;
		}
		case enAnimationStep_Max:
		{
			targetAlpha = m_baseAlpha;
			baseAlpha = m_targetAlpha;
			break;
		}
	}

	const float computePercent = m_elapsedTime / m_targetTime;

	float computeAlpha = nsK2EngineLow::Math::Lerp<float>(computePercent, baseAlpha, targetAlpha);

	m_render->SetMulColor(Vector4(0.0f, 0.0f, 0.0f, computeAlpha));

	m_elapsedTime += deltaTime;
	if (m_elapsedTime >= m_targetTime) {
		m_elapsedTime = 0;
		m_currentStep = m_currentStep == enAnimationStep_Min ? enAnimationStep_Max : enAnimationStep_Min;
	}
}