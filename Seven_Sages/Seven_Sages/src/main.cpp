#include <iostream>
#include <thread>

#include <Sage.h>
#include <Baguette.h>

#define SAGE_QT 7

int main()
{
	Sage sageArray[SAGE_QT];
	std::thread threadArray[SAGE_QT];
	Baguette baguetteArray[SAGE_QT];

	for (int i = 0; i < SAGE_QT; ++i)
	{
		if (i == 0)
		{
			sageArray[i].SetLeft(&baguetteArray[0]);
			sageArray[i].SetRight(&baguetteArray[SAGE_QT - 1]);
		}
		else if (i == SAGE_QT - 1)
		{
			sageArray[i].SetLeft(&baguetteArray[SAGE_QT - 1]);
			sageArray[i].SetRight(&baguetteArray[0]);
		}
		else
		{
			sageArray[i].SetLeft(&baguetteArray[i]);
			sageArray[i].SetRight(&baguetteArray[i + 1]);
		}
	}


	for (int i = 0; i < 7; ++i) // day of the week
	{
		for (int i = 0; i < SAGE_QT; ++i)
		{
			threadArray[i] = std::thread{ &Sage::main, &sageArray[i] };
		}

		bool isFinished[SAGE_QT];
		for (auto& finish : isFinished)
			finish = false;

		while (true)
		{
			for (int i = 0; i < SAGE_QT; ++i)
			{
				std::cout << sageArray[i].GetState() << " / ";
				if (sageArray[i].IsDayFinished())
					isFinished[i] = true;
			}
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << std::endl;

			bool everyoneFinished = false;

			for (auto& finish : isFinished)
				finish ? everyoneFinished = true : everyoneFinished = false;

			if (everyoneFinished)
			{
				for (int i = 0; i < SAGE_QT; ++i)
				{
					threadArray[i].join();
					sageArray[i].SetCyclesCompleted(0);
				}
				std::cout << "\n---- Day " << i << " finished ----\n\n";
				break;
			}
		}
	}

}