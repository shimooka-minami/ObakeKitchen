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
	enTitleMenuType_Select,
	enTitleMenuType_Play,
	enTitleMenuType_Cotrol,
	enTitleMenuType_Setting,
	enTitleMenuType_Num,
};


class ITtitleMenu : Noncopyable
{
public:
	ITtitleMenu() {}
	virtual ~ITtitleMenu() {}

	virtual bool Start() = 0;
	virtual void Update() = 0;
	virtual void Render(RenderContext& rc) = 0;
	virtual bool CanChange(int& request) = 0;
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
	bool CanChange(int& request) override;
};


/** タイトル表示の後の説明・プレイ人数などの設定を表示する */
class TitleSelectMenu : public ITtitleMenu
{
private:
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
	bool m_isChange = false;
	bool m_isPlayAnimation = false;

	Vector3 m_senPosition;
	Vector3 m_penPosition;

public:
	TitleSelectMenu();
	virtual ~TitleSelectMenu();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	bool CanChange(int& request) override;
};




/** プレイヤー選択 */
class TitlePlayerSelectMenu : public ITtitleMenu
{
private:
	std::unique_ptr<UICanvas> m_uiCanvas;
	UIIcon* m_playerObake[MAX_PLAYER_NUM];
	UIIcon* m_playerNumber[MAX_PLAYER_NUM];

	bool m_isPlayerConected[MAX_PLAYER_NUM];
	bool m_isBack = false;

public:
	TitlePlayerSelectMenu();
	~TitlePlayerSelectMenu();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc)override;
	bool CanChange(int& request) override;
};


/** 操作画面 */
class TitleControlGuide : public ITtitleMenu
{
private:
	std::unique_ptr<UICanvas> m_uiCanvas;
	UIIcon* m_backObake;

	bool m_isBack = false;


public:
	TitleControlGuide();
	~TitleControlGuide();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc)override;
	bool CanChange(int& request) override;
};


/** 設定画面 */
class TitleSetting : public ITtitleMenu
{
	enum EnNPCType
	{
		enNPCType_kind,
		enNPCType_mean,
		enNPCType_Random,
		enNPCType_Max,
	};

private:
	std::unique_ptr<UICanvas> m_uiCanvas;
	UIIcon* m_npcTypeObake[NPC_TYPE_NUM];
	UIIcon* m_npcTypeIcon[NPC_TYPE_NUM];
	UIIcon* m_backObake;

	int m_npcTypeIndex = enNPCType_kind;

	bool m_isNPCConected[NPC_TYPE_NUM] = {true,false,false};
	bool m_isBack = false;
	bool m_isChange = false;


public:
	TitleSetting();
	~TitleSetting();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc)override;
	bool CanChange(int& request) override;
};


/** タイトルシーン */
class TitleScene : public IScene
{
	appScene(TitleScene);


private:
	//SpriteRender m_spriteRender[enTitleSpriteKind_Max];
	//std::unique_ptr<SpriteAnimationBase> m_buttonAnimation;

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




private:
	static bool sIsStartGame;


public:
	static void SetStartGame(bool isStart)
	{
		sIsStartGame = isStart;
	}
};