/**
 * UIInteractIcon.h
 * 調理場と納品場のアイコン
 */
#pragma once


class UICanvas;
class UIIcon;


class UIInteractIcon : public IGameObject
{
private:
	std::unique_ptr<UICanvas> m_uiCanvas = nullptr;
	
	UIIcon* m_aButton = nullptr;

	Vector3 m_position;

	bool m_isDrawAButton = false;


public:
	/** コンストラクタ 初期化 */
	UIInteractIcon();
	/** デストラクタ 破棄 */
	~UIInteractIcon();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);


public:
	// @todo for あとでコメント
	void Initialize(const EnInteractType type, const Vector3& position);


	void SetDrawAButton(const bool draw) { m_isDrawAButton = draw; }
};



