#include "program.h"

Program::Program() 
{
    screenWidth = HDWidth;
    screenHeight = HDHeight;
    closeProgram = false;
    sceneManager = new SceneManager(scenes::menu); 
    game = NULL;
    mainMenu = NULL;
    pausedMenu = NULL;
    endGameScreen = NULL;
    credits = NULL;
    tutorial = NULL;
    endGameMessage = "GAME OVER";   

    InitWindow(screenWidth, screenHeight, "PONG by Williams Facundo");
    InitAudioDevice();

    programMusic = LoadMusicStream("assets/audio/music.mp3");
    programMusic.looping = true;    
    gameMusic = LoadMusicStream("assets/audio/game.mp3");
    gameMusic.looping = true;

    SetMusicVolume(programMusic, 0.2f);
    SetMusicVolume(gameMusic, 0.2f);

    SetTargetFPS(60);
}
Program::~Program() 
{
    if (sceneManager != NULL) 
    {
        delete sceneManager;
        sceneManager = NULL;
    }

    UnloadMusicStream(programMusic);
    UnloadMusicStream(gameMusic);

    CloseAudioDevice();
    CloseWindow();
}
void Program::Init() 
{
    game = new Game(screenWidth, screenHeight);
    mainMenu = new Menu("PLAY", "CREDITS", "TUTORIAL", "EXIT");
    pausedMenu = new Menu("RESUME","RESET","MAIN MENU","EXIT");
    endGameScreen = new ShortTextScreen(endGameMessage);
    credits = new Credits();
    tutorial = new Tutorial(); 

    PlayMusicStream(programMusic);
    PlayMusicStream(gameMusic);
}
void Program::DeInit() 
{
    if (game != NULL) 
    {
        delete game;
        game = NULL;
    }
    if (mainMenu != NULL) 
    {
        delete mainMenu;
        mainMenu = NULL;
    }
    if (pausedMenu != NULL) 
    {
        delete pausedMenu;
        pausedMenu = NULL;
    }
    if (endGameScreen != NULL) 
    {
        delete endGameScreen;
        endGameScreen = NULL;
    }
    if (credits != NULL) 
    {
        delete credits;
        credits = NULL;
    }
    if (tutorial != NULL)
    {
        delete tutorial;
        tutorial = NULL;
    }
}
void Program::Play() 
{
    Init();    

    while (!WindowShouldClose() && !closeProgram)
    {
        switch (sceneManager->GetActualScene())
        {
        case scenes::game:
            game->Input(sceneManager, gameMusic, programMusic);
            game->Update(screenWidth, screenHeight, sceneManager, gameMusic);
            game->Draw(screenWidth, screenHeight);
            break;
        case scenes::menu:
            mainMenu->MainMenuInput(sceneManager, scenes::game, scenes::credits, scenes::tutorial, scenes::exit, gameMusic, programMusic);
            mainMenu->Update(programMusic);
            mainMenu->Draw(true, RED);
            break;
        case scenes::tutorial:
            tutorial->Input(sceneManager, gameMusic, programMusic);
            tutorial->Update(programMusic);
            tutorial->Draw();
            break;
        case scenes::paused:
            pausedMenu->PauseMenuInput(sceneManager, scenes::game, scenes::game, scenes::menu, scenes::exit, game, gameMusic, programMusic);
            pausedMenu->Update(programMusic);
            pausedMenu->Draw(false, BLACK);
            break;
        case scenes::credits:
            credits->Input(sceneManager, gameMusic, programMusic);
            credits->Update(programMusic);
            credits->Draw();
            break;
        case scenes::exit:
            SetCloseProgram(true);
            break;
        case scenes::endGame:
            endGameScreen->Input(sceneManager, game, gameMusic, programMusic);
            endGameScreen->Update(gameMusic);            
            endGameScreen->Draw(endGameMessage, game);
            break;
        default:
            break;
        }        
    }

    DeInit();
}
void Program::SetCloseProgram(bool closeProgram)
{
    this->closeProgram = closeProgram;
}