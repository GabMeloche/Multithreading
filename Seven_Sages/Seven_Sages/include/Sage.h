#pragma once
#include <Baguette.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <ColorPrint.h>

enum class State { THINKING, EATING, WAITING };

class Sage
{
private:
	bool m_dayFinished = false;
	State m_state;
	int m_id;
	unsigned int m_cyclesCompleted = 0;
	unsigned int m_mealsPerDay;

	Baguette* m_left;
	Baguette* m_right;

public:
	Sage(unsigned int p_mealsPerDay = 3);
	~Sage() = default;

	void PrintStatus() const;

	void main();
	void SetState(State p_state) { m_state = p_state; }
	void SetLeft(Baguette* p_left) { m_left = p_left; }
	void SetRight(Baguette* p_right) { m_right = p_right; }
	void SetCyclesCompleted(int p_cycles) { m_cyclesCompleted = p_cycles; }
	void SetMealsPerDay(unsigned int p_meals) { m_mealsPerDay = p_meals; }

	[[nodiscard]] std::string GetState() const;
	[[nodiscard]] bool IsDayFinished() const { return m_dayFinished; }


};
