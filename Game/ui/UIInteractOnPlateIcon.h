/**
 * UIInteractOnPlateIcon.h
 * 皿の上に食材を置くときに出るアイコン
 */
#pragma once


class UICanvas;
class UIIcon;
class UIImage;


class UIInteractOnPlateIcon : public IGameObject
{
private:
	std::unique_ptr<UICanvas> m_uiCanvas = nullptr;

	UIIcon* m_aButton = nullptr;

	Vector3 m_position;

	bool m_isDrawAButton = false;

	// @todo for test
	// プレイヤーが近くにいるのか
	bool m_isNearPlayer = false;


public:
	UIInteractOnPlateIcon();
	~UIInteractOnPlateIcon();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

public:
	/** 表示する画像 */
	void Initialize();

	/** Aボタンを表示するかの設置 */
	void SetDrawAButton(const bool draw) { m_isDrawAButton = draw; }


	void SetPosition(const Vector3& position) { m_position = position; }
};