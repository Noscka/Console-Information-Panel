#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "ConsoleSectionsFiles/ConsoleSection.h"

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    //ShowConsoleCursor(false);

    ConsoleSection CS = ConsoleSection();

    CS.Append(L"aa\n");
    CS.Append(L"gwagwa\n");
    CS.Append(L"552151\n");
    CS.Append(L"5521gg51\n");

    std::wcout << L"cunt" << std::endl;

    system("pause");
    return 0;
}