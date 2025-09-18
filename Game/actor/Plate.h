/**
 * Plate.h
 * 皿にのった物関連
 */
#pragma once
#include "Actor.h"


class Plate : public Actor
{
protected:
	/** 物理的な当たり判定(PhysicalBody) */
	CharacterController m_characterController;
	/** 物体ではない当たり判定(GhostBody) */
	CollisionObject m_collisionObject;


public:
	Plate() {}
	~Plate() {}

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;


public:
	void Initialize(const char* modelName, const Vector3& position, const Vector3 scale, const Quaternion& rotation);

	/**
	 * 当たり判定チェックのため取得
	 * NOTE：それ以外では使用しないこと
	 */
	CollisionObject* GetCollisionObject() { return &m_collisionObject; }
};




/**
 * 加工前の食材が乗った皿
 * ※投げることができる
 */
class FoodPlate : public Plate
{
protected:
	/** 投げる際に加えられる力 */
	Vector3 m_addForce;


public:
	FoodPlate();
	~FoodPlate();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;


public:
	/**
	 * 皿を投げる
	 */
	void Throw(const Vector3& direction);


public:
	FoodStatus* GetStatus() { return dynamic_cast<FoodStatus*>(m_status); }
};