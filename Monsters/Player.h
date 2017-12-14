#pragma once
#include <Windows.h>
#include <time.h>


class Player
{
private:
	COORD m_Position;
	short m_Lives;
	int m_Score;
	int m_Leaps;

public:
	Player();
	~Player();

	void Move(COORD Direction);
	void RandomLeap(COORD ArenaSize);

	void GetPosition(COORD * Position);

	void SetLives(short Lives);
	short GetLives(void);

	void SetScore(int Score);
	int GetScore(void);

	void SetLeaps(int Leaps);
	int GetLeaps(void);
};

