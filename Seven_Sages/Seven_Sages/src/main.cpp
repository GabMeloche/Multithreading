#include <Baguette.h>
#include <SageManager.h>

#define SAGE_QT 7
#define NUMBER_OF_DAYS 7
#define MEALS_PER_DAY 3

int main()
{
	std::vector<Baguette> baguetteArray(SAGE_QT);
	SageManager sages(SAGE_QT, MEALS_PER_DAY, baguetteArray);
	sages.SageCycle(NUMBER_OF_DAYS);
}