#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "ConsoleSectionsFiles/ConsoleSection.h"

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    //ShowConsoleCursor(false);

    ConsoleSection CS = ConsoleSection(Bottom, 0);

    CS.Overwrite(L"agag\ngwag,gwaga,gaw,g\nfawfaw\n");

    std::wcout << L"cunt" << std::endl;

    CS.TestFill();

    while (true)
    {
        CS.Overwrite(L"agag\ngwag,gwaga,gaw,g\nfawfaw\n");
        Sleep(100);
    }

    system("pause");
    return 0;
}