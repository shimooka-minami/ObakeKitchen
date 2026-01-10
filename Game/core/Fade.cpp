#include "stdafx.h"
#include "Fade.h"
class UIAnimation;


Fade* Fade::m_instance = nullptr;


Fade::Fade()
{
	m_fadeRender.Init("Assets/ui/fade.dds", 1920.0f, 1080.0f);
	m_fadeRender.SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));

	m_nowloadingRender.Init("Assets/ui/nowloading.dds", 256.0f, 28.0f);
	m_nowloadingRender.SetPosition(Vector3(745.0f, -400.0f, 0.0f));
	m_iconRender.Init("Assets/ui/loadingIcon.dds", 64.0f, 64.0f);
	m_iconRender.SetPosition(Vector3(900.0f, -400.0f, 0.0f));

	std::vector<Vector3> targetTranslateList = { Vector3(900.0f, -410.0f, 0.0f), Vector3(900.0f, -390.0f, 0.0f), Vector3(900.0f, -410.0f, 0.0f) };
	std::vector<float> timeList = { 1.0f,1.0f };
	//m_uiAnimation = std::make_unique<UIAnimation>(&m_iconRender, true, timeList, targetTranslateList);
	//m_uiAnimation->Play();
}


Fade::~Fade()
{
}


void Fade::Update()
{
	if (!isEnable) {
		return;
	}
	m_fadeRender.Update();
	m_nowloadingRender.Update();
	m_iconRender.Update();

	//m_uiAnimation->Update();
}


void Fade::Render(RenderContext& rc)
{
	if (!isEnable) {
		return;
	}
	m_fadeRender.Draw(rc);
	m_nowloadingRender.Draw(rc);
	m_iconRender.Draw(rc);
}




/***************************/


FadeObject::FadeObject()
{
	Fade::Create();
}


FadeObject::~FadeObject()
{
	Fade::Delete();
}


bool FadeObject::Start()
{	
	return true;
}


void FadeObject::Update()
{
	Fade::Get().Update();
}


void FadeObject::Render(RenderContext& rc)
{
	Fade::Get().Render(rc);
}