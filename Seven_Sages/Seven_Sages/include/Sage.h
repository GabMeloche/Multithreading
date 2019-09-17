#pragma once

enum class State { THINKING, EATING, WAITING };

class Sage
{

private:
	State m_state;
	int m_cyclesCompleted = 0;

public:
	Sage() : m_state{ State::THINKING } {};
	~Sage() = default;

	void ChangeState(State p_state);
	void main();
};
