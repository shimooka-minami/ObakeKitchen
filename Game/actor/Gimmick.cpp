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




/*************************************/


bool PointLightGimmick::Start()
{	
	m_pointLight[0] = g_sceneLight->NewPointLight();
	m_pointLight[0]->SetPosition(Vector3(m_transform.m_position.x + 15.0f, m_transform.m_position.y, m_transform.m_position.z));
	m_pointLight[0]->SetColor(Vector3(170.0f, 0.0f, 190.0f));
	m_pointLight[0]->SetRange(80.0f);
	m_pointLight[0]->SetAffectPowParam(1.0f);

	m_pointLight[1] = g_sceneLight->NewPointLight();
	m_pointLight[1]->SetPosition(Vector3(m_transform.m_position.x - 15.0f, m_transform.m_position.y, m_transform.m_position.z));
	m_pointLight[1]->SetColor(Vector3(170.0f, 0.0f, 190.0f));
	m_pointLight[1]->SetRange(80.0f);
	m_pointLight[1]->SetAffectPowParam(1.0f);

	m_pointLight[2] = g_sceneLight->NewPointLight();
	m_pointLight[2]->SetPosition(Vector3(m_transform.m_position.x, m_transform.m_position.y, m_transform.m_position.z + 15.0f));
	m_pointLight[2]->SetColor(Vector3(170.0f, 0.0f, 190.0f));
	m_pointLight[2]->SetRange(80.0f);
	m_pointLight[2]->SetAffectPowParam(1.0f);

	m_pointLight[3] = g_sceneLight->NewPointLight();
	m_pointLight[3]->SetPosition(Vector3(m_transform.m_position.x, m_transform.m_position.y, m_transform.m_position.z - 15.0f));
	m_pointLight[3]->SetColor(Vector3(170.0f, 0.0f, 190.0f));
	m_pointLight[3]->SetRange(20.0f);
	m_pointLight[3]->SetAffectPowParam(1.0f);

	m_pointLight[4] = g_sceneLight->NewPointLight();
	m_pointLight[4]->SetPosition(Vector3(m_transform.m_position.x, m_transform.m_position.y, m_transform.m_position.z));
	m_pointLight[4]->SetColor(Vector3(50.0f, 0.0f, 80.0f));
	m_pointLight[4]->SetRange(500.0f);
	m_pointLight[4]->SetAffectPowParam(3.5f);

	return true;
}


void PointLightGimmick::Update()
{
	for (int i = 0; i < 5; ++i)
	{
		m_pointLight[i]->Update();
	}
}


void PointLightGimmick::Render(RenderContext& renderContect)
{
	StaticGimmick::Render(renderContect);
}