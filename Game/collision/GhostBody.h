/**
 * GhostBody.h
 * 物理的な物体ではない当たり判定の処理群
 */
#pragma once
#include "Collider.h"


/** 物体ではない判定処理の基底クラス */
class IGhostBody : public Noncopyable
{
protected:
	/** コリジョンを持つオーナーとなるゲームオブジェクト */
	IGameObject* m_owner = nullptr;
	/** 当たり判定を行う処理を持つ(継承先な好きな当たり判定処理にする) */
	app::RefCollider m_collider = nullptr;
	/** 座標 */
	Vector3 m_position = Vector3::Zero;
	/** コリジョン当たり判定先を分けるための種別 */
	int m_collisionType = 0;


public:
	IGhostBody() {}
	virtual ~IGhostBody() {}

	/** 座標などの更新を行う */
	virtual void Update() = 0;


public:
	/**
	 * コライダーの取得を行う
	 * 当たり判定処理などで使用される
	 */
	app::RefCollider GetCollider() { return m_collider; }

	/** 座標取得 */
	const Vector3& GetPosition() const { return m_position; }
	/** 座標設定 */
	void SetPosition(const Vector3& position) { m_position = position; }
};




/** 球の物理的ではない当たり判定処理機能を持つクラス */
class SphereGhostBody : public IGhostBody
{
private:
	float m_radisu = 1.0f;


public:
	SphereGhostBody();
	~SphereGhostBody();

	/** 更新 */
	void Update() override;

	/** 形状の生成 */
	void Create(IGameObject* owner,const Vector3& position, const float radius, const int collisionType);

public:
	/** 球取得 */
	app::RefSphereCollider GetCollider() { return std::dynamic_pointer_cast<app::SphereCollider>(m_collider); }

	/** 半径取得 */
	float GetRadius() const { return m_radisu; }
	/** 半径設定 */
	void SetRadius(const float radius) { m_radisu = radius; }
};