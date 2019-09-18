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
}

void Sage::ChangeState(State p_state)
{
	m_state = p_state;
}

std::string Sage::GetState()
{
	switch (m_state)
	{
	case State::EATING:
		return "E";
		break;

	case State::THINKING:
		return "T";
		break;

	case State::WAITING:
		return "W";
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
		bool rightLock;
		bool leftLock;

		if (m_state == State::THINKING)
		{
			std::this_thread::sleep_for(std::chrono::seconds(5));
			ChangeState(State::WAITING);
		}

		else if (m_state == State::WAITING)
		{
			rightLock = m_right->m_mutex.try_lock();
			leftLock = m_left->m_mutex.try_lock();

			if (rightLock && leftLock)
			{
				ChangeState(State::EATING);
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
			else
			{
				if (rightLock)
					m_right->m_mutex.unlock();
				
				if (leftLock)
					m_left->m_mutex.unlock();
			}
		}
		else if (m_state == State::EATING)
		{
			m_left->m_mutex.unlock();
			m_right->m_mutex.unlock();
			ChangeState(State::THINKING);
		}
		++m_cyclesCompleted;
	}


}