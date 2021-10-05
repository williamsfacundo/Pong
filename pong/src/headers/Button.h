#ifndef  BUTTON_H
#define BUTTON_H

#include "sceneManager.h"

class Button 
{
private:
	Rectangle structure;
	Color recColor;
	Color textColor;
	const char* text;	
public:
	Button(Rectangle structure, const char* text, Color recColor);  
	Button(Rectangle structure);

	void SetStructure(Rectangle structure);
	void SetStructure(float x, float y, float width, float height);
	void SetStructureX(float x);
	void SetStructureY(float y);
	void SetStructureWidth(float width);
	void SetStructureHeight(float height);
	void SetRecColor(Color recColor);
	void SetTextColor(Color textColor);
	void SetText(const char* text);

	Rectangle GetStructure();
	Color GetRecColor();
	Color GetTextColor();
	const char* GetText();	

	bool IsMouseOnButton();
	bool ButtonPressed();
	void ChangeColorWhenMouseOnButton(Color recButtonColor, Color recTextColor, Color recButtonColorTwo, Color recTextColorTwo);
	void ChangeSceneWhenMousePressed(SceneManager* sceneManager, scenes newScene);
	bool ChangeSceneWhenMousePressedAndResetGame(SceneManager* sceneManager, scenes newScene);
	void DrawButton();
	void DrawButton(Color textColor);
};

#endif // ! BUTTON_H

