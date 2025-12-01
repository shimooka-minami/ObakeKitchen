/**
 * TitleScene.h
 * タイトル画面のシーン
 */
#pragma once
#include "IScene.h"
#include "ui/SpriteAnimation.h"

class Player;

enum EnTitleSpriteKind
{
	//enTitleSpriteKind_Background,
	enTitleSpriteKind_Logo,
	enTitleSpriteKind_ButtonA,
	enTitleSpriteKind_Max,
};



/** タイトルシーン */
class TitleScene : public IScene
{
	appScene(TitleScene);


private:
	SpriteRender m_spriteRender[enTitleSpriteKind_Max];
	std::unique_ptr<SpriteAnimationBase> m_buttonAnimation;

	Player* m_player;
	std::unique_ptr<ModelRender> m_titleBack;

	bool m_isRequestNext = false;


public:
	TitleScene();
	virtual ~TitleScene();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

	virtual bool RequestScene(uint32_t& id, float& waitTime)  override;
};