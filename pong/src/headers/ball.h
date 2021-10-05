#pragma once
#ifndef BALL_H
#define BALL_H

#include "pad.h"

class Ball 
{
private:
	Vector2 position;
	Vector2 velocity;

	Color color;

	float radius;
	
	bool moving;

	TexturesBall textureBall;
public:
	//Setters
	Ball(Vector2 position, float radius, Color color);
	void SetX(float x);
	void SetY(float y);
	void SetVelocity(Vector2 velocity);
	void SetRadius(float radius);
	void SetColor(Color color);	
	void SetMoving(bool moving);
	void SetRandomVelocity(short minX, short maxX, short minY, short maxY);
	void SetRandomDirection(short aux);	
	void SetNewRandomVelocityWithSameOldSign();
	void Reset(int screenWidth, int screenHeight);
	void SetTextureBall(TexturesBall textureBall);	

	//Getters
	Vector2 GetPosition();
	Vector2 GetVelocity();
	float GetRadius();
	Color GetColor();	
	bool GetMoving();
	TexturesBall GetTextureBall();

	//Other Functions
	void Draw();		
	void UpdatePosition(int screenWidth, int screenHeight);
	void StartMoving(int launchKey);	
	void Update(int screenWidth, int screenHeight, Pad* playerOne, Pad* playerTwo);
	void BallOutsideLimits(int screenWidth, int screenHeight, Pad* playerOne, Pad* playerTwo);
	void ChangeTexturePadRight();
	void ChangeTexturePadLeft();
};

#endif
