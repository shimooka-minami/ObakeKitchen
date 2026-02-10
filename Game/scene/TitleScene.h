/**
 * TitleScene.h
 * タイトル画面のシーン
 */
#pragma once
#include "IScene.h"

class Player;
class UICanvas;
class UIImage;
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
	enTitleMenuType_StartTab,
	enTitleMenuType_Cotrol,
	enTitleMenuType_Setting,
	enTitleMenuType_Num,
};


class ITitleMenu : Noncopyable
{
public:
	ITitleMenu() {}
	virtual ~ITitleMenu() {}

	virtual bool Start() = 0;
	virtual void Update() = 0;
	virtual void Render(RenderContext& rc) = 0;
	virtual bool CanChange(int& request) = 0;
};


class TitleStartMenu : public ITitleMenu
{
private:
	std::unique_ptr<UICanvas> m_uiCanvas = nullptr;
	UIIcon* m_titleIcon = nullptr;

	bool m_isChange = false;
	bool m_isPressed = false;


public:
	TitleStartMenu();
	virtual ~TitleStartMenu();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	bool CanChange(int& request) override;
};


/** タイトル表示の後の説明・プレイ人数などの設定を表示する */
class TitleSelectMenu : public ITitleMenu
{
private:
	enum EnSelectMenuType
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
class TitlePlayerSelectMenu : public ITitleMenu
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
class TitleControlGuide : public ITitleMenu
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
class TitleSetting : public ITitleMenu
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


/** タブ画面 */
class SelectTab : public ITitleMenu
{
private:
	enum EnSelectTab
	{
		enSelectTab_No,
		enSelectTab_Yes,
		enSelectTabt_Num
	};

private:
	std::unique_ptr<UICanvas> m_uiCanvas;

	int m_currentTabSelectindex = enSelectTab_No;

	bool m_isChange = false;
	bool m_isPlayAnimation = false;

	//std::vector<UIIcon*> m_button;
	std::shared_ptr<UICanvas> m_canvas;

	Vector3 m_wakuTabPosition;
	Vector3 m_wakuTabScale;
	UIIcon* m_wakuTab;
	//UIIcon* m_wakuTab;
	
	// @todo for test
	UIIcon* m_yesButton;
	UIIcon* m_noButton;

	std::unique_ptr<UIVector3Animation> m_wakuTabuScaleAnimation = nullptr;

public:
	SelectTab();
	~SelectTab();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	bool CanChange(int& reqest) override;


private:
	void UpdateSelectTabIndex();
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
	std::unique_ptr<ITitleMenu> m_titleMenu = nullptr;

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