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

	Baguette* m_left;
	Baguette* m_right;

public:
	Sage();
	~Sage() = default;

	void ChangeState(State p_state);
	void main();
	void SetLeft(Baguette* p_left) { m_left = p_left; }
	void SetRight(Baguette* p_right) { m_right = p_right; }

	std::string GetState();

};
