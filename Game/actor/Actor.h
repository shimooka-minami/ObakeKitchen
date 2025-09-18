/**
 * Actor.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#pragma once
#include "ActorStatus.h"


/**
 * アクタークラス
 * NOTE:見た目が存在するゲームオブジェクトに設定する
 */
class Actor : public IGameObject
{
protected:
	/** 座標 */
	Vector3 m_position;
	/** 拡縮 */
	Vector3 m_scale;
	/** 回転 */
	Quaternion m_rotation;
	/** モデル描画 */
	ModelRender m_modelRender;
	/** ステータス */
	ActorStatus* m_status;


public:
	Actor();
	~Actor();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& renderContect) override;


public:
	/** モデル描画機能を取得 */
	ModelRender* GetModelRender() { return &m_modelRender; }


public:
	/**
	 * 座標取得
	 */
	inline const Vector3& GetPosition() const { return m_position; }
	/**
	 * 座標設定
	 */
	inline void SetPosition(const Vector3& position) { m_position = position; }

	/**
	 * 拡縮取得
	 */
	inline const Vector3& GetScale() const { return m_scale; }
	/**
	 * 拡縮設定
	 */
	inline void SetScale(const Vector3& scale) { m_scale = scale; }

	/**
	 * 回転取得
	 */
	inline const Quaternion& GetRotation() const { return m_rotation; }
	/**
	 * 回転設定
	 */
	inline void SetRotation(const Quaternion& rotation) { m_rotation = rotation; }
};