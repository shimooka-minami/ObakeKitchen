#pragma once

class SaveData
{
private:
	bool m_isControlerConected[MAX_PLAYER_NUM];

private:
	SaveData();
	~SaveData();

	/*void Serialize();
	void Deserialize();*/

public:
	// プレイヤー何人いるか
	inline bool IsControlerConected(int number) const
	{
		return m_isControlerConected[number];
	}
	// せったー
	inline void SetContolerConected(const int number, const bool isControler)
	{
		m_isControlerConected[number] = isControler;
	}



	/**
	 * シングルトン用
	 */

private:
	static SaveData* m_instance; //シングルトンパス

public:
	/**
	 * インスタンスを作る
	 */
	static void CreateInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new SaveData();
		}
	}

	/**
	 * インスタンスを取得
	 */
	static SaveData* GetInstance()
	{
		return m_instance;
	}

	/**
	 * インスタンスを破棄
	 */
	static void DestroyInstance()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};


