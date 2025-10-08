/**
 * BootScene.h
 * 起動画面のシーン
 */
#pragma once
#include "IScene.h"


/** 起動シーン */
class BootScene : public IScene
{
	appScene(BootScene);


private:
	SpriteRender* m_spriteRender;
	float m_elapsedTime = 0.0f;
	float m_changeTime = 0.0f;
	float m_shortChangeTime = 0.0f;
	int m_currentIndex = 0;


public:
	BootScene();
	virtual ~BootScene();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

	virtual bool RequestScene(uint32_t& id)  override;


private:
	void Change();

	bool CanChange() const;
};

