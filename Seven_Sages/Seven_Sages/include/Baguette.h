#pragma once
#include <mutex>

struct Baguette
{
public:
	std::mutex m_mutex{};
};
