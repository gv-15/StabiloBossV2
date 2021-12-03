#pragma once

#include <chrono>

#include "Sprite.h"
class Timer : public Sprite
{
	std::chrono::high_resolution_clock::time_point m_t0, m_t1;

public:
	Timer(string Filename, double x, double y, double x1, double y2);
	~Timer();

	void Start();
	double ElapsedSeconds(bool restart = false);
};
