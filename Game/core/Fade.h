/**
 * Fafde.h
 * 読み込みなどで表示するためFade処理
 */
#pragma once
#include "ui/UIAnimation.h"
#include "memory"


/**
 * Fade処理本体
 */
class Fade
{
private:
	SpriteRender m_fadeRender;
	SpriteRender m_nowloadingRender;
	SpriteRender m_iconRender;
	bool isEnable = false;

	//std::unique_ptr<TranslateSpriteAnimation> m_spriteAnimation;
	//std::unique_ptr<UIAnimation> m_uiAnimation;

private:
	Fade();
	~Fade();


public:
	void Update();
	void Render(RenderContext& rc);

	
public:
	void Enable() { isEnable = true; }
	void Disable() { isEnable = false; }



	/**
	 * シングルトン用
	 */
private:
	static Fade* m_instance;


public:
	static void Create()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Fade();
		}
	}
	static Fade& Get()
	{
		return *m_instance;
	}
	static void Delete()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};




/***************************/


class FadeObject : public IGameObject
{
public:
	FadeObject();
	virtual ~FadeObject();


	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
};