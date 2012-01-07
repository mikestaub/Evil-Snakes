#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "game.h"
#pragma comment(lib, "winmm.lib")

//We can use this macro to limit the frames per second of the game
// EASY=60 MEDIUM=30 HARD=15
#define GAME_SPEED 50

bool Game::run(void)    //This is the game loop-the heart of the program.
{
	level = new Level(&drawArea, 30, 20);

	drawArea.createBackgroundTile(TILE_EMPTY, ' ');
	drawArea.createBackgroundTile(TILE_WALL, 219);

	drawArea.createSprite(SPRITE_PLAYER, 1);
	drawArea.createSprite(SPRITE_ENEMY, '$');
	drawArea.createSprite(SPRITE_FIREBALL, '*');

	player = new Mage(level, &drawArea, 0);

	level->draw();

	level->addPlayer(player);
	level->addEnemies(3);

	char key = ' ';
	startTime = timeGetTime();
	lastTime = 0;
	frameCount = 0;

	while(key != 'q')
	{
		while (!getInput( &key))
		{
			timerUpdate();
		}

		level->keyPress(key);
	}

	delete player;
	return true;
}

bool Game::getInput(char* c) //This function checks whether the keyboard is pressed, and stores the value of the key if it is
{
	if(kbhit()) // need function to detect keyboard kit
	{
		*c = getch();
		return true;
	}

	return false;
}

void Game::timerUpdate() //This function controls the FPS of the game by comparing the current elapsed time to the set GAME_SPEED
{
	double currentTime =  timeGetTime() - lastTime;

	if(currentTime < GAME_SPEED)
		return;

	level->update();
	frameCount++;                 //If enough time has elapsed, then update the frame
	lastTime = timeGetTime();
}
