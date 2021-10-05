#include "tutorial.h"

Tutorial::Tutorial() 
{
	goBackButton = new Button({ 490.0f, 600.0f, 300.0f, 120.0f }, "MENU", WHITE);
	background = LoadTexture("assets/Images/background_four.png");
}
Tutorial::~Tutorial() 
{
	if (goBackButton != NULL)
	{
		delete goBackButton;
	}

	UnloadTexture(background);
}
void Tutorial::Input(SceneManager* sceneManager, Music gameMusic, Music programMusic)
{
	if (IsKeyPressed(stopMusicKey))
	{
		if (IsMusicPlaying(gameMusic))
		{
			PauseMusicStream(gameMusic);
			PauseMusicStream(programMusic);
		}
		else
		{
			ResumeMusicStream(gameMusic);
			ResumeMusicStream(programMusic);
		}
	}

	goBackButton->ChangeSceneWhenMousePressed(sceneManager, scenes::menu);
}
void Tutorial::Update(Music music)
{
	UpdateMusicStream(music);
	goBackButton->ChangeColorWhenMouseOnButton(recButtonColor, recTextColor, recButtonColorTwo, recTextColorTwo);
}
void Tutorial::Draw() 
{
	BeginDrawing();

	ClearBackground(RAYWHITE);
	
	DrawTexture(background, 1, 1, WHITE);

	DrawText("There are two pads in the game and one ball.", 140, 50, 30, ORANGE);
	DrawText("Objective: the ball must pass the other player pad.", 140, 110, 30, ORANGE);
	DrawText("In order to win you must reach the neccesary points to win,", 140, 170, 30, ORANGE);
	DrawText("or have more points than your rival when the time is out.", 140, 230, 30, ORANGE);
	DrawText("At the start of the match, before pressing space you can ", 140, 320, 30, ORANGE);
	DrawText("use the black arrows to config some game parameters such as:", 140, 380, 30, ORANGE);
	DrawText("the pads and the ball textures, the timer of the match in (VIOLET)", 140, 440, 30, ORANGE);
	DrawText("and the score needed to win in (ORANGE)", 140, 500, 30, ORANGE);
	DrawText("Finally, press (SPACE) to launch ball", 140, 560, 30, ORANGE);
	DrawText("STOP/RESUME music (M)", 850, 680, 30, ORANGE);
	
	goBackButton->DrawButton();

	DrawText("ESC(exit)", 5, 40, 25, DARKGRAY);

	EndDrawing();
}