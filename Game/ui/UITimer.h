/**
 * UITimer.h
 * 制限時間の表示
 */
#pragma once


class UICanvas;
class UIDigit;
class UIIcon;

class TimeKeeper;

class UITimer : public IGameObject
{
private:
	UICanvas* m_uiCanvas = nullptr;
	UIDigit* m_uiDigit = nullptr;
	UIIcon* m_uiHourGlass = nullptr;
	float m_timer = 0;
	bool m_isTimeLimit = false;

	TimeKeeper* m_timeKeeper = nullptr;

public:
	/** コンストラクタ 初期化 */
	UITimer();
	/** デストラクタ 破棄 */
	~UITimer();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);


public:
	/** 表示させたい時間を設定 */
	void SetTimer(const float timer) { m_timer = timer; }
};



