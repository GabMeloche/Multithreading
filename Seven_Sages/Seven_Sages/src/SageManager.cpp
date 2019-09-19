#include <SageManager.h>
#include <iostream>

SageManager::SageManager(unsigned int p_numberOfSages, unsigned int p_numberOfMeals, Baguette* p_baguettes)
{
	m_sages = new Sage[p_numberOfSages];
	m_numberOfSages = p_numberOfSages;

	for (int i = 0; i < p_numberOfSages; ++i)
	{
		m_sages[i].SetMealsPerDay(p_numberOfMeals);

		if (i == 0)
		{
			m_sages[i].SetLeft(&p_baguettes[0]);
			m_sages[i].SetRight(&p_baguettes[p_numberOfSages - 1]);
		}
		else if (i == p_numberOfSages - 1)
		{
			m_sages[i].SetLeft(&p_baguettes[p_numberOfSages - 1]);
			m_sages[i].SetRight(&p_baguettes[0]);
		}
		else
		{
			m_sages[i].SetLeft(&p_baguettes[i]);
			m_sages[i].SetRight(&p_baguettes[i + 1]);
		}
	}

}

SageManager::~SageManager()
{
	delete m_sages;
}

void SageManager::SageCycle(uint16_t p_numberOfDays)
{
	for (int i = 0; i < p_numberOfDays; ++i) // day of the week
	{
		std::vector<std::thread> threadArray(m_numberOfSages);

		for (int i = 0; i < m_numberOfSages; ++i)
		{
			threadArray[i] = std::thread{ &Sage::main, &m_sages[i] };
		}

		std::vector<bool> isFinished(m_numberOfSages);

		for (int i = 0; i < isFinished.size(); ++i)
			isFinished[i] = false;

		while (true)
		{
			for (int i = 0; i < m_numberOfSages; ++i)
			{
				m_sages[i].PrintStatus();
				std::cout << " | ";

				if (m_sages[i].IsDayFinished())
					isFinished[i] = true;
			}
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << std::endl;

			bool everyoneFinished = false;

			for (int i = 0; i < isFinished.size(); ++i)
				isFinished[i] ? everyoneFinished = true : everyoneFinished = false;

			if (everyoneFinished)
			{
				for (int i = 0; i < m_numberOfSages; ++i)
				{
					threadArray[i].join();
					m_sages[i].SetCyclesCompleted(0);
				}
				std::cout << "\n---- Day " << i << " finished ----\n";
				break;
			}
		}
	}
}