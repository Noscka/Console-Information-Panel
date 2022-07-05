#pragma once
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "../DynamicArray (different project)/DynamicArray.h"

enum ConsoleSide : USHORT
{
	Top = 1,
	Right = 2,
	Bottom = 3,
	Left = 4,
};

class ConsoleSection
{
private:
	// Section Style vars
	ConsoleSide SectionSide;
	wchar_t SeperatorChar;
	uint8_t Padding;

	// Clearing
	COORD OldBegin, OldEnd;

public:
	/// <summary>
	/// Section with more customizability
	/// </summary>
	/// <param name="sectionSide"> - Side where the section will be</param>
	/// <param name="seperatorChar"> - Character used to seperate outside and inside</param>
	/// <param name="padding"> - how much space between inside content and seperator</param>
	ConsoleSection(ConsoleSide sectionSide = Bottom, uint8_t padding = 1, wchar_t seperatorChar = L'━');

	/// <summary>
	/// Will change the content to the provided array
	/// </summary>
	/// <param name="output"> - the wide char array to overwrite with</param>
	void Overwrite(const wchar_t* output);

	void TestFill();

	/// <summary>
	/// Will add to the current array
	/// </summary>
	/// <param name="output"> - The array to append</param>
	//void Append(const wchar_t* output);
};