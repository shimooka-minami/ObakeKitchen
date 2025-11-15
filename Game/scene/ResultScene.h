/**
 * ResultScene.h
 * リザルト画面のシーン
 */
#pragma once
#include "IScene.h"

class UICanvas;
class UIIcon;

/** リザルトシーン */
class ResultScene : public IScene
{
	appScene(ResultScene);


private:
	SpriteRender m_spriteRender;
	UICanvas* m_uiCanvas = nullptr;
	UIIcon* m_uiIcon = nullptr;

	bool isRequestNext = false;


public:
	ResultScene();
	virtual ~ResultScene();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

	virtual bool RequestScene(uint32_t& id, float& waitTime)  override;
};