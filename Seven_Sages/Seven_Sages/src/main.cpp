#include <iostream>
#include <thread>

#include <Sage.h>
#include <Baguette.h>

int main()
{
	Sage sageArray[7];
	std::thread threadArray[7];
	Baguette baguetteArray[7];
	
	for (int i = 0; i < 7; ++i)
	{
		if (i == 0)
		{
			sageArray[i].SetLeft(&baguetteArray[0]);
			sageArray[i].SetRight(&baguetteArray[6]);
		}
		else if (i == 6)
		{
			sageArray[i].SetLeft(&baguetteArray[6]);
			sageArray[i].SetRight(&baguetteArray[0]);
		}
		else
		{
			sageArray[i].SetLeft(&baguetteArray[i]);
			sageArray[i].SetRight(&baguetteArray[i + 1]);
		}
	}

	for (int i = 0; i < 7; ++i)
	{
		threadArray[i] = std::thread{ &Sage::main, &sageArray[i] };
	}

	while (true)
	{
		for (int i = 0; i < 7; ++i)
		{
			std::cout << sageArray[i].GetState() << " / ";
			
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << std::endl;
	}

	for (int i = 0; i < 7; ++i)
	{
		threadArray[i].join();
	}
}