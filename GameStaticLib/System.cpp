#include "pch.h"
#include "System.h"
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>


System::System()
{
}


System::~System()
{
}

void System::Clear()
{

	// Get the Win32 handle representing standard output.
	// This generally only has to be done once, so we make it static.
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	// std::cout uses a buffer to batch writes to the underlying console.
	// We need to flush that to the console because we're circumventing
	// std::cout entirely; after we clear the console, we don't want
	// stale buffered text to randomly be written out.
	std::cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(hOut, &csbi))
	{
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(hOut, topLeft);
}

void System::HideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void System::SetCursorPos(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void System::SetTextColor(ConsoleColor foregroundColor, ConsoleColor backgroundColor)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD Color = 0;
	switch (foregroundColor)
	{
	case Blue:
		Color |= FOREGROUND_BLUE; break;
	case Red:
		Color |= FOREGROUND_RED; break;
	case Green:
		Color |= FOREGROUND_GREEN; break;
	case Yellow:
		Color |= FOREGROUND_RED | FOREGROUND_GREEN; break;
	case White:
		Color |= FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN; break;
	case Black:
	default: break;
	}
	switch (backgroundColor)
	{
	case Blue:
		Color |= BACKGROUND_BLUE; break;
	case Red:
		Color |= BACKGROUND_RED; break;
	case Green:
		Color |= BACKGROUND_GREEN; break;
	case Yellow:
		Color |= BACKGROUND_RED | BACKGROUND_GREEN; break;
	case White:
		Color |= BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN; break;
	case Black:
	default: break;
	}
	SetConsoleTextAttribute(hOut, Color);
}

bool System::IsKeyPressed()
{
	return _kbhit();
}

char System::GetNextPressedKey()
{
	return _getch();
}