#pragma once

#include <Windows.h>
#include <stdio.h>

#include "ConsoleLibrary.h"
#include "Player.h"

enum GameStatus {
	GameMainMenu = 1,
	GameRunning = 2,
	GamePaused = 3,
	GameWon = 4,
	GameLostLife = 5,
	GameLost = 6,
	GameExit = 7,
	GameSplashScreen = 8
};

enum GameDifficulty {
	GameEasy = 1,
	GameMedium = 2,
	GameHard = 3
};

class Game {
private:
	ConsoleLibrary * m_Console;
	int m_LastAction;

	int m_GameStatus;
	COORD m_Arena;
	Player m_Player;
	COORD * m_Monsters;
	int m_MonsterNumber;

public:
	Game();
	Game(ConsoleLibrary * Console);
	~Game();

	void ShowSplash(void);
	void ShowMenu(void);
	void ShowGame(void);
	void ShowWon(void);
	void ShowLostLife(void);
	void ShowLost(void);
	void ShowExit(void);
	void Show(void);

	void ProcessSplash(void);
	void ProcessMenu(void);
	void ProcessGame(void);
	void ProcessWon(void);
	void ProcessLostLife(void);
	void ProcessLost(void);
	void ProcessExit(void);
	void ProcessState(void);

	void SetConsole(ConsoleLibrary * Console);

	void StartNewGame(int Difficulty);
	void EndGame(void);
	void CheckCollisions(void);
	int GetAction(void);
	int GetStatus(void);
	void MoveMonsters(void);
};