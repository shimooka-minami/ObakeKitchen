/**
 * ResultScene.h
 * リザルト画面のシーン
 */
#pragma once
#include "IScene.h"


/** リザルトシーン */
class ResultScene : public IScene
{
	appScene(ResultScene);


private:
	SpriteRender m_spriteRender;

	bool isRequestNext = false;


public:
	ResultScene();
	virtual ~ResultScene();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

	virtual bool RequestScene(uint32_t& id, float& waitTime)  override;
};