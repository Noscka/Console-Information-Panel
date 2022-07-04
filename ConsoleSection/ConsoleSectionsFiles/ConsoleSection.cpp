#include "ConsoleSection.h"

/* Add to SWT */
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        return { 0, 0 };
    }
}

ConsoleSection::ConsoleSection(ConsoleSide sectionSide, wchar_t seperatorChar, uint8_t padding)
{
    SectionSide = sectionSide;
    SeperatorChar = seperatorChar;
    Padding = padding;
    Content = DynamicArray<wchar_t>(10, 30);
}

void ConsoleSection::Overwrite(const wchar_t* output)
{
    /* Get console rows and columns*/
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    int rows, columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    /* Get cursor coords to return to*/
    COORD OriginalCoords = { GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X, GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y };
    COORD WritingCoords = { 0,rows - 3 };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), WritingCoords);

    std::wstring OutputString = std::wstring(columns, L'━');

    OutputString += L'\n';
    OutputString += output;
    OutputString += L'\n';

    wprintf(OutputString.c_str());

    Content.Array = (wchar_t*)output;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), OriginalCoords);
}

void ConsoleSection::Append(const wchar_t* output)
{
    int i = 0;
    while (true)
    {
        if (output[i] == NULL)
            break;
        Content.Append(output[i]);
        i++;
    }

    /* Get console rows and columns*/
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    int rows, columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    std::wstring OutputString = std::wstring(columns, SeperatorChar);

    OutputString += L'\n';
    OutputString += Content.Array;
    OutputString += L'\n';

    int NewLineCount = 0;

    for (wchar_t ch : Content)
    {
        if (ch == '\n')
            NewLineCount++;
    }

    /* Get cursor coords to return to*/
    COORD OriginalCoords = { GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X, GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y };
    COORD WritingCoords = { 0,rows - (NewLineCount+Padding) };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), WritingCoords);
    

    wprintf(OutputString.c_str());

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), OriginalCoords);

}