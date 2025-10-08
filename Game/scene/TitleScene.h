/**
 * TitleScene.h
 * タイトル画面のシーン
 */
#pragma once
#include "IScene.h"


 /** タイトルシーン */
class TitleScene : public IScene
{
	appScene(TitleScene);


private:
	SpriteRender m_spriteRender;


public:
	TitleScene();
	virtual ~TitleScene();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

	virtual bool RequestScene(uint32_t& id)  override;
};

