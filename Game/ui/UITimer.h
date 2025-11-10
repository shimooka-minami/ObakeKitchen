/**
 * UITimer.h
 * 制限時間の表示
 */
#pragma once


class UICanvas;
class UIDigit;


class UITimer : public IGameObject
{
private:
	UICanvas* m_uiCanvas = nullptr;
	UIDigit* m_uiDigit = nullptr;
	float m_timer = 0;


public:
	/** コンストラクタ 初期化 */
	UITimer();
	/** デストラクタ 破棄 */
	~UITimer();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);


public:
	/** 表示させたいスコアを設定 */
	void SetTimer(const float timer) { m_timer = timer; }
};



