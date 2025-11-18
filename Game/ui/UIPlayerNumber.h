/**
 * UIPlayerNumber.h
 * プレイヤーのアイコン
 */
#pragma once


class UICanvas;
class UIIcon;


class UIPlayerNumber : public IGameObject
{
private:
	UICanvas* m_uiCanvas = nullptr;
	
	Vector3 m_position;
	int m_playerNumber = 1;


public:
	/** コンストラクタ 初期化 */
	UIPlayerNumber();
	/** デストラクタ 破棄 */
	~UIPlayerNumber();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);


public:
	// @todo for あとでコメント
	void Initialize(const int number);

	void SetPosition(const Vector3& position) { m_position = position; }
};



