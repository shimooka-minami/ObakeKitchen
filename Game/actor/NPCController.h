#pragma once

class Player;

class NPCController : public IGameObject
{
private:
	/**
	 * 関数ポインタの型定義（記述を楽にするため）
	 */
	using EnterFunc = void (*)(NPCController*);
	using UpdateFunc = void (*)(NPCController*);
	using ExitFunc = void (*)(NPCController*);
	using CheckFunc = int (*)(NPCController*);


private:
	/** AI思考処理 */
	struct AIState
	{
		/**
		 * 初期化
		 * この思考に入った瞬間に1回呼ばれる
		 */
		EnterFunc enter;
		/**
		 * 更新
		 * この思考中、毎フレーム呼ばれる（入力生成など）
		 */
		UpdateFunc update;
		/**
		 * 後片付け
		 * この思考から抜ける瞬間に1回呼ばれる
		 */
		ExitFunc exit;
		/**
		 * 遷移判定
		 * 次の思考IDを返す（遷移しない場合は -1 を返す）
		 */
		CheckFunc check;
	};


private:
	/** 思考パターンのID */
	enum EnAIStateID
	{
		enAIState_Idle,   // 待機
		enAIState_FreeMove,  // 適当に移動
		enAIState_Max,   // 最大数
		enAIState_Invalid = -1, // 無効値
	};


private:
	Player* m_target = nullptr;
	float m_elapsedTime = 0.0f;

	Vector3 m_targetPosition = Vector3::Zero;


	/** 現在の思考状態 */
	EnAIStateID m_currentState = enAIState_Idle;
	/** 初期化処理をしたか */
	bool m_isInitialized = false;


public:
	NPCController();
	~NPCController();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;


public:
	/** 操作対象の設定 */
	void SetTarget(Player* target)
	{
		m_target = target;
	}


private:
	void ChangeState(EnAIStateID nextState);




	// -----------------------------------------------------
	//  各ステートの実装 (static関数)
	// -----------------------------------------------------
private:
	static std::map<EnAIStateID, AIState> m_stateMap;


public:
	/** 初期化 */
	static void Initialize();


private:
	/** 登録関数 */
	static void RegisterState(const EnAIStateID id, EnterFunc enter, UpdateFunc update, ExitFunc exit, CheckFunc check)
	{
		AIState state;
		// 引数が nullptr ならダミー関数を入れる（これで呼び出し側でのnullptrチェックが不要になる）
		state.enter = (enter != nullptr) ? enter : DoNothing;
		state.update = (update != nullptr) ? update : DoNothing;
		state.exit = (exit != nullptr) ? exit : DoNothing;
		state.check = (check != nullptr) ? check : CheckNothing;
		// mapに登録
		m_stateMap.emplace(id, state);
	}
	/** AIStateを探す */
	AIState* FindAIState(const EnAIStateID id)
	{
		auto it = m_stateMap.find(id);
		if (it != m_stateMap.end()) {
			return &it->second;
		}
		return nullptr;
	}



	/**
	 * 何もしないダミー関数を用意しておく
	 */
	static void DoNothing(NPCController*) {}
	/** 遷移なし */
	static int CheckNothing(NPCController*) { return -1; }

	/**
	 * 待機関連
	 */
	static void EnterIdle(NPCController* npc);
	static void UpdateIdle(NPCController* npc);
	static void ExitIdle(NPCController* npc);
	static int CheckIdle(NPCController* npc);

	/**
	 * 適当に移動関連
	 */
	static void EnterFreeMove(NPCController* npc);
	static void UpdateFreeMove(NPCController* npc);
	static void ExitFreeMove(NPCController* npc);
	static int CheckFreeMove(NPCController* npc);

};