/**
 * UIAnimation.cpp
 * UIAnimationをアニメーションさせる機能群
 */
#include "stdafx.h"
#include "UIAnimation.h"
#include "UIBase.h"

UIColorVector4Animation::UIColorVector4Animation() {
	SetFunc([&](Vector4 v) {
		m_ui->m_color = v;
		});
}

/*******************************************************/


UIScaleVector3Animation::UIScaleVector3Animation() {
	SetFunc([&](Vector3 s) {
		m_ui->m_transform.m_localScale = s;
		m_ui->m_transform.UpdateTransform();
		});
}




UITranslateVector3Aniamtion::UITranslateVector3Aniamtion()
{
	SetFunc([&](Vector3 s) {
		m_ui->m_transform.m_localPosition = s;
		m_ui->m_transform.UpdateTransform();
		});
}




UIRotationAnimation::UIRotationAnimation()
{
	SetFunc([&](float s) {
		Quaternion q;
		q.SetRotationDegY(s);
		m_ui->m_transform.m_localRotation = q;
		m_ui->m_transform.UpdateTransform();
		});
}