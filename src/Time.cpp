#include "Time.hpp"
#include <algorithm>

Time::Time(float targetFps)
	: m_accumulator(0.0f)
	, m_deltaTime(0.0f)
{

	m_fixedDeltaTime = 1.0f / targetFps;

	m_prevTime = std::chrono::high_resolution_clock::now();

}

void Time::Tick()
{

	auto currentTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> elapsedTime = currentTime - m_prevTime;
	m_prevTime = currentTime;

	m_deltaTime = elapsedTime.count();

	m_deltaTime = std::min(m_deltaTime, 0.25f);

	m_accumulator += m_deltaTime;

}

bool Time::ConsumeFixedSteps()
{

	if (m_accumulator >= m_fixedDeltaTime)
	{

		m_accumulator -= m_fixedDeltaTime;
		return true;

	}

	return false;

}