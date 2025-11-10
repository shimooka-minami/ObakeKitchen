/**
 * TimeKeeper.h
 * ŠÔŠÇ—
 */
#pragma once
#include "ui/SpriteAnimation.h"


class TimeKeeper
{
private:
	/** c‚èŠÔ */
	float m_currentTime = 0.0f;
	/** §ŒÀŠÔ */
	float m_limitTime = 0.0f;


public:
	TimeKeeper();
	~TimeKeeper();


public:
	void Update();


public:
	/** §ŒÀŠÔ‚Ìİ’è */
	void SetLimitTime(const float limitTime)
	{
		m_limitTime = limitTime;
	}
	/** ¡‚ÌŠÔ‚Ìæ“¾ */
	float GetTime() const { return m_currentTime; }
	/** c‚èŠÔ‚Ìæ“¾ */
	float GetRemainingTime() const
	{
		return m_limitTime - m_currentTime;
	}

	/** ¡‚ÌŠÔ‚ª§ŒÀŠÔ‚ğ’´‚¦‚½‚© */
	bool IsTimeOver() const
	{
		if (m_currentTime >= m_limitTime)
		{
			return true;
		}
		return false;
	}
};