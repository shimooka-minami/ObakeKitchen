/**
 * ResultScene.h
 * リザルト画面のシーン
 */
#pragma once
#include "IScene.h"
#include <core/TaskSchedulerSystem.h>

class UICanvas;
class UIIcon;
class UIScore;
class UIDigit;

/** リザルトシーン */
class ResultScene : public IScene
{
	appScene(ResultScene);


private:
	SpriteRender m_spriteRender;

	UICanvas* m_uiCanvas = nullptr;

	UIIcon* m_uiIcon = nullptr;
	UIIcon* m_uiText = nullptr;
	UIIcon* m_backObake = nullptr;

	UIScore* m_uiScore = nullptr;

	UIDigit* m_uiDigit = nullptr;

	std::array<UIIcon*, 3> m_starList;
	std::array<UIIcon*, 3> m_starEffectList;
	std::unique_ptr<TaskSchedulerSystem> m_playScheduler;

	bool isRequestNext = false;


public:
	ResultScene();
	virtual ~ResultScene();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

	virtual bool RequestScene(uint32_t& id, float& waitTime)  override;
};