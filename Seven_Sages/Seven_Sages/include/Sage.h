#pragma once
#include <Baguette.h>
#include <string>

enum class State { THINKING, EATING, WAITING };

class Sage
{

private:
	State m_state;
	int m_cyclesCompleted = 0;
	int m_id;
	bool m_dayFinished = false;

	Baguette* m_left;
	Baguette* m_right;

public:
	Sage();
	~Sage() = default;

	void main();
	void SetState(State p_state) { m_state = p_state; }
	void SetLeft(Baguette* p_left) { m_left = p_left; }
	void SetRight(Baguette* p_right) { m_right = p_right; }
	void SetCyclesCompleted(int p_cycles) { m_cyclesCompleted = p_cycles; }

	std::string GetState();
	bool IsDayFinished() { return m_dayFinished; }


};
