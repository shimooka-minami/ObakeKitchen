#pragma once

class Player;
class PlayerStatus;

class IState;
class IdleState;

enum enPlayerState
{
	enPlayerIdle,
	enPlayerWalk,
	enPlayerDash,
	enPlayerNum,
};


class StateMachine
{
private:
	/** 今のステータス*/
	IState* m_currentState;
	/** ステートのリスト*/
	IState* m_stateList[enPlayerNum];

	/** プレイヤーの方向を取る変数(スティック入力の方向) */
	Vector3 m_direction = Vector3::Zero;

	/** 座標 */
	Vector3 m_position = Vector3::Zero;
	/** 拡縮 */
	Vector3 m_scale = Vector3::One * 1.0f;
	/** 回転 */
	Quaternion m_rotation = Quaternion::Identity;

	/** 主人を持つ ※基本触らない! */
	Player* m_owner = nullptr;
	/** 主人のステータスを持つ */
	PlayerStatus* m_ownerStatus = nullptr;

	/** ダッシュできるかどうか */
	bool m_isDash = false;


public:
	StateMachine();
	~StateMachine();
	
	/** 更新 */
	void Update();
	/** ステート変更 */
	void ChangeState();


private:
	/** 変更するステートを取得 */
	IState* GetChangeState() const;

	/** 歩く状態に変更できるか */
	bool CanChangeWalk() const;
	/** 走る状態に変更できるか */ 
	bool CanChangeDash() const; 


public:
	/** 初期設定用の関数 */
	void Setup(Player* owner);

public:
	/** 主人のステータス取得 */
	PlayerStatus* GetOwnerStatus() { return m_ownerStatus; }

	/** 主人のアニメーションを生成 */
	void PlayAnimation(const int animationIndex);


public:
	/** 方向のゲッター */
	const Vector3& GetDirection() { return m_direction; }
	/** 方向のセッター */
	void SetDirection(const Vector3& direction) { m_direction = direction; }

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

	/**
	 * ダッシュの設定
	 */
	inline void SetDash(const bool isDash) { m_isDash = isDash; }
};

