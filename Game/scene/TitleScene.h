/**
 * TitleScene.h
 * タイトル画面のシーン
 */
#pragma once
#include "IScene.h"

class Player;
class UICanvas;
class UIIcon;


enum EnTitleSpriteKind
{
	//enTitleSpriteKind_Background,
	//enTitleSpriteKind_Logo,
	//enTitleSpriteKind_ButtonA,
	enTitleSpriteKind_Max,
};


enum EnTitleMenuType
{
	enTitleMenuType_Start,
	EnTitleMenuType_Select,
	EnTitleMenuType_Num,
};



class ITtitleMenu : Noncopyable
{
public:
	ITtitleMenu() {}
	virtual ~ITtitleMenu() {}

	virtual bool Start() = 0;
	virtual void Update() = 0;
	virtual void Render(RenderContext& rc) = 0;
	virtual bool CanChange() = 0;
};


class TitleStartMenu : public ITtitleMenu
{
private:
	std::unique_ptr<UICanvas> m_uiCanvas = nullptr;
	UIIcon* m_titleIcon = nullptr;

	bool m_isChange = false;


public:
	TitleStartMenu();
	virtual ~TitleStartMenu();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	bool CanChange() override;
};


/** タイトル表示の後の説明・プレイ人数などの設定を表示する */
class TitleSelectMenu : public ITtitleMenu
{
	enum enSelectMenuType
	{
		enSelectMenuType_GameStart,
		enSelectMenuType_Operation,
		enSelectMenuType_Setting,
		enSelectMenuType_End,
		enSelectMenuType_Num,
	};

private:
	std::unique_ptr<UICanvas> m_uiCanvas;
	UIIcon* m_selectMenu;
	UIIcon* m_hanePen;
	UIIcon* m_sen;

	int m_currentSelectIndex = enSelectMenuType_GameStart;
	
	Vector3 m_senPosition;
	Vector3 m_penPosition;

public:
	TitleSelectMenu();
	virtual ~TitleSelectMenu();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	bool CanChange() override;
};




/** タイトルシーン */
class TitleScene : public IScene
{
	appScene(TitleScene);


private:
	//SpriteRender m_spriteRender[enTitleSpriteKind_Max];
	std::unique_ptr<SpriteAnimationBase> m_buttonAnimation;

	Player* m_player;
	std::unique_ptr<ModelRender> m_titleBack;
	std::unique_ptr<SpriteRender> m_titleRender;

	int m_currentMenu = enTitleMenuType_Start;
	std::unique_ptr<ITtitleMenu> m_titleMenu = nullptr;

	bool m_isRequestNext = false;


public:
	TitleScene();
	virtual ~TitleScene();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

	virtual bool RequestScene(uint32_t& id, float& waitTime)  override;


private:
	void ChangeTitleMenu();
};