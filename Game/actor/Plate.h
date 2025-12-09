/**
 * Plate.h
 * 皿にのった物関連
 */
#pragma once
#include "Actor.h"
#include "collision/GhostBody.h"


class Plate : public Actor
{
protected:
	/** 物理的な当たり判定(PhysicalBody) */
	CharacterController m_characterController;
	/** 物体ではない当たり判定(GhostBody) */
	std::unique_ptr<SphereGhostBody> m_ghostBody = nullptr;


public:
	Plate();
	~Plate();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;


public:
	virtual void Initialize(const char* modelName, const Vector3& position, const Vector3 scale, const Quaternion& rotation);

	/** 座標の設定 お皿の位置 */
	void SetPosition(const Vector3& position);

public:
	/**
	 * 皿を置く
	 */
	void Put(const Vector3& direction);


public:
	FoodStatus* GetStatus() { return dynamic_cast<FoodStatus*>(m_status); }
};




/**********************************/


/**
 * 食材が乗った皿
 * ※投げることができる
 */
class FoodPlate : public Actor
{
	using SuperClass = Plate;


private:
	enum EnState
	{
		enState_Food,		// 料理前
		enState_Coocked,	// 料理後
	};


protected:
	/** 物理的な当たり判定(PhysicalBody) */
	CharacterController m_characterController;
	/** 物体ではない当たり判定(GhostBody) */
	std::unique_ptr<SphereGhostBody> m_ghostBody = nullptr;

	/** 投げる際に加えられる力 */
	Vector3 m_addForce;
	
	/** 料理前と後で分けるために必要な情報 */
	EnState m_state = enState_Food;
	ModelRender m_coockedRender;


public:
	FoodPlate();
	~FoodPlate();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;


public:
	/** 初期化 */
	void Initialize(const char* modelName, const char* coockedModelName, const Vector3& position, const Vector3 scale, const Quaternion& rotation);

	/** 座標の設定 お皿の位置 */
	void SetPosition(const Vector3& position);

	/** 料理後に変更 */
	void ChangedCoocke() { m_state = enState_Coocked; }
	/** 料理後か */
	bool IsCoocked() { return m_state == enState_Coocked; }


public:
	/**
	 * 皿を投げる
	 */
	void Throw(const Vector3& direction);


public:
	FoodStatus* GetStatus() { return dynamic_cast<FoodStatus*>(m_status); }
};