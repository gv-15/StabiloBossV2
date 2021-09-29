#pragma once

enum ConsoleColor {White, Blue, Red, Green, Yellow, Black};

class System
{
public:
	System();
	virtual ~System();

	static void Clear();
	static void HideCursor();
	static void SetCursorPos(int x, int y);
	static void SetTextColor(ConsoleColor foregroundColor, ConsoleColor backgroundColor= Black);
	static bool IsKeyPressed();
	static char GetNextPressedKey();
};

