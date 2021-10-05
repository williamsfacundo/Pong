#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include "game.h"

class Menu 
{
private:
	Button* buttonOne; //Resume
	Button* buttonTwo; //Reset
	Button* buttonThree; //Menu
	Button* buttonFour; //Exit
	Texture2D backgroundOne;
	Texture2D backgroundTwo;	
public:
	Menu(const char* buttonOneText, const char* buttonTwoText, const char* buttonThreeText, const char* buttonFourText);
	~Menu();
	void MainMenuInput(SceneManager* sceneManager, scenes buttonOneScene, scenes buttonTwoScene, scenes buttonThreeScene, scenes buttonFourScene, Music gameMusic, Music programMusic);
	void PauseMenuInput(SceneManager* sceneManager, scenes buttonOneScene, scenes buttonTwoScene, scenes buttonThreeScene, scenes buttonFourScene, Game* game, Music gameMusic, Music programMusic);
	void Update(Music music);
	void Draw(bool showBackgroundOne, Color buttonTextColor);
	void AdaptButtonsToScreen();
	void StopMusic(Music gameMusic, Music programMusic);
};

#endif // !MENU_H

