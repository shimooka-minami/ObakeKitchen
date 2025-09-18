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