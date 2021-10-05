#include "Button.h"

Button::Button(Rectangle structure, const char* text, Color recColor) //
{
	SetStructure(structure);
	SetText(text);
	SetRecColor(recColor);
}
Button::Button(Rectangle structure) 
{
	SetStructure(structure);
	SetText(" ");
	SetRecColor(WHITE);
}
void Button::SetStructure(Rectangle structure) 
{
	this->structure = structure;
}
void Button::SetStructure(float x, float y, float width, float height) 
{
	SetStructureX(x);
	SetStructureY(y);
	SetStructureWidth(width);
	SetStructureHeight(height);
}
void Button::SetStructureX(float x) 
{
	structure.x = x;
}
void Button::SetStructureY(float y) 
{
	structure.y = y;
}
void Button::SetStructureWidth(float width) 
{
	structure.width = width;
}
void Button::SetStructureHeight(float height) 
{
	structure.height = height;
}
void Button::SetRecColor(Color recColor)
{
	this->recColor = recColor;
}
void Button::SetTextColor(Color textColor) 
{
	this->textColor = textColor;
}
void Button::SetText(const char* text) 
{
	this->text = text;
}
Rectangle Button::GetStructure() 
{
	return structure;
}
Color Button::GetRecColor()
{
	return recColor;
}
Color Button::GetTextColor() 
{
	return textColor;
}
const char* Button::GetText()
{
	return text;
}
bool Button::IsMouseOnButton() 
{
	return (GetMouseX() > GetStructure().x && GetMouseX() < GetStructure().x + GetStructure().width
		&& GetMouseY() > GetStructure().y && GetMouseY() < GetStructure().y + GetStructure().height);	
}
bool Button::ButtonPressed() 
{
	return (IsMouseOnButton() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}
void Button::ChangeColorWhenMouseOnButton(Color recButtonColor, Color recTextColor, Color recButtonColorTwo, Color recTextColorTwo)
{
	if (IsMouseOnButton()) 
	{
		SetRecColor(recButtonColor);
		SetTextColor(recTextColor);
	}
	else 
	{	
		SetRecColor(recButtonColorTwo);
		SetTextColor(recTextColorTwo);
	}
}
void Button::ChangeSceneWhenMousePressed(SceneManager* sceneManager, scenes newScene) 
{
	if (ButtonPressed()) 
	{
		sceneManager->SetActualScene(newScene);
	}
}
bool Button::ChangeSceneWhenMousePressedAndResetGame(SceneManager* sceneManager, scenes newScene)
{
	bool resetGame = false;

	if(ButtonPressed())
	{
		sceneManager->SetActualScene(newScene);		
		resetGame = true;
	}

	return resetGame;
}
void Button::DrawButton() 
{	
	DrawRectangleLinesEx(GetStructure(), 5, GetRecColor());
	DrawText(GetText(), (static_cast<int>(GetStructure().x + ((GetStructure().width) / 5) * 2)), static_cast<int>(GetStructure().y + ((GetStructure().height / 5) * 2)), 30, GetTextColor());
}
void Button::DrawButton(Color textColor)
{
	DrawRectangleLinesEx(GetStructure(), 5, GetRecColor());
	DrawText(GetText(), (static_cast<int>(GetStructure().x + ((GetStructure().width) / 5) * 2)), static_cast<int>(GetStructure().y + ((GetStructure().height / 5) * 2)), 30, textColor);
}
