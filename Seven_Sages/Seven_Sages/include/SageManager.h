#pragma once
#include <iostream>
#include <vector>
#include <Sage.h>
#include <Baguette.h>

class SageManager
{
private:
	unsigned int m_numberOfSages;
	Sage* m_sages;
	
public:
	SageManager(unsigned int p_numberOfSages, unsigned int p_numberOfMeals, std::vector<Baguette>& p_baguettes);
	~SageManager();

	void SageCycle(uint16_t p_numberOfDays);

};