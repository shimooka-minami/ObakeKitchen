#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_modelRender.Init("Assets/modelData/Ground/ground2.tkm");
	//m_modelRender.Init("Assets/");
	m_modelRender.SetScale({ 1.0f, 1.0f, 1.0f });
	m_modelRender.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_modelRender.Update();
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

}

BackGround::~BackGround()
{
}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
