#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_modelRender.Init("Assets/modelData/Ground/ground.tkm");
	//m_modelRender.Init("Assets/");
	m_modelRender.SetScale({ 2.0f, 2.0f, 2.0f });
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
