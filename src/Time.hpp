#pragma once
#include <chrono>

class Time
{

public:

	Time(float targetFps = 60.0f);

	void Tick();

	bool ConsumeFixedSteps();

	float GetDeltaTime() const {
		return m_deltaTime;
	}

	float GetFixedDeltaTime() const {
		return m_fixedDeltaTime;
	}

private:

	float m_deltaTime;

	float m_fixedDeltaTime;

	float m_accumulator;

	std::chrono::high_resolution_clock::time_point m_prevTime;

};