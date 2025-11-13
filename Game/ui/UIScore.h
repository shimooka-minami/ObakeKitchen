/**
 * UIScore.h
 * スコアを計算する
 */
#pragma once


class UICanvas;
class UIDigit;


class UIScore : public IGameObject
{
private:
	UICanvas* m_uiCanvas = nullptr;
	UIDigit* m_uiDigit = nullptr;
	int m_score = 0;

	UICanvas* m_uiAddScoreCanvas = nullptr;
	UIDigit* m_uiAddScoreDigit = nullptr;
	int m_requestAddScore = 0;
	int m_addScore = 0;


public:
	/** コンストラクタ 初期化 */
	UIScore();
	/** デストラクタ 破棄 */
	~UIScore();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);


public:
	/** 表示させたいスコアを設定 */
	void SetScore(const int score)
	{
		m_requestAddScore = score - m_score;		// 200 = 1000 - 800
		m_score = score;					// 1000
	}
};



