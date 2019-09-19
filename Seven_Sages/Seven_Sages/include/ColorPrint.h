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
	ColorPrint(ColorPrint& p_color) = delete;

	template <typename Arg, typename... Args>
	static void Print(Color p_color, Arg&& p_var1, Args&&... p_var2)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, static_cast<WORD>(p_color));

		std::cout << std::forward<Arg>(p_var1);
		((std::cout << std::forward<Args>(p_var2)), ...);

		SetConsoleTextAttribute(hConsole, 15);
	}
};
