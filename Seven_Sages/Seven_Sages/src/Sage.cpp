#include <Sage.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

Sage::Sage()
{
	m_state = State::THINKING;
	 static int id = 0;
	 m_id = ++id;
	 m_left = nullptr;
	 m_right = nullptr;

	 std::cout << "Sage " << m_id << " has been created\n";
}

void Sage::ChangeState(State p_state)
{
	/*std::string type1;
	std::string type2;

	if (m_state == State::THINKING && p_state == State::EATING)
	{
		type1 = "THINKING";
		type2 = "EATING";
	}

	if (m_state == State::EATING && p_state == State::THINKING)
	{
		type1 = "EATING";
		type2 = "THINKING";
	}

	if (m_state == State::WAITING && p_state == State::THINKING)
	{
		type1 = "WAITING";
		type2 = "THINKING";
	}

	if (m_state == State::THINKING && p_state == State::WAITING)
	{
		type1 = "THINKING";
		type2 = "WAITING";
	}

	if (m_state == State::WAITING && p_state == State::EATING)
	{
		type1 = "WAITING";
		type2 = "EATING";
	}

	if (m_state == State::EATING && p_state == State::WAITING)
	{
		type1 = "EATING";
		type2 = "WAITING";
	}

	std::cout << "Sage " << m_id << " changed from " << type1 << " to " << type2 << std::endl;*/
	m_state = p_state;
}

std::string Sage::GetState()
{
	switch (m_state)
	{
	case State::EATING:
		return "EATING";
		break;

	case State::THINKING:
		return "THINKING";
		break;

	case State::WAITING:
		return "WAITING";
		break;

	default:
		return "null";
		break;

	}
}

void Sage::main()
{
	while (true)
	{
		switch (m_state)
		{
		case State::THINKING:
			if (m_left->m_isUsed == true || m_right->m_isUsed == true)
				ChangeState(State::WAITING);

			else if (m_left->m_isUsed == false && m_right->m_isUsed == false)
			{
				ChangeState(State::EATING);
				m_left->m_isUsed = true;
				m_right->m_isUsed = true;
			}

			break;

		case State::WAITING:
			if (m_left->m_isUsed == false && m_right->m_isUsed == false)
			{
				ChangeState(State::EATING);
				m_left->m_isUsed = true;
				m_right->m_isUsed = true;
			}
			break;

		case State::EATING:
			ChangeState(State::THINKING);
			m_left->m_isUsed = false;
			m_right->m_isUsed = false;
			break;

		default:
			break;
		}
		++m_cyclesCompleted;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}

}