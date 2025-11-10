/**
 * Score.cpp
 * スコアを計算する
 */
#include "stdafx.h"
#include "Score.h"

// インスタンスの初期化
Score* Score::m_instance = nullptr;

Score::Score()
{
}


Score::~Score()
{
}

void Score::AddScore(int score)
{
	m_currentScore += score;
}




