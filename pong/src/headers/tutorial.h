#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Button.h"

class Tutorial 
{
private:
	Button* goBackButton;
	Texture2D background;
public:
	Tutorial();
	~Tutorial();
	void Input(SceneManager* sceneManager, Music gameMusic, Music programMusic);
	void Update(Music music);
	void Draw();
};

#endif
