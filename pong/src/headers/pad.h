#ifndef PAD_H
#define PAD_H

#include <raylib.h>
#include "vars.h"

class Pad 
{
private:
	Rectangle structure = {0,0,0,0};
	Rectangle topRec;
	Rectangle downRec;
	Rectangle rightRec;
	Rectangle leftRec;

	Color color = WHITE;

	Movement movementStatus = Movement::none;

	float moveSpeed = 450.5f;

	bool isCollidingBall;	

	int score[2];

	TexturesPad texturePad;
public:
	//Setters
	Pad(Rectangle rec, Color color);	
	void SetPadX(float value);
	void SetPadY(float value);
	void SetPadWidth(float value);
	void SetPadHeight(float value);
	void SetPadColor(Color color);
	void SetIsCollidingBall(bool isCollidingBall);	
	void SetTopRec(Rectangle rec);
	void SetDownRec(Rectangle rec);
	void SetRightRec(Rectangle rec);
	void SetLeftRec(Rectangle rec);
	void ScoreUp();
	void ResetScore();
	void ResetPosition(float x, float y);
	void SetTexturePad(TexturesPad texturePad);	
	
	//Getters
	Rectangle GetStructure();
	Color GetPadColor();
	bool GetIsCollidingBall();
	Rectangle GetTopRec();
	Rectangle GetDownRec();
	Rectangle GetRightRec();
	Rectangle GetLeftRec();	
	Movement GetMovementStatus();
	TexturesPad GetTexturePad();

	//Other Functions
	void Draw();
	void DetectInput(int keyUp, int keyDown);
	void MovePlayer(int screenHeight);			
	void ShowScore(Vector2 positionLeftScore, Vector2 positionRightScore);
	bool playerWin(int scoreToWin[2]);
	void ChangeTexturePadRight();
	void ChangeTexturePadLeft();
};

#endif

