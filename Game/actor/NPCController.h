#pragma once

class Player;

class NPCController : public IGameObject
{
private:
	Player* m_target = nullptr;
	float m_elapsedTime = 0.0f;

public:
	NPCController();
	~NPCController();

	bool Start() override;
	void Update() override;
	void Render(RenderContext&rc) override;

	/** 操作対象の設定 */
	void SetTarget(Player* target) 
	{ 
		m_target = target;
	}

//private:
//	/** 左スティックの入力があるか */
//	inline bool IsInputStickL()
//	{
//		 左スティックの入力があるかどうかを判定
//		if ((fabsf(GetPad()->GetLStickXF()) >= FLT_EPSILON) || (fabsf(GetPad()->GetLStickYF()) >= FLT_EPSILON))
//		{
//			return true;
//		}
//		return false;
//	}
//	/** 左スティックの入力量を取得 */
//	Vector3 GetStickL();
//	/** 左スティックによる方向を使って回転を計算 */
//	Quaternion ComputeRotation();
//	/** 対象のコントローラーを取得 */
//	GamePad* GetPad()
//	{
//		return g_pad[m_controllerIndex];
//	}
};