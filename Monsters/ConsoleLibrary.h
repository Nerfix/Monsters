#pragma once

#include <windows.h>

enum ConsoleColor
{
	Red = 1,
	Green = 2,
	Blue = 4
};

class ConsoleLibrary
{
	HANDLE m_Screen;
	HANDLE m_Keyboard;

	WORD m_TextColor;
	WORD m_BackgroundColor;

public:
	ConsoleLibrary();
	~ConsoleLibrary();

	void SetBackgroundColor( WORD Color );
	void SetTextColor( WORD Color );
	void SetTitle( char * Title );
	void SetPosition( COORD Position );

	void Clear( void );
	void OutputString( char * String );

	void Read( char * Buffer, DWORD BufferSize );
	int GetKey( void );
};