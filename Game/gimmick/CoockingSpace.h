/**
 * CoockingSpace.h
 * 料理する場所の判定を提供する
 */
#pragma once
#include "collision/GhostBody.h"


/**
 * CoockingSpace
 */
class CoockingSpace : public IGameObject
{
private:
	bool m_isNearPlayer = false;

public:
	/** 例外でpublic */
	Transform m_transform;

protected:
	/** 判定の半径 */
	float m_radius = 0.0f;

	/** 当たり判定 */
	std::unique_ptr<SphereGhostBody> m_ghostBody;


public:
	CoockingSpace();
	~CoockingSpace();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& renderContect) override {}	// 描画はない


private:
	void UpdateTransform();


public:
	/** 半径の設定 */
	inline void SetRadius(const float radius) { m_radius = radius; }

	/** プレイヤーが近くにいるかの設定 */
	inline void SetNearPlayer(const bool isNearPlayer) { m_isNearPlayer = isNearPlayer; }

	/** プレイヤーが近くにいるかの取得 */
	inline bool IsNearPlayer() const { return m_isNearPlayer; }
};