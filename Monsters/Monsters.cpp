// Monsters.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConsoleLibrary.h"
#include "Game.h"

int main()
{
	ConsoleLibrary Console;
	Game Game(&Console);

	Console.SetTitle("Monsters");

	while (Game.GetStatus() != GameExit) {
		Game.ProcessState();
	}

    return 0;
}

