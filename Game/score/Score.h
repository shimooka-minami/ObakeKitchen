/**
 * Score.h
 * スコアを計算する
 */
#pragma once


class Score
{
private:
	/** 今のスコア */
	int m_currentScore = 0;


private:
	/** コンストラクタ 初期化 */
	Score();
	/** デストラクタ 破棄 */
	~Score();


public:
	void AddScore(int score);


public:
	int GetScore() const { return m_currentScore; }


	/**
	 * シングルトン
	 */
private:
	/** シングルトンインスタンス */
	/** インスタンス=実体 これはクラス内で1個しかもたない */
	static Score* m_instance;


public:
	/** 
	 * シングルトンインスタンスを生成する 
	 */
	static void CreateInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Score();
		}
	}

	/**
	 * シングルトンインスタンスを取得する
	 */
	static Score* GetInstance()
	{
		return m_instance;
	}
	
	/**
	 * 利用可能か
	 */
	static bool IsAvailable()
	{
		return m_instance != nullptr;
	}

	/**
	 * シングルトンインスタンスを放棄する
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



