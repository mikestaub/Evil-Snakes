#include <iostream>
#include "drawEngine.h"
#include "game.h"

using namespace std;

DrawEngine::DrawEngine(int xSize, int ySize)
{
	screenWidth = xSize;
	screenHeight = ySize;

	// set cursor visibility to false
	cursorVisibility(false);
}

DrawEngine::~DrawEngine()
{
	// set cursor visibility to true
	cursorVisibility(true);
}

int DrawEngine::createSprite(int index, char c)
{
	// make sure index is within bounds of the array
	if(index >= 0 && index < 16)
	{
		spriteImage[index] = c;
		return 1;
	}

	// if out of range, return -1
	return -1;
}

void DrawEngine::deleteSprite(int index)
{
	// In this implementation this is not needed, becuase we are not 
	// dynamically allocating space for sprites. It is here for conceptual purposes only.
}

void DrawEngine::drawSprite(int index, int posx, int posy)
{
	// go to the correct location
	gotoxy(posx, posy);
	// print the character
	cout << spriteImage[index];
}

void DrawEngine::eraseSprite(int posx, int posy)
{
	gotoxy(posx, posy);
	cout << ' ';
}

void DrawEngine::setMap(char **data)
{
	map = data;
}

void DrawEngine::createBackgroundTile(int index, char c)
{
	if(index >= 0 && index < 16)
		tileImage[index] = c;
}

void DrawEngine::drawBackground(void)
{
	if(map)
	{
		for(int y = 0 ; y < screenHeight ; y++)
		{
			// start at the correct spot
			gotoxy(0, y);

				for(int x = 0 ; x < screenWidth ; x++)
					// lookup the correct character to print using the index
					cout << tileImage[ map[x][y] ];
		}
	}
}

void DrawEngine::gotoxy(int posx, int posy)
{
	HANDLE output_handle;
	COORD pos;
	pos.X = posx;
	pos.Y = posy;
	output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output_handle, pos);
}

void DrawEngine::cursorVisibility(bool visibility)
{
	HANDLE output_handle;
	CONSOLE_CURSOR_INFO cciInfo;
	cciInfo.bVisible = visibility;
	output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(output_handle, &cciInfo);
}
