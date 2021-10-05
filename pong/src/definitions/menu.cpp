#include "menu.h"

Menu::Menu(const char* buttonOneText, const char* buttonTwoText, const char* buttonThreeText, const char* buttonFourText)
{     
    buttonOne = new Button({ 0,0,0,0, }, buttonOneText, BLACK);
    buttonTwo = new Button({ 0,0,0,0, }, buttonTwoText, BLACK);
    buttonThree = new Button({ 0,0,0,0, }, buttonThreeText, BLACK);
    buttonFour = new Button({ 0,0,0,0, }, buttonFourText, BLACK);

    backgroundOne = LoadTexture("assets/Images/background_two.png");
    backgroundOne.width = GetScreenWidth();
    backgroundOne.height = GetScreenHeight();
    backgroundTwo = LoadTexture("assets/Images/background_three.png");
    backgroundTwo.width = GetScreenWidth();
    backgroundTwo.height = GetScreenHeight();    

    AdaptButtonsToScreen();
}
Menu::~Menu() 
{
    if (buttonOne != NULL) 
    {
        delete buttonOne;
        buttonOne = NULL;
    }
    if (buttonTwo != NULL)
    {
        delete buttonTwo;
        buttonTwo = NULL;
    }
    if (buttonThree != NULL)
    {
        delete buttonThree;
        buttonThree = NULL;
    }
    if (buttonFour != NULL)
    {
        delete buttonFour;
        buttonFour = NULL;
    }

    UnloadTexture(backgroundOne);
    UnloadTexture(backgroundTwo);
}
void Menu::MainMenuInput(SceneManager* sceneManager, scenes buttonOneScene, scenes buttonTwoScene, scenes buttonThreeScene, scenes buttonFourScene, Music gameMusic, Music programMusic)
{
    StopMusic(gameMusic, programMusic);

    buttonOne->ChangeSceneWhenMousePressed(sceneManager, buttonOneScene);
    buttonTwo->ChangeSceneWhenMousePressed(sceneManager, buttonTwoScene);
    buttonThree->ChangeSceneWhenMousePressed(sceneManager, buttonThreeScene);
    buttonFour->ChangeSceneWhenMousePressed(sceneManager, buttonFourScene);
}
void Menu::PauseMenuInput(SceneManager* sceneManager, scenes buttonOneScene, scenes buttonTwoScene, scenes buttonThreeScene, scenes buttonFourScene, Game* game, Music gameMusic, Music programMusic)
{
    StopMusic(gameMusic, programMusic);

    buttonOne->ChangeSceneWhenMousePressed(sceneManager, buttonOneScene);
    if (buttonTwo->ChangeSceneWhenMousePressedAndResetGame(sceneManager, buttonTwoScene)) { game->ResetGameValues(); }
    if (buttonThree->ChangeSceneWhenMousePressedAndResetGame(sceneManager, buttonThreeScene)) { game->ResetGameValues(); }
    buttonFour->ChangeSceneWhenMousePressed(sceneManager, buttonFourScene);
}
void Menu::Update(Music music) 
{
    UpdateMusicStream(music);

    buttonOne->ChangeColorWhenMouseOnButton(recButtonColor, recTextColor, recButtonColorTwo, recTextColorTwo);
    buttonTwo->ChangeColorWhenMouseOnButton(recButtonColor, recTextColor, recButtonColorTwo, recTextColorTwo);
    buttonThree->ChangeColorWhenMouseOnButton(recButtonColor, recTextColor, recButtonColorTwo, recTextColorTwo);
    buttonFour->ChangeColorWhenMouseOnButton(recButtonColor, recTextColor, recButtonColorTwo, recTextColorTwo);
}
void Menu::Draw(bool showBackgroundOne, Color buttonTextColor)
{
    BeginDrawing();
    
    ClearBackground(RAYWHITE);

    if (showBackgroundOne) 
    {
        DrawTexture(backgroundOne, 1, 1, WHITE);
    }
    else 
    {
        DrawTexture(backgroundTwo, 1, 1, WHITE);
    }   

    buttonOne->DrawButton(buttonTextColor);
    buttonTwo->DrawButton(buttonTextColor);
    buttonThree->DrawButton(buttonTextColor);
    buttonFour->DrawButton(buttonTextColor);
    
    DrawText("ESC(exit)", 5, 40, 25, DARKGRAY);
    DrawText("STOP/RESUME music (M)", 850, 680, 30, ORANGE);

    EndDrawing();
}
void Menu::AdaptButtonsToScreen() 
{
    buttonOne->SetStructure(static_cast<float>((GetScreenWidth() / 6) * 1.5), static_cast<float>((GetScreenHeight() / 7) * 1), static_cast<float>(((GetScreenWidth() / 8) * 4)), static_cast<float>(((GetScreenHeight() / 10) * 1)));
    buttonTwo->SetStructure(static_cast<float>((GetScreenWidth() / 6) * 1.5), static_cast<float>((GetScreenHeight() / 7) * 2), static_cast<float>(((GetScreenWidth() / 8) * 4)), static_cast<float>(((GetScreenHeight() / 10) * 1)));
    buttonThree->SetStructure(static_cast<float>((GetScreenWidth() / 6) * 1.5), static_cast<float>((GetScreenHeight() / 7) * 3), static_cast<float>(((GetScreenWidth() / 8) * 4)), static_cast<float>(((GetScreenHeight() / 10) * 1)));
    buttonFour->SetStructure(static_cast<float>((GetScreenWidth() / 6) * 1.5), static_cast<float>((GetScreenHeight() / 7) * 4), static_cast<float>(((GetScreenWidth() / 8) * 4)), static_cast<float>(((GetScreenHeight() / 10) * 1)));
}
void Menu::StopMusic(Music gameMusic, Music programMusic)
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
}