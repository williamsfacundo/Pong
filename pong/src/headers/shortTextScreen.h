#ifndef SHORTTEXTSCREEN_H
#define SHORTTEXTSCREEN_H

#include "game.h"
#include "Button.h"

class ShortTextScreen
{
private:
	const char* messageText;
	Vector2 messagePosition;
	Button* goBackButton;
public:
	ShortTextScreen(const char* messageText);
	~ShortTextScreen();
	void Input(SceneManager* sceneManager, Game* game, Music gameMusic, Music programMusic);
	void Update(Music music);
	void Draw(const char* winnerName, Game* game);
	void AdaptComponentsToScreen();
};

#endif