#include "sceneManager.h"

SceneManager::SceneManager(scenes firstScene) 
{
	SetActualScene(firstScene);
}
void SceneManager::SetActualScene(scenes newScene) 
{
	actualScene = newScene;
}
scenes SceneManager::GetActualScene() 
{
	return actualScene;
}