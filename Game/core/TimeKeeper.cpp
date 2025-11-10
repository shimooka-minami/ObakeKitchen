#include "stdafx.h"
#include "TimeKeeper.h"


TimeKeeper::TimeKeeper()
{
}


TimeKeeper::~TimeKeeper()
{
}


void TimeKeeper::Update()
{
	m_currentTime += g_gameTime->GetFrameDeltaTime();
}


