#include <stdlib.h>
#include <math.h>
#include "enemy.h"
#include "level.h"
#include "character.h"

Enemy::Enemy(Level *l, DrawEngine *de, int s_index, float x, float y, int i_lives)
	: Sprite(l, de, s_index, x, y, i_lives)
{
		goal = 0;
		classID = ENEMY_CLASSID;
}

bool Enemy::move(float x, float y)
{
	int xpos = (int)(pos.x + x);
	int ypos = (int)(pos.y + y);

	if(isValidLevelMove(xpos, ypos))
	{
		// make sure we don't hit other enemies
		list <Sprite *>::iterator Iter;
		list <Sprite *>::iterator Iter2;

		for(Iter = level->npc.begin(); Iter != level->npc.end(); Iter++)
		{
			if((*Iter) != this && (int)(*Iter)->getX() == xpos
				&& (int)(*Iter)->getY() == ypos)
			{
				if(((*Iter)->classID == FIREBALL_CLASSID))
				{
					this->addLives(-1);
					(*Iter)->addLives(-1);
					return true;
				}
				return false;
			}
		}

		erase(pos.x, pos.y);

		pos.x += x;
		pos.y += y;

		facingDirection.x = x;
		facingDirection.y = y;

		draw(pos.x, pos.y);

		if ((int)goal->getX() == xpos && (int)goal->getY() == ypos)
			goal->addLives(-1);

		return true;
	}
	return false;
}

void Enemy::idleUpdate(void)
{
	if(!(this->isAlive()))
	{
		delete this;
		return;
	}
	if(goal)
		simulateAI();
}

void Enemy::addGoal(Character *g)
{
	goal = g;
}

void Enemy::simulateAI(void)
{
	// get the position of the character
	vector goal_pos = goal->getPosition();
	vector direction;

	direction.x = goal_pos.x - pos.x;
	direction.y = goal_pos.y - pos.y;

	// use pathagorean theorum to find the magnitude of the vector
	float mag = sqrt(direction.x * direction.x + direction.y * direction.y);

	// divide by magnitude to get unit vector
	// you might need to multiply the magnitude by some int first, depending on how fast your processor is...
	direction.x = direction.x / (mag * 10);
	direction.y = direction.y / (mag * 10);
	 
	if(!move(direction.x, direction.y))
	{
		// try to go in all four possible directions ( brute force ) using expression rand() % 3 - 1
		// to create a value between -1 and 1
		while (!move( float(rand() % 3 - 1), float(rand() % 3 - 1)))
		{
			// do nothing
		}
	}
}
