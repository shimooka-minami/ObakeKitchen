#pragma once

class Player;
class PlayerStatus;

class IState;

class FoodPlate;


enum enPlayerState
{
	enPlayerIdle,
	enPlayerWalk,
	enPlayerDash,
	enPlayerHavePlate,
	enPlayerThrow,
	enPlayerCoocking,
	enPlayerNum,
};


class StateMachine
{
private:
	/** 今のステータス*/
	IState* m_currentState = nullptr;
	IState* m_nextState = nullptr;
	/** ステートのリスト*/
	IState* m_stateList[enPlayerNum];

	/** プレイヤーの方向を取る変数(スティック入力の方向) */
	Vector3 m_direction = Vector3::Zero;

	/** 移動ベクトル */
	Vector3 m_moveVector = Vector3::Zero;

	/** 座標 */
	Vector3 m_position = Vector3::Zero;
	/** 拡縮 */
	Vector3 m_scale = Vector3::One * 1.0f;
	/** 回転 */
	Quaternion m_rotation = Quaternion::Identity;

	/** 皿の位置 */
	Vector3 m_platePos = Vector3::Zero;

	/** 主人を持つ ※基本触らない! */
	Player* m_owner = nullptr;
	/** 主人のステータスを持つ */
	PlayerStatus* m_ownerStatus = nullptr;

	/** フードプレートクラスのポインタ */
	FoodPlate* m_targetFood = nullptr;

	/** 左スティックの入力量 */
	float m_stickLAmount = 0.0f;

	/** ダッシュできるかどうか */
	bool m_isDash = false;
	/** 皿を持つと投げるの両立 */
	bool m_actionButtonA = false;

	/** 皿が近くにあるか */
	bool m_isNearFood = false;
	/** 皿が目の前にあるか */
	bool m_isForwardFood = false;

	/** 料理スペースに入った */
	bool m_isInCookingSpace = false;
	/** 食材スペースに入った */
	bool m_isInFoodSpace = false;


public:
	StateMachine();
	~StateMachine();
	
	/** 更新 */
	void Update();
	/** ステート変更 */
	void ChangeState();


private:
	/** ステートの追加をラップした関数 */
	template<typename T>
	void AddState(enPlayerState state)
	{
		m_stateList[state] = new T(this);
	}

	/** 指定した状態か */
	inline bool IsEqualCurrentState(enPlayerState state) const
	{
		return m_currentState == m_stateList[state];
	}


public:
	/** 指定した状態になるか */
	inline bool IsEqualNextState(enPlayerState state) const
	{
		return m_nextState == m_stateList[state];
	}


private:
	/** 変更するステートを取得 */
	IState* GetChangeState() const;

	/** 歩く状態に変更できるか */
	bool CanChangeWalk() const;
	/** 走る状態に変更できるか */ 
	bool CanChangeDash() const; 
	/** 皿を持った状態に変更できるか */
	bool ChangeHavePlate() const;
	/** 皿を持ったままに変更する */
	bool CanChangeThrow() const;
	/** 料理する状態に変更できるか */
	bool CanChangeCooking() const;


public:
	/** 初期設定用の関数 */
	void Setup(Player* owner);

public:
	/** 主人取得 */
	Player* GetOwner() { return m_owner; }

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
	 * 移動ベクトル取得
	 */
	inline const Vector3& GetMoveVector() const { return m_moveVector; }
	/**
	 * 移動ベクトル設定
	 */
	inline void SetMoveVector(const Vector3& moveVector) { m_moveVector = moveVector; }

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

	/**
	 * 皿の位置を取得
	 */
	inline const Vector3& GetPlatePosition() const { return m_platePos; }

	/**
	 * 皿の位置を設定 いるか分からんけど一応
	 */
	inline void SetPlatePosition(const Vector3& platePos) { m_platePos = platePos; }


	/**
	 * アクションAボタン 持つと投げるを両立
	 */
	inline void ActionButtonA(const bool actionButtonA) { m_actionButtonA = actionButtonA; }

	/**
	 * 入力量を設定
	 */
	inline void SetStickLAmount(const float stickLAmount) { m_stickLAmount = stickLAmount; }
	
	/**
	 * 入力量の取得
	 */ 
	inline float GetStickLAmount() const { return m_stickLAmount; }


	/**
	 * 近くのフードの設定 設定だけ取得は作るな
	 */
	inline void SetNearFood(const bool isNearFood) { m_isNearFood = isNearFood; }

	/**
	 * 近くのフードの真偽設定 
	 */
	inline bool IsNearFood() const { return m_isNearFood; }


	/**
	 * 角度の設定
	 */
	inline bool IsForwardFood() const { return m_isForwardFood; }

	/**
	 * 角度の取得
	 */
	inline void SetForwardFood(const bool isForwardFood) { m_isForwardFood = isForwardFood; }

	/**
	 * 料理スペースに入ったか
	 */
	inline void SetInCookingSpace(const bool inSpace) { m_isInCookingSpace = inSpace; }

	/**
	 * 食材スペースに入ったか
	 */
	inline void SetInFoodSpace(const bool inFoodSpace) { m_isInFoodSpace = inFoodSpace; }


public:
	/**
	 * フードプレートクラスの設定
	 */
	inline void SetTargetFood(FoodPlate* targetFood) { m_targetFood = targetFood; }

	/**
	 * フードプレートクラスの取得
	 */ 
	inline FoodPlate* GetTargetFood() { return m_targetFood; }
};

