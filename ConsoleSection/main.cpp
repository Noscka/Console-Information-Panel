#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>


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



void WriteInInfo(const wchar_t* output)
{
    /* Get console rows and columns*/
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    int rows, columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    /* Get cursor coords to return to*/
    COORD OriginalCoords = { GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X, GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y };
    COORD WritingCoords = {0,rows-3};

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), WritingCoords);
    
    std::wstring OutputString = std::wstring(columns, L'━');
    
    OutputString += L'\n';
    OutputString += output;
    OutputString += L'\n';

    wprintf(OutputString.c_str());

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), OriginalCoords);
}

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    ShowConsoleCursor(false);

    WriteInInfo(L"aa");

    std::wcout << L"cunt" << std::endl;

    system("pause");
    return 0;
}