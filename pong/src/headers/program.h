#ifndef PROGRAM_H
#define PROGRAM_H

#include "tutorial.h"
#include "credits.h"
#include "shortTextScreen.h"
#include "game.h"
#include "menu.h"

class Program
{
private:
	int screenWidth;
	int screenHeight;
	bool closeProgram;
	SceneManager* sceneManager;	
	Game* game;
	Menu* mainMenu;
	Menu* pausedMenu;
	ShortTextScreen* endGameScreen; 
	Credits* credits;
	Tutorial* tutorial;
	const char* endGameMessage;
	Music programMusic;
	Music gameMusic;
public:
	Program();
	~Program();
	void Init();	
	void DeInit();
	void Play();
	void SetCloseProgram(bool closeProgram);
};

#endif // !PROGRAM_H

