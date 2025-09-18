/**
 * ActorStatus.h
 * ステータス関連をまとめるファイル
 */
#pragma once


 /**
  * ステータス生成関数
  * ※必ずこの関数を呼んでステータスの生成をすること！
  * 　Factoryパターンで指定したステータスを生成してセットアップまでする
  */
template <typename TStatus>
static TStatus* CreateStatus()
{
	auto* status = new TStatus();
	status->Setup();
	return status;
}




/**********************/


/**
 * アクタークラス
 */
class ActorStatus
{
public:
	ActorStatus() {}
	~ActorStatus() {}

	/** ステータスのセットアップを必ず作ってください */
	virtual void Setup() = 0;
};




/**********************/


/**
 * キャラクターステータス
 */
class CharacterStatus : public ActorStatus
{
protected:
	/** キャラクターのスピード */
	float m_speed = 0.0f;
	/** キャラクターのダッシュスピード */
	float m_dashSpeed = 0.0f;
	/** キャラクターの半径 */
	float m_radius = 0.0f;
	/** キャラクターの高さ */
	float m_height = 0.0f;

public:
	CharacterStatus() {}
	~CharacterStatus() {}

	/** 初期設定 */
	virtual void Setup() override {}


public:
	/** スピードのゲッター */
	float GetSpeed() const { return m_speed; }
	/** ダッシュスピードのゲッター */
	float GetDashSpeed() const { return m_dashSpeed; }
	/** 半径のゲッター */
	float GetRadius() const { return m_radius; }
	/** 高さのゲッター */
	float GetHeight() const { return m_height; }
};




/**********************/


/**
 * プレイヤーステータス
 */
class PlayerStatus : public CharacterStatus
{
public:
	PlayerStatus();
	~PlayerStatus();

	/** 初期化 */
	virtual void Setup() override;
};




/***********************/






/**********************/


/**
 * 皿にのった物のステータス
 */
class PlateStatus : public ActorStatus
{
protected:
	/** フードの半径 */
	float m_radius = 0.0f;
	/** フードの高さ */
	float m_height = 0.0f;


public:
	PlateStatus() {}
	~PlateStatus() {}

	virtual void Setup() override {}


public:
	/** 半径のゲッター **/
	float GetRadius() const { return m_radius; }
	/** 高さのゲッター **/
	float GetHeight() const { return m_height; }
};




/**********************/


/**
 * 食材ステータス
 */
class FoodStatus : public PlateStatus
{
private:
	float m_addForcePower = 0.0f;	// 追加される力の強さ


public:
	FoodStatus();
	~FoodStatus();

	/** 初期化 */
	virtual void Setup() override;


public:
	/** 追加される力の強さのゲッター */
	float GetAddForcePower() const { return m_addForcePower; }
};