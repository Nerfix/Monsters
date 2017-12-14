#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Move(COORD Direction) {
	m_Position.X += Direction.X;
	m_Position.Y += Direction.Y;
}

void Player::RandomLeap(COORD ArenaSize) {
	srand(time(NULL));

	m_Position.X = (rand() % (ArenaSize.X - 1)) + 1;
	m_Position.Y = (rand() % (ArenaSize.Y - 1)) + 1;
}

void Player::GetPosition(COORD * Position) {
	memcpy(Position, &m_Position, sizeof(COORD));
}

void Player::SetLives(short Lives) {
	m_Lives = Lives;
}

short Player::GetLives(void) {
	return m_Lives;
}

void Player::SetScore(int Score) {
	m_Score = Score;
}

int Player::GetScore(void) {
	return m_Score;
}

void Player::SetLeaps(int Leaps) {
	m_Leaps = Leaps;
}

int Player::GetLeaps(void) {
	return m_Leaps;
}