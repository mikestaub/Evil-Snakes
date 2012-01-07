#ifndef GAME_H
#define GAME_H

#include "drawEngine.h"
#include "level.h"
#include "character.h"
#include "mage.h"
#include "windows.h"

class Game
{

public:
	bool run(void);

private:
	Level *level;

	double frameCount;
	double startTime;
	double lastTime;

	DrawEngine drawArea;

protected:
	Mage *player;

	bool getInput(char* key);
	void timerUpdate(void);
};

#endif
