#include "pad.h"

//Setters
Pad::Pad(Rectangle rec, Color color) 
{
	structure = rec;
	SetPadColor(color);
	SetIsCollidingBall(false);
	topRec = {0,0,0,0};
	downRec = { 0,0,0,0 };
	rightRec = { 0,0,0,0 };
	leftRec = { 0,0,0,0 };
	ResetScore();
	SetTexturePad(TexturesPad::one);
}
void Pad::SetPadX(float value) 
{
	structure.x = value;
}
void Pad::SetPadY(float value)
{
	structure.y = value;
}
void Pad::SetPadWidth(float value)
{
	structure.width = value;
}
void Pad::SetPadHeight(float value)
{
	structure.height = value;
}
void Pad::SetPadColor(Color color)
{
	this->color = color;
}
void Pad::SetIsCollidingBall(bool isCollidingBall)
{
	this->isCollidingBall = isCollidingBall;
}
void Pad::SetTopRec(Rectangle rec)
{
	topRec = rec;
}
void Pad::SetDownRec(Rectangle rec)
{
	downRec = rec;
}
void Pad::SetRightRec(Rectangle rec)
{
	rightRec = rec;
}
void Pad::SetLeftRec(Rectangle rec)
{
	leftRec = rec;
}
void Pad::ScoreUp()
{
	score[1] += 1;

	if (score[1] > nine) 
	{
		if (score[0] < nine)
		{
			score[1] = zero;
			score[0] += 1;
		}
		else 
		{
			ResetScore();
		}		
	}	
}
void Pad::ResetScore()
{
	score[0] = zero;
	score[1] = zero;
}
void Pad::ResetPosition(float x, float y)
{
	SetPadX(x);
	SetPadY(y);
}
void Pad::SetTexturePad(TexturesPad texturePad)
{
	this->texturePad = texturePad;
}

//Getters
Rectangle Pad::GetStructure() 
{
	return structure;
}
Color Pad::GetPadColor() 
{
	return color;
}
bool Pad::GetIsCollidingBall()
{
	return isCollidingBall;
}
Rectangle Pad::GetTopRec() 
{
	return topRec;
}
Rectangle Pad::GetDownRec()
{
	return downRec;
}
Rectangle Pad::GetRightRec()
{
	return rightRec;
}
Rectangle Pad::GetLeftRec()
{
	return leftRec;
}
Movement Pad::GetMovementStatus() 
{
	return movementStatus;
}
TexturesPad Pad::GetTexturePad() 
{
	return texturePad;
}

//Other Functions
void Pad::Draw()
{
	DrawRectangleRec(structure, color);
}
void Pad::DetectInput(int keyUp, int keyDown)
{
	if (IsKeyDown(keyUp)) 
	{
		movementStatus = Movement::up;
	}
	else if (IsKeyDown(keyDown)) 
	{
		movementStatus = Movement::down;
	}
	else
	{
		movementStatus = Movement::none;
	}
}
void Pad::MovePlayer(int screenHeight) 
{
	switch (movementStatus)
	{
	case Movement::up:
				
		if (structure.y > 0) 
		{
			structure.y -= moveSpeed * GetFrameTime();
		}
		
		break;
	case Movement::down:

		if ((structure.y + structure.height) < screenHeight)
		{
			structure.y += moveSpeed * GetFrameTime();
		}
		
		break;
	case Movement::none:

		structure.y += 0;
		break;
	default:

		structure.y += 0;
		break;
	}
}
void Pad::ShowScore(Vector2 positionLeftScore, Vector2 positionRightScore)
{
	DrawTextCodepoint(GetFontDefault(), score[0], positionLeftScore, 60, ORANGE);
	DrawTextCodepoint(GetFontDefault(), score[1], positionRightScore, 60, ORANGE);	
}
bool Pad::playerWin(int scoreToWin[2])
{
	if (score[0] >= scoreToWin[0] && score[1] >= scoreToWin[1])
	{
		return true;
	}
	else 
	{
		return false;
	}
}
void Pad::ChangeTexturePadRight()
{
	switch (GetTexturePad())
	{
	case TexturesPad::one:

		SetTexturePad(TexturesPad::two);

		break;
	case TexturesPad::two:

		SetTexturePad(TexturesPad::three);

		break;
	case TexturesPad::three:

		SetTexturePad(TexturesPad::four);

		break;
	case TexturesPad::four:

		SetTexturePad(TexturesPad::five);

		break;
	case TexturesPad::five:

		SetTexturePad(TexturesPad::one);

		break;
	}
}
void Pad::ChangeTexturePadLeft() 
{
	switch (GetTexturePad())
	{
	case TexturesPad::one:

		SetTexturePad(TexturesPad::five);

		break;
	case TexturesPad::two:

		SetTexturePad(TexturesPad::one);

		break;
	case TexturesPad::three:

		SetTexturePad(TexturesPad::two);

		break;
	case TexturesPad::four:

		SetTexturePad(TexturesPad::three);

		break;
	case TexturesPad::five:

		SetTexturePad(TexturesPad::four);

		break;
	}
}