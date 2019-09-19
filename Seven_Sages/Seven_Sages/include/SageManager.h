#pragma once
#include <Sage.h>
#include <Baguette.h>
#include <vector>

class SageManager
{
public:
	SageManager(unsigned int p_numberOfSages, unsigned int p_numberOfMeals, Baguette* p_baguettes);
	~SageManager();

	void SageCycle(uint16_t p_numberOfDays);

private:
	int m_numberOfSages;
	Sage* m_sages;
};