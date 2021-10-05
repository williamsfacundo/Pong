#include "ball.h"

//Setters
Ball::Ball(Vector2 position, float radius, Color color) 
{
	SetX(position.x);
	SetY(position.y);
	SetRadius(radius);
	SetColor(color);	
	SetMoving(false);
	SetRandomVelocity(velocityMinX, velocityMaxX, velocityMinY, velocityMaxY);
	SetRandomDirection(GetRandomValue(minDirection, maxDirection));
	SetTextureBall(TexturesBall::one);
}
void Ball::SetX(float x) 
{
	position.x = x;
}
void Ball::SetY(float y) 
{
	position.y = y;
}
void Ball::SetVelocity(Vector2 velocity) 
{
	this->velocity = velocity;
}
void Ball::SetRadius(float radius) 
{
	this->radius = radius;
}
void Ball::SetColor(Color color) 
{
	this->color = color;
}
void Ball::SetMoving(bool moving)
{
	this->moving = moving;
}
void Ball::SetRandomVelocity(short minX, short maxX, short minY, short maxY)
{
	SetVelocity({ static_cast<float>(GetRandomValue(minX, maxX)),
		static_cast<float>(GetRandomValue(minY, maxY)) });
}
void Ball::SetRandomDirection(short aux)
{
	switch (aux)
	{
	case 1:
		SetVelocity({ GetVelocity().x * -1, GetVelocity().y });
		break;
	case 2:
		SetVelocity({ GetVelocity().x, GetVelocity().y * -1 });
		break;
	case 3:
		SetVelocity({ GetVelocity().x * -1, GetVelocity().y * -1 });
		break;
	case 4:
		SetVelocity({ GetVelocity().x, GetVelocity().y });
		break;
	}
}
void Ball::SetNewRandomVelocityWithSameOldSign()
{
	if (GetVelocity().x < 0 && GetVelocity().y < 0)
	{
		SetRandomVelocity(velocityMinX, velocityMaxX, velocityMinY, velocityMaxY);
		SetVelocity({ GetVelocity().x * -1, GetVelocity().y * -1 });
	}
	else if (GetVelocity().x < 0)
	{
		SetRandomVelocity(velocityMinX, velocityMaxX, velocityMinY, velocityMaxY);
		SetVelocity({ GetVelocity().x * -1, GetVelocity().y });
	}
	else if (GetVelocity().y < 0)
	{
		SetRandomVelocity(velocityMinX, velocityMaxX, velocityMinY, velocityMaxY);
		SetVelocity({ GetVelocity().x, GetVelocity().y * -1 });
	}
}
void Ball::Reset(int screenWidth, int screenHeight)
{
	SetX(static_cast<float>(screenWidth / 2));
	SetY(static_cast<float>(screenHeight / 2));
	SetRandomVelocity(velocityMinX, velocityMaxX, velocityMinY, velocityMaxY);
	SetRandomDirection(GetRandomValue(1, 4));
	SetMoving(false);
}
void Ball::SetTextureBall(TexturesBall textureBall) 
{
	this->textureBall = textureBall;
}

//Getters
Vector2 Ball::GetPosition()
{
	return position;
}
Vector2 Ball::GetVelocity() 
{
	return velocity;
}
float Ball::GetRadius() 
{
	return radius;
}
Color Ball::GetColor() 
{
	return color;
}
bool Ball::GetMoving() 
{
	return moving;
}
TexturesBall Ball::GetTextureBall() 
{
	return textureBall;
}

//Other Functions
void Ball::Draw() 
{
	DrawCircleV(position, radius, color);
}
void Ball::UpdatePosition(int screenWidth, int screenHeight)
{
	if (GetMoving()) 
	{
		SetX(position.x + ((velocity.x) * (screenWidth / 640) * GetFrameTime()));
		SetY(position.y + ((velocity.y) * (screenWidth / 640) * GetFrameTime()));
	}	
}
void Ball::StartMoving(int launchKey) 
{
	if (IsKeyPressed(launchKey)) 
	{
		if (GetMoving() != true) 
		{ 
			SetMoving(true); 
		}
	}
}
void Ball::Update(int screenWidth, int screenHeight, Pad* playerOne, Pad* playerTwo)
{
	BallOutsideLimits(screenWidth, screenHeight, playerOne, playerTwo);
	UpdatePosition(screenWidth, screenHeight);
}
void Ball::BallOutsideLimits(int screenWidth, int screenHeight, Pad* playerOne, Pad* playerTwo)
{
	if (GetPosition().x - GetRadius() < 0 || GetPosition().x + GetRadius() > screenWidth)
	{
		if (GetPosition().x - GetRadius() < 0)
		{
			playerTwo->ScoreUp();
		}
		else		
		{
			playerOne->ScoreUp();
		}

		Reset(screenWidth, screenHeight);	
		playerOne->ResetPosition(128.0f, 270.0f);
		playerTwo->ResetPosition(1024, 270);
	}

	//Arreglar bug pelota loop de cambio de signo de velocidad queda atrapado en los bordes
	if (GetPosition().y - GetRadius() < 0 || GetPosition().y + GetRadius() > screenHeight)
	{
		SetVelocity({ (GetVelocity().x), (GetVelocity().y) * -1 });
	}
}
void Ball::ChangeTexturePadRight() 
{
	switch (GetTextureBall())
	{
	case TexturesBall::one:

		SetTextureBall(TexturesBall::two);

		break;
	case TexturesBall::two:

		SetTextureBall(TexturesBall::three);

		break;
	case TexturesBall::three:

		SetTextureBall(TexturesBall::four);

		break;
	case TexturesBall::four:

		SetTextureBall(TexturesBall::five);

		break;
	case TexturesBall::five:

		SetTextureBall(TexturesBall::one);

		break;
	}
}
void Ball::ChangeTexturePadLeft() 
{
	switch (GetTextureBall())
	{
	case TexturesBall::one:

		SetTextureBall(TexturesBall::five);

		break;
	case TexturesBall::two:

		SetTextureBall(TexturesBall::one);

		break;
	case TexturesBall::three:

		SetTextureBall(TexturesBall::two);

		break;
	case TexturesBall::four:

		SetTextureBall(TexturesBall::three);

		break;
	case TexturesBall::five:

		SetTextureBall(TexturesBall::four);

		break;
	}
}