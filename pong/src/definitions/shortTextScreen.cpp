#include "shortTextScreen.h"

ShortTextScreen::ShortTextScreen(const char* messageText)
{
	this->messageText = messageText;
	messagePosition = {0,0};
	goBackButton = new Button({ 0,0,0,0 }, "MENU", WHITE);

	AdaptComponentsToScreen();
}
ShortTextScreen::~ShortTextScreen()
{
	if (goBackButton != NULL)
	{
		delete goBackButton;
		goBackButton = NULL;
	}
}
void ShortTextScreen::Input(SceneManager* sceneManager, Game* game, Music gameMusic, Music programMusic)
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

	if (goBackButton->ChangeSceneWhenMousePressedAndResetGame(sceneManager, scenes::menu)) { game->ResetGameValues(); }
}
void ShortTextScreen::Update(Music music)
{
	UpdateMusicStream(music);
	goBackButton->ChangeColorWhenMouseOnButton(recButtonColor, recTextColor, recButtonColorTwo, recTextColorTwo);
}
void ShortTextScreen::Draw(const char* winnerName, Game* game)
{
	BeginDrawing();	

	ClearBackground(RAYWHITE);

	game->DrawForEndGame();

	DrawText(messageText, static_cast<int>(messagePosition.x), static_cast<int>(messagePosition.y), 100, GREEN);
	goBackButton->DrawButton();

	DrawText("ESC(exit)", 5, 40, 25, DARKGRAY);

	EndDrawing();
}
void ShortTextScreen::AdaptComponentsToScreen()
{
	goBackButton->SetStructure(GetScreenWidth() / 2.0f - 150.0f, GetScreenHeight() / 2.0f + 150.0f, 300.0f, 150.0f);
	messagePosition = { static_cast<float>(GetScreenWidth() / 2.0f - 300), 150.0f};
}