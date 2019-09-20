#pragma once
#include <string>
#include <Windows.h>

enum class Color
{
	WHITE = 15,
	RED = 4,
	BLUE = 1,
	GREEN = 2
};

class ColorPrint
{
public:
	ColorPrint() = delete;
	~ColorPrint() = delete;
	ColorPrint(const ColorPrint& p_other) = delete;

	template <typename Arg, typename... Args>
	static void Print(Color p_color, Arg&& p_arg, Args&&... p_args)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, static_cast<WORD>(p_color));

		std::cout << std::forward<Arg>(p_arg);
		((std::cout << std::forward<Args>(p_args)), ...);

		SetConsoleTextAttribute(hConsole, 15);
	}
};
