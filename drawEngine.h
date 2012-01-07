#ifndef DRAWENGINE_H
#define DRAWENGINE_H

class DrawEngine
{

public:
	DrawEngine(int xSize = 30, int ySize = 20);
	~DrawEngine();

	int createSprite(int index, char c);
	void deleteSprite(int index);

	void drawSprite(int index, int posx, int posy);
	void eraseSprite(int posx, int posy);

	void setMap(char **);
	void createBackgroundTile(int index, char c);
	void drawBackground(void);

protected:
	char **map;
	int screenWidth, screenHeight;
	// static space to hold 16 unique sprites
	char spriteImage[16];
	char tileImage[16];

private:
	void gotoxy(int posx, int posy);
	void cursorVisibility(bool visibility);
};

#endif
