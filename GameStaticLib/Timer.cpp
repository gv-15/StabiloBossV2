#include "pch.h"
#include "Timer.h"


Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::Start()
{
	m_t0 = std::chrono::high_resolution_clock::now();
}

double Timer::ElapsedSeconds(bool restart)
{
	m_t1 = std::chrono::high_resolution_clock::now();

	auto elapsedTime = m_t1 - m_t0;

	if (restart)
		m_t0 = m_t1;

	return (std::chrono::duration<double, std::ratio<1>>(elapsedTime)).count();;
}