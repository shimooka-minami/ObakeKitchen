/**
 * DeliverySpace.h
 * 出来た料理を納品する
 */
#pragma once


/**
 * DeliverySpace
 */
class DeliverySpace : public IGameObject
{
public:
	/** 例外でpublic */
	Transform m_transform;

protected:
	/** 判定の半径 */
	float m_radius = 0.0f;

	/** 当たり判定 */
	CollisionObject m_collisionObject;


public:
	DeliverySpace();
	~DeliverySpace();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& renderContect) override {} // 描画はない


private:
	void UpdateTransform();


public:
	/** 半径の設定 */
	inline void SetRadius(const float radius) { m_radius = radius; }

	/** 当たり判定の取得 */
	inline CollisionObject* GetCollision() { return &m_collisionObject; }
};