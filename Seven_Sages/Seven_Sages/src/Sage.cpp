#include <Sage.h>

Sage::Sage(unsigned int p_mealsPerDay)
{
	m_state = State::THINKING;
	static int id = 0;
	m_id = ++id;
	m_mealsPerDay = p_mealsPerDay;
	m_left = nullptr;
	m_right = nullptr;
}

std::string Sage::GetState() const
{
	switch (m_state)
	{
	case State::EATING:
		return "E";

	case State::THINKING:
		return "T";

	case State::WAITING:
		return "W";

	default:
		return "null";

	}
}

void Sage::PrintStatus() const
{
	switch (m_state)
	{
	case State::EATING:
		ColorPrint::Print(Color::RED, "E");
		break;

	case State::THINKING:
		ColorPrint::Print(Color::BLUE, "T");
		break;

	case State::WAITING:
		ColorPrint::Print(Color::GREEN, "W");
		break;

	default:
		break;
	}
}

void Sage::main()
{
	m_dayFinished = false;

	while (m_cyclesCompleted < m_mealsPerDay)
	{
		bool rightLock;
		bool leftLock;

		switch (m_state)
		{
		case State::THINKING:
			std::this_thread::sleep_for(std::chrono::seconds(5));
			SetState(State::WAITING);
			break;

		case State::WAITING:
			rightLock = m_right->m_mutex.try_lock();
			leftLock = m_left->m_mutex.try_lock();

			if (rightLock && leftLock)
			{
				SetState(State::EATING);
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
			else
			{
				if (rightLock)
					m_right->m_mutex.unlock();

				if (leftLock)
					m_left->m_mutex.unlock();
			}

			break;

		case State::EATING:
			m_left->m_mutex.unlock();
			m_right->m_mutex.unlock();
			SetState(State::THINKING);
			++m_cyclesCompleted;
			break;

		default:
			break;
		}
	}

	m_dayFinished = true;
}

