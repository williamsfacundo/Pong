#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "vars.h"

class SceneManager 
{
private:
	scenes actualScene;
public:
	SceneManager(scenes firstScene);
	void SetActualScene(scenes newScene);
	scenes GetActualScene();
};

#endif