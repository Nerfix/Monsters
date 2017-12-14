#include "stdafx.h"
#include "Game.h"

Game::Game() {
	m_Console = NULL;
	m_GameStatus = GameSplashScreen;
	m_LastAction = 0;
	m_Monsters = NULL;
}

Game::Game(ConsoleLibrary * Console) {
	m_Console = Console;
	m_GameStatus = GameSplashScreen;
	m_LastAction = 0;
	m_Monsters = NULL;
}

Game::~Game() {
	m_Console = NULL;
	m_GameStatus = GameSplashScreen;
	m_LastAction = 0;
	m_Monsters = NULL;
}

void Game::SetConsole(ConsoleLibrary * Console) {
	m_Console = Console;
}

int Game::GetStatus(void) {
	return m_GameStatus;
}

void Game::ShowSplash(void) {
	m_Console->Clear();
	m_Console->OutputString("\tWelcome to Monsters 1.0 \n\n");
	m_Console->OutputString("Playing Monsters is very easy. \n\n");

	m_Console->OutputString("The objective of the game is to destroy \n");
	m_Console->OutputString("all the monsters. Two or more monsters \n");
	m_Console->OutputString("are destroyed when they move to the \n");
	m_Console->OutputString("same cell in the field. You also lose a \n");
	m_Console->OutputString("life if you move to a cell where a \n");
	m_Console->OutputString("monster is. You move the player with the \n");
	m_Console->OutputString("numerical keypad in the eight possible \n");
	m_Console->OutputString("directions. You can also press Insert \n");
	m_Console->OutputString("which will make you leap to a random \n");
	m_Console->OutputString("place in the field.\n\n");

	m_Console->SetTextColor(Red);
	m_Console->OutputString("NOTE: Make sure NumLock is turned off.\n\n");
	m_Console->SetTextColor(Red | Green | Blue);

	m_Console->OutputString("There are three difficulties available:\n\n");
	m_Console->OutputString(" Easy :    Monsters = 10    Arena = 25*15\n");
	m_Console->OutputString("           Lives    =  4    Leaps = 3\n");
	m_Console->OutputString(" Medium :  Monsters = 20    Arena = 35*18\n");
	m_Console->OutputString("           Lives    =  3    Leaps = 2\n");
	m_Console->OutputString(" Hard :    Monsters = 30    Arena = 50*23\n");
	m_Console->OutputString("           Lives    =  2    Leaps = 1\n");
}

void Game::ShowMenu(void) {
	COORD Position;

	m_Console->SetBackgroundColor(0);
	m_Console->SetTextColor(Red);
	m_Console->Clear();

	m_Console->SetBackgroundColor(Red | Green | Blue);

	m_Console->OutputString("                                            \n");
	m_Console->OutputString("           Monsters - version 1.0           \n");
	m_Console->OutputString("                                              ");

	m_Console->SetBackgroundColor(0);
	m_Console->SetTextColor(Red | Green | Blue);

	Position.X = 1;
	Position.Y = 4;
	m_Console->SetPosition(Position);
	m_Console->OutputString("What do you want to do? ");

	Position.X = 3;
	Position.Y = 6;
	m_Console->SetPosition(Position);
	m_Console->OutputString("1 - Start new game - Easy");
	Position.Y = 7;
	m_Console->SetPosition(Position);
	m_Console->OutputString("2 - Start new game - Medium");
	Position.Y = 8;
	m_Console->SetPosition(Position);
	m_Console->OutputString("3 = Start new game - Hard");

	Position.Y = 10;
	m_Console->SetPosition(Position);
	m_Console->OutputString("Q - Exit game");
}

void Game::ShowGame(void) {
	COORD Position;
	int Monster;

	m_Console->SetBackgroundColor(0);
	m_Console->SetTextColor(Green);

	m_Player.GetPosition(&Position);

	m_Console->SetPosition(Position);
	m_Console->OutputString("P");

	int FieldX, FieldY;
	m_Console->SetBackgroundColor(Red | Green | Blue);
	m_Console->SetTextColor(Red | Green | Blue);

	for (FieldY = 0; FieldY <= m_Arena.Y; FieldY++) {
		if ((FieldY == 0) || (FieldY == m_Arena.Y)) {
			for (FieldX = 0; FieldX <= m_Arena.X; FieldX++) {
				Position.X = FieldX;
				Position.Y = FieldY;
				m_Console->SetPosition(Position);
				m_Console->OutputString("#");
			}
		}
		else {
			Position.X = 0;
			Position.Y = FieldY;
			m_Console->SetPosition(Position);
			m_Console->OutputString("#");
			Position.X = m_Arena.X;
			Position.Y = FieldY;
			m_Console->SetPosition(Position);
			m_Console->OutputString("#");
		}
	}

	m_Console->SetBackgroundColor(0);
	m_Console->SetTextColor(Red);
	for (Monster = 0; Monster < m_MonsterNumber; Monster++) {
		if (m_Monsters[Monster].X != 0) {
			m_Console->SetPosition(m_Monsters[Monster]);
			m_Console->OutputString("M");
		}
	}

	char Buffer[100];

	sprintf_s(Buffer, "    Lives: %d \t\t Score: %d \t Leaps: %d",
		m_Player.GetLives() - 1,
		m_Player.GetScore(),
		m_Player.GetLeaps());

	Position.X = 5;
	Position.Y = 24;
	m_Console->SetPosition(Position);
	m_Console->SetTextColor(Red | Green);
	m_Console->OutputString(Buffer);
}

void Game::ShowWon(void) {
	ShowGame();

	COORD Position;

	Position.X = 20;
	Position.Y = 11;
	m_Console->SetPosition(Position);

	m_Console->SetBackgroundColor(Green);
	m_Console->SetTextColor(Red);

	m_Console->OutputString("########################################");
	Position.Y = 12;
	m_Console->SetPosition(Position);
	m_Console->OutputString("#           Congratulations!           #");
	Position.Y = 13;
	m_Console->SetPosition(Position);
	m_Console->OutputString("#  You have killed all the monsters.   #");
	Position.Y = 14;
	m_Console->SetPosition(Position);
	m_Console->OutputString("########################################");
}

void Game::ShowLostLife(void) {
	ShowGame();

	COORD Position;

	Position.X = 20;
	Position.Y = 11;
	m_Console->SetPosition(Position);

	m_Console->SetBackgroundColor(Green);
	m_Console->SetTextColor(Red);

	m_Console->OutputString("########################################");
	Position.Y = 12;
	m_Console->SetPosition(Position);
	m_Console->OutputString("#         You have lost a life         #");
	Position.Y = 13;
	m_Console->SetPosition(Position);
	m_Console->OutputString("########################################");
}

void Game::ShowLost(void) {
	ShowGame();

	COORD Position;

	Position.X = 20;
	Position.Y = 11;
	m_Console->SetPosition(Position);

	m_Console->SetBackgroundColor(Green);
	m_Console->SetTextColor(Red);

	m_Console->OutputString("########################################");
	Position.Y = 12;
	m_Console->SetPosition(Position);
	m_Console->OutputString("              Tough luck!               ");
	Position.Y = 13;
	m_Console->SetPosition(Position);
	m_Console->OutputString("      You have lost all your lives.     ");
	Position.Y = 14;
	m_Console->SetPosition(Position);
	m_Console->OutputString("########################################");
}

void Game::ShowExit(void) {
	m_Console->SetBackgroundColor(0);
	m_Console->SetTextColor(Red | Green | Blue);
	m_Console->Clear();
	m_Console->OutputString("\n    Monster 1.0 \n\n\n");
	m_Console->OutputString(" by: Ventsislav Tanev \n\n\n\n");
	m_Console->OutputString("Thanks for playing!\n\n\n");
	m_Console->OutputString("No real monsters were hurt during ");
	m_Console->OutputString("the development of this game!\n\n");
}

void Game::Show(void) {
	m_Console->SetBackgroundColor(0);
	m_Console->SetTextColor(Red | Green | Blue);
	m_Console->Clear();

	switch (m_GameStatus) {
	case GameMainMenu:
		ShowMenu();
		break;
		
	case GameRunning:
		ShowGame();
		break;

	case GameWon:
		ShowWon();
		break;

	case GameLostLife:
		ShowLostLife();
		break;

	case GameLost:
		ShowLost();
		break;

	case GameExit:
		ShowExit();
		break;

	case GameSplashScreen:
		ShowSplash();
		break;

	default:
		break;
	}
}

void Game::StartNewGame(int Difficulty) {
	int Monster;

	COORD Position;

	m_GameStatus = GameRunning;

	switch (Difficulty) {
	case GameEasy:
		m_MonsterNumber = 10;
		m_Player.SetLives(4);
		m_Player.SetLeaps(3);
		m_Arena.X = 25;
		m_Arena.Y = 15;
		break;

	case GameMedium:
		m_MonsterNumber = 20;
		m_Player.SetLives(3);
		m_Player.SetLeaps(2);
		m_Arena.X = 35;
		m_Arena.Y = 18;
		break;

	case GameHard:
		m_MonsterNumber = 30;
		m_Player.SetLives(2);
		m_Player.SetLeaps(1);
		m_Arena.X = 50;
		m_Arena.Y = 23;
		break;
	}

	m_Player.RandomLeap(m_Arena);
	m_Player.GetPosition(&Position);
	m_Player.SetScore(0);

	m_Monsters = new COORD[m_MonsterNumber];
	srand(time(NULL));

	for (Monster = 0; Monster < m_MonsterNumber; Monster++) {
		do {
			m_Monsters[Monster].X = (rand() % (m_Arena.X - 1)) + 1;
			m_Monsters[Monster].Y = (rand() % (m_Arena.Y - 1)) + 1;
		} while ((m_Monsters[Monster].X == Position.X) &&
			(m_Monsters[Monster].Y == Position.Y));
	}
}

int Game::GetAction(void) {
	m_LastAction = m_Console->GetKey();

	return m_LastAction;
}

void Game::MoveMonsters(void)
{
	COORD Distance, Position;
	int Monster;

	m_Player.GetPosition(&Position);

	for (Monster = 0; Monster < m_MonsterNumber; Monster++) {
		if (m_Monsters[Monster].X != 0) {
			Distance.X = Position.X - m_Monsters[Monster].X;
			Distance.Y = Position.Y - m_Monsters[Monster].Y;

			if (Distance.X > 0) {
				Distance.X = 1;
			}
			if (Distance.X < 0) {
				Distance.X = -1;
			}
			if (Distance.Y > 0) {
				Distance.Y = 1;
			}
			if (Distance.Y < 0) {
				Distance.Y = -1;
			}

			m_Monsters[Monster].X += Distance.X;
			m_Monsters[Monster].Y += Distance.Y;
		}
	}
}

void Game::ProcessSplash(void) {
	if (m_LastAction) {
		m_GameStatus = GameMainMenu;
	}
}

void Game::ProcessMenu(void) {
	switch (m_LastAction) {
	case VK_ESCAPE:
	case 'Q':
	case 'q':
		m_GameStatus = GameExit;
		break;

	case '1':
		StartNewGame(GameEasy);
		m_GameStatus = GameRunning;
		break;

	case '2':
		StartNewGame(GameMedium);
		m_GameStatus = GameRunning;
		break;

	case '3':
		StartNewGame(GameHard);
		m_GameStatus = GameRunning;
		break;

	default:
		break;
	}
}

void Game::ProcessGame(void) {
	COORD Movement;
	int Monster, MonstersAlive;

	Movement.X = 0;
	Movement.Y = 0;

	switch (m_LastAction) {
	case VK_UP:
		Movement.Y = -1;
		break;

	case VK_DOWN:
		Movement.Y = 1;
		break;

	case VK_LEFT:
		Movement.X = -1;
		break;

	case VK_RIGHT:
		Movement.X = 1;
		break;

	case VK_HOME:
		Movement.X = -1;
		Movement.Y = -1;
		break;

	case VK_PRIOR:
		Movement.X = 1;
		Movement.Y = -1;
		break;

	case VK_END:
		Movement.X = -1;
		Movement.Y = 1;
		break;

	case VK_NEXT:
		Movement.X = 1;
		Movement.Y = 1;
		break;

	case VK_INSERT:
		if (m_Player.GetLeaps() > 0) {
			m_Player.RandomLeap(m_Arena);
			m_Player.SetLeaps(m_Player.GetLeaps() - 1);
		}
		break;

	case VK_ESCAPE:
		EndGame();
		m_GameStatus = GameMainMenu;
		break;
	}

	if ((Movement.X != 0) || (Movement.Y != 0)) {
		COORD PlayerPosition;

		m_Player.GetPosition(&PlayerPosition);

		if ((Movement.X + PlayerPosition.X > 0) &&
			(Movement.Y + PlayerPosition.Y > 0) &&
			(Movement.X + PlayerPosition.X < m_Arena.X) &&
			(Movement.Y + PlayerPosition.Y < m_Arena.Y)) {

			m_Player.Move(Movement);
		}

		MoveMonsters();
		CheckCollisions();

		MonstersAlive = 0;
		for (Monster = 0; Monster < m_MonsterNumber; Monster++) {
			if (m_Monsters[Monster].X != 0) {
				MonstersAlive = 1;
				break;
			}
		}

		if (MonstersAlive == 0) {
			m_GameStatus = GameWon;
		}
	}
}

void Game::CheckCollisions()
{
	COORD Position;
	int MonsterA, MonsterB;

	m_Player.GetPosition(&Position);

	for (MonsterA = 0; MonsterA < m_MonsterNumber; MonsterA++) {
		if (m_Monsters[MonsterA].X != 0) {
			if ((m_Monsters[MonsterA].X == Position.X) &&
				(m_Monsters[MonsterA].Y == Position.Y)){

				m_Monsters[MonsterA].X = 0;
				m_Monsters[MonsterA].Y = 0;
			
				if (m_Player.GetLives() - 1 <= 0) {
					m_GameStatus = GameLost;
				}
				else {
					m_GameStatus = GameLostLife;
				}

				return;
			}

			for (MonsterB = MonsterA + 1; MonsterB < m_MonsterNumber; MonsterB++) {
				if (m_Monsters[MonsterB].X != 0) {
					if ((m_Monsters[MonsterA].X == m_Monsters[MonsterB].X) &&
						m_Monsters[MonsterA].Y == m_Monsters[MonsterB].Y) {

						m_Monsters[MonsterA].X = m_Monsters[MonsterB].X = 0;
						m_Monsters[MonsterA].Y = m_Monsters[MonsterB].Y = 0;
						m_Player.SetScore(m_Player.GetScore() + 15);
					}
				}
			}
		}
	}
}

void Game::ProcessWon(void) {
	if (m_LastAction) {
		m_GameStatus = GameMainMenu;
	}

	EndGame();
}

void Game::EndGame(void)
{
	if (m_Monsters != NULL) {
		delete[] m_Monsters;
	}

	m_Monsters = NULL;
}

void Game::ProcessLostLife(void) {
	int isValid = 0;
	int Monster;
	COORD Position;

	m_Player.SetLives(m_Player.GetLives() - 1);
	if (m_Player.GetLives() - 1 <= -1) {
		m_GameStatus = GameLost;
	}
	else {
		m_GameStatus = GameRunning;
		isValid = 0;

		do {
			m_Player.RandomLeap(m_Arena);
			m_Player.GetPosition(&Position);

			for (Monster = 0; Monster < m_MonsterNumber; Monster++) {
				if (m_Monsters[Monster].X != 0) {
					if ((m_Monsters[Monster].X != Position.X) &&
						m_Monsters[Monster].Y != Position.Y) {

						isValid = 1;
					}
					else {
						isValid = 0;
					}
				}
			}
		} while (isValid == 0);
	}
}

void Game::ProcessLost(void) {
	if (m_LastAction) {
		m_GameStatus = GameMainMenu;
	}

	EndGame();
	Show();
}

void Game::ProcessState(void) {
	if (m_GameStatus == GameSplashScreen) {
		Show();
	}

	if (GetAction()) {
		switch (m_GameStatus) {
		case GameMainMenu:
			ProcessMenu();
			break;

		case GameRunning:
			ProcessGame();
			break;

		case GameWon:
			ProcessWon();
			break;

		case GameLostLife:
			ProcessLostLife();
			break;

		case GameLost:
			ProcessLost();
			break;

		case GameSplashScreen:
			ProcessSplash();
			break;

		default:
			break;

		}

		Show();
	}
}

void Game::ProcessExit(void) {
	EndGame();
	m_GameStatus = GameExit;
}