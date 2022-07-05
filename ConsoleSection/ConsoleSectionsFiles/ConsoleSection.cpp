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

ConsoleSection::ConsoleSection(ConsoleSide sectionSide, uint8_t padding, wchar_t seperatorChar)
{
    SectionSide = sectionSide;
    SeperatorChar = seperatorChar;
    Padding = padding;
}

void ConsoleSection::Refresh()
{
    COORD tl = OldBegin;
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = (s.srWindow.Right - s.srWindow.Left + 1) * (OldEnd.Y - OldBegin.Y);
    FillConsoleOutputCharacterW(console, L' ', cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    //SetConsoleCursorPosition(console, tl);
}

void ConsoleSection::Overwrite(const wchar_t* output)
{
    /* Get console rows and columns*/
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    int rows, columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    /* Calculate amoutn of lines to use for the section*/
    int NewLineCount = 0;
    
    int i = 0;
    while (true)
    {
        if (output[i] == NULL)
            break;

        if (output[i] == '\n')
            NewLineCount++;

        i++;
    }

    /* Get cursor coords to return to*/
    COORD OriginalCoords = { GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X, GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y };
    COORD WritingCoords = { 0,rows - (NewLineCount + 2*Padding)-1 };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), WritingCoords);

    std::wstring OutputString = std::wstring(columns, L'━');

    OutputString += std::wstring(Padding+1, L'\n');
    OutputString += output;
    OutputString += std::wstring(Padding, L'\n');

    Refresh();
    wprintf(OutputString.c_str());

    OldBegin = WritingCoords;
    OldEnd = { (SHORT)columns, GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y };

    //Content.Array = (wchar_t*)output;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), OriginalCoords);
}

//void ConsoleSection::Append(const wchar_t* output)
//{
//    int i = 0;
//    while (true)
//    {
//        if (output[i] == NULL)
//            break;
//        Content.Append(output[i]);
//        i++;
//    }
//
//    /* Get console rows and columns*/
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//
//    int rows, columns;
//
//    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
//    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
//
//    std::wstring OutputString = std::wstring(columns, SeperatorChar);
//
//    OutputString += L'\n';
//    OutputString += Content.Array;
//    OutputString += L'\n';
//
//    int NewLineCount = 0;
//
//    for (wchar_t ch : Content)
//    {
//        if (ch == '\n')
//            NewLineCount++;
//    }
//
//    /* Get cursor coords to return to*/
//    COORD OriginalCoords = { GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X, GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y };
//    COORD WritingCoords = { 0,rows - (NewLineCount+Padding) };
//
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), WritingCoords);
//    
//
//    wprintf(OutputString.c_str());
//
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), OriginalCoords);
//
//}