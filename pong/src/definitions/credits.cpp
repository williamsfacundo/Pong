#include "credits.h"

Credits::Credits() 
{
	goBackButton = new Button({ 490.0f, 580.0f, 300.0f, 120.0f }, "MENU", WHITE);
	background = LoadTexture("assets/Images/background_one.png");
	background.width = GetScreenWidth();
	background.height = GetScreenHeight();
}
Credits::~Credits()
{
	if (goBackButton != NULL) 
	{
		delete goBackButton;
	}

	UnloadTexture(background);
}
void Credits::Input(SceneManager* sceneManager, Music gameMusic, Music programMusic)
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
void Credits::Update(Music music)
{
	UpdateMusicStream(music);
	goBackButton->ChangeColorWhenMouseOnButton(recButtonColor, recTextColor, recButtonColorTwo, recTextColorTwo);
}
void Credits::Draw()

{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawTexture(background, 1, 1, RAYWHITE);

	DrawRectangle(100, 120, 1100, 50, ORANGE);
	DrawText("GAME DEVELOPED BY WILLIAMS FACUNDO", 100, 120, 50, GREEN);

	DrawRectangle(0, 230, GetScreenWidth(), 320, RED);
	DrawTextEx(GetFontDefault(), "Game Background:  https://saurabhkgp.itch.io/the-dawn-parallax-background", { 40.0f, 250.0f }, 26.0f, 1.0f, BLACK);
	DrawTextEx(GetFontDefault(), "Ball And Pad Textures:  https://opengameart.org/content/27-planets-in-hi-res", { 40.0f, 300.0f }, 26.0f, 1.0f, BLACK);
	DrawTextEx(GetFontDefault(), "Else Background images:  https://wallpaperscraft.com/download/river_grass_trees_153970/1280x720", { 40.0f, 350.0f }, 26.0f, 1.0f, BLACK);
	DrawTextEx(GetFontDefault(), "        https://wallpaperscraft.com/download/city_art_retrowave_143233/1280x720", { 40.0f, 400.0f }, 26.0f, 1.0f, BLACK);
	DrawTextEx(GetFontDefault(), "        https://wallpaperscraft.com/download/palms_vector_art_118164/1280x720", { 40.0f, 450.0f }, 26.0f, 1.0f, BLACK);
	DrawTextEx(GetFontDefault(), "        https://wallpaperscraft.com/download/drawing_surreal_colorful_psychedelic_62135/1280x720", { 40.0f, 500.0f }, 26.0f, 1.0f, BLACK);

	goBackButton->DrawButton(ORANGE);

	DrawText("ESC(exit)", 5, 40, 25, GREEN);

	EndDrawing();
}