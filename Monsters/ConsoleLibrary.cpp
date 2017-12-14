#include "stdafx.h"
#include "ConsoleLibrary.h"

ConsoleLibrary::ConsoleLibrary() {
	m_Screen = GetStdHandle( STD_OUTPUT_HANDLE );
	m_Keyboard = GetStdHandle( STD_INPUT_HANDLE );

	SetTextColor( Red | Green | Blue );
	SetBackgroundColor( 0 );
}

ConsoleLibrary::~ConsoleLibrary() {

}

void ConsoleLibrary::SetBackgroundColor(WORD Color) {
	m_BackgroundColor = 0;

	if (Color & Red) {
		m_BackgroundColor |= BACKGROUND_RED;
	}
	if (Color & Green) {
		m_BackgroundColor |= BACKGROUND_GREEN;
	}
	if (Color & Blue) {
		m_BackgroundColor |= BACKGROUND_BLUE;
	}

	SetConsoleTextAttribute(m_Screen, m_TextColor | m_BackgroundColor);
}

void ConsoleLibrary::SetTextColor(WORD Color) {
	m_TextColor = 0;

	if (Color & Red) {
		m_TextColor |= FOREGROUND_RED;
	}
	if (Color & Green) {
		m_TextColor |= FOREGROUND_GREEN;
	}
	if (Color & Blue) {
		m_TextColor |= FOREGROUND_BLUE;
	}

	SetConsoleTextAttribute(m_Screen, m_TextColor | m_BackgroundColor);
}

void ConsoleLibrary::SetTitle(char * Title) {
	SetConsoleTitleA(Title);
}

void ConsoleLibrary::Clear(void) {
	COORD Start;
	DWORD Written;

	Start.X = 0;
	Start.Y = 0;

	FillConsoleOutputAttribute(m_Screen, m_TextColor | m_BackgroundColor, 80 * 25, Start, &Written);
	FillConsoleOutputCharacterA(m_Screen, ' ', 80 * 25, Start, &Written);
	SetConsoleCursorPosition(m_Screen, Start);
}

void ConsoleLibrary::SetPosition(COORD Position) {
	SetConsoleCursorPosition(m_Screen, Position);
}

void ConsoleLibrary::OutputString(char * String) {
	DWORD Written;

	WriteConsoleA(m_Screen, String, strlen(String), &Written, NULL);
}

void ConsoleLibrary::Read(char * Buffer, DWORD BufferSize) {
	DWORD Read;

	ReadConsoleA(m_Keyboard, Buffer, BufferSize, &Read, NULL);
}

int ConsoleLibrary::GetKey(void) {
	DWORD Read;
	INPUT_RECORD Event;

	ReadConsoleInputA(m_Keyboard, &Event, 1, &Read);

	if (Event.EventType == KEY_EVENT) {
		if (Event.Event.KeyEvent.bKeyDown) {
			return Event.Event.KeyEvent.wVirtualKeyCode;
		}
	}

	return 0;
}