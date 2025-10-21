/**
 * Gimmick.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#include "stdafx.h"
#include "Gimmick.h"


Gimmick::Gimmick()
{

}


Gimmick::~Gimmick()
{

}


bool Gimmick::Start()
{
	return true;
}


void Gimmick::Update()
{
}


void Gimmick::Render(RenderContext& renderContect)
{
}


void Gimmick::Initialize(const char* assetName, const Vector3& position, const Vector3& scale, const Quaternion& rotation)
{
	m_transform.m_localPosition = position;
	m_transform.m_localScale = scale;
	m_transform.m_localRotation = rotation;
	m_transform.UpdateTransform();

	m_modelRender.Init(assetName);
	m_modelRender.SetTRS(position, rotation, scale);
	m_modelRender.Update();
}




/*************************************/


bool StaticGimmick::Start()
{
	return true;
}


void StaticGimmick::Update()
{

}


void StaticGimmick::Render(RenderContext& renderContect)
{
	m_modelRender.Draw(renderContect);
}


void StaticGimmick::Initialize(const char* assetName, const Vector3& position, const Vector3& scale, const Quaternion& rotation)
{
	Gimmick::Initialize(assetName, position, scale, rotation);

	m_physicalObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix(), 0.0f);
}