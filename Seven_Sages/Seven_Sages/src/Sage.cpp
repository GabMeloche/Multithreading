#include <Sage.h>
#include <iostream>

void Sage::ChangeState(State p_state)
{
	std::cout << "changed from " + static_cast<char>(m_state);
	std::cout <<  " to " + static_cast<char>(p_state) << std::endl;
	m_state = p_state;
}

void Sage::main()
{

}