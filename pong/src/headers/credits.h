#ifndef CREDITS_H
#define CREDITS_H

#include "Button.h"

class Credits 
{
private:
	Button* goBackButton;
	Texture2D background;
public:
	Credits();
	~Credits();
	void Input(SceneManager* sceneManager, Music gameMusic, Music programMusic);
	void Update(Music music);
	void Draw();
};

#endif
