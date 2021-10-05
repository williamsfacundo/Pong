#include "game.h"

//Setters
Game::Game(int screenWidth, int screenHeight)
{    
    Init();
}
Game::~Game() 
{
    DeInit();
}
void Game::SetScoreToWin(short scoreLeft, short scoreRight) 
{
    scoreToWin[0] = scoreLeft;
    scoreToWin[1] = scoreRight;
}
void Game::SetPauseGameKey(int pausedGameKey) 
{
    this->pauseGameKey = pausedGameKey;
}
void Game::SetDTimer(double timer) 
{
    this->dTimer = timer;
}
void Game::SetATimer(short scoreLeft, short scoreMedium, short scoreRight) 
{
    aTimer[0] = scoreLeft;
    aTimer[1] = scoreMedium;
    aTimer[2] = scoreRight;
}

//Getter
int* Game::GetScoreToWin() 
{
    return scoreToWin;
}
int Game::GetPauseGameKey() 
{
    return pauseGameKey;
}
double Game::GetDTimer() 
{
    return dTimer;
}

//Game Flow
void Game::Init()
{   
    SetScoreToWin(initScoreToWin[0], initScoreToWin[1]);   
    SetDTimer(initDTimer);
    SetATimer(initATimer[0], initATimer[1], initATimer[2]);
    SetPauseGameKey(KEY_P);

    playerOne = new Pad({ 128,270,44,180 }, WHITE);
    playerTwo = new Pad({ 1024,270,44,180 }, WHITE);    
    ball = new Ball( { 640, 360}, 40, WHITE); 
    arrowsWorking = true;

    leftPadLeftArrowButton = new Button({playerOne->GetStructure().x - 60, playerOne->GetStructure().y + (playerOne->GetStructure().height / 2) - 25, arrowButtonsWidth, arrowButtonsHeight});
    leftPadRightArrowButton = new Button({ playerOne->GetStructure().x + playerOne->GetStructure().width, playerOne->GetStructure().y + (playerOne->GetStructure().height / 2) - 25, arrowButtonsWidth, arrowButtonsHeight });
    
    rightPadLeftArrowButton = new Button({ playerTwo->GetStructure().x - 60, playerTwo->GetStructure().y + (playerTwo->GetStructure().height / 2) - 25, arrowButtonsWidth, arrowButtonsHeight });
    rightPadRightArrowButton = new Button({ playerTwo->GetStructure().x + playerTwo->GetStructure().width, playerTwo->GetStructure().y + (playerTwo->GetStructure().height / 2) - 25, arrowButtonsWidth, arrowButtonsHeight });
    
    ballLeftArrowButton = new Button({ ball->GetPosition().x - ball->GetRadius() - 50, ball->GetPosition().y - ball->GetRadius() / 2, arrowButtonsWidth, arrowButtonsHeight });
    ballRightArrowButton = new Button({ ball->GetPosition().x + ball->GetRadius() - 15, ball->GetPosition().y - ball->GetRadius() / 2, arrowButtonsWidth, arrowButtonsHeight });
    
    scoreUpArrowButton = new Button({ playerOnePositionLeftScore.x - 15, playerOnePositionLeftScore.y - 60, arrowButtonsWidth, arrowButtonsHeight });
    scoreDownArrowButton = new Button({ playerOnePositionLeftScore.x - 15, playerOnePositionLeftScore.y + 50, arrowButtonsWidth, arrowButtonsHeight });
    
    timerUpArrowButton = new Button({ middleTimerPosition.x - 12, middleTimerPosition.y - 50, arrowButtonsWidth, arrowButtonsHeight });
    timerDownArrowButton = new Button({ middleTimerPosition.x - 12, middleTimerPosition.y + 70, arrowButtonsWidth, arrowButtonsHeight });

    LoadTexturesAndSetUp();    
}
void Game::Input(SceneManager* sceneManager, Music gameMusic, Music programMusic)
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

    if (ball->GetMoving()) 
    {
        playerOne->DetectInput(KEY_W, KEY_S); 
        playerTwo->DetectInput(KEY_UP, KEY_DOWN);
    }    

    if (arrowsWorking)
    {
        InputArrows();
    }

    if (IsKeyPressed(KEY_SPACE)) 
    {
        arrowsWorking = false;
    }

    ball->StartMoving(KEY_SPACE);
    PauseGameWithInput(sceneManager);
}
void Game::Update(int screenWidth, int screenHeight, SceneManager* sceneManager, Music music)
{
    UpdateMusicStream(music);

    ball->Update(screenWidth, screenHeight, playerOne, playerTwo);
        
    PadCollisionBall(playerOne, ball);
    PadCollisionBall(playerTwo, ball);        

    if (ball->GetMoving())
    {
        playerOne->MovePlayer(screenHeight);
        playerTwo->MovePlayer(screenHeight);
    }  

    if(!arrowsWorking && !IsCursorHidden()) 
    {
        HideCursor();
    }

    GameOver(sceneManager);

    UpdateTimer();
    
    UpdateScrollingValues();

    if (sceneManager->GetActualScene() != scenes::game && IsCursorHidden()) 
    {
        ShowCursor();
    }
}
void Game::Draw(int screenWidth, int screenHeight) 
{
    BeginDrawing();

    ClearBackground(RAYWHITE);   

    DrawBackground();

    DrawBall();

    DrawPlayer(playerOne);

    DrawPlayer(playerTwo);    
    
    if (arrowsWorking) 
    {
        DrawTextCodepoint(GetFontDefault(), scoreToWin[0], playerOnePositionLeftScore, 60, ORANGE);
        DrawTextCodepoint(GetFontDefault(), scoreToWin[1], playerOnePositionRightScore, 60, ORANGE);
    }
    else 
    {
        playerOne->ShowScore(playerOnePositionLeftScore, playerOnePositionRightScore);
        playerTwo->ShowScore(playerTwoPositionLeftScore, playerTwoPositionRightScore);
    }    

    ShowTimer();

    ShowKeysUI();

    if (arrowsWorking) 
    {
        DrawArrows();
    }

    DrawText("STOP/RESUME music (M)", 850, 680, 30, ORANGE);

    EndDrawing();
}
void Game::DrawForEndGame() 
{
    DrawBackground();

    DrawBall();

    DrawPlayer(playerOne);

    DrawPlayer(playerTwo);

    playerOne->ShowScore(playerOnePositionLeftScore, playerOnePositionRightScore);
    playerTwo->ShowScore(playerTwoPositionLeftScore, playerTwoPositionRightScore);    

    ShowTimer();     

    DrawText("STOP/RESUME music (M)", 850, 680, 30, ORANGE);
}
void Game::DeInit() 
{
    if (playerOne != NULL) 
    { 
        delete playerOne, playerOne = NULL; 
    }
    if (playerTwo != NULL) 
    {
        delete playerTwo, playerTwo = NULL; 
    }
    if (ball != NULL) 
    { 
        delete ball, ball = NULL; 
    }  

    UnloadTexture(background); 
    UnloadTexture(midgroundOne);   
    UnloadTexture(foregroundOne);
    UnloadTexture(midgroundTwo);
    UnloadTexture(foregroundTwo);
    UnloadTexture(midgroundThree);
    UnloadTexture(foregroundThree);
    UnloadTexture(ballTextureOne);
    UnloadTexture(padTextureOne);
    UnloadTexture(padTextureTwo);
    UnloadTexture(padTextureThree);
    UnloadTexture(padTextureFour);
    UnloadTexture(padTextureFive);
    UnloadTexture(verticalUpArrowButtonTexture);
    UnloadTexture(verticalDownArrowButtonTexture);
    UnloadTexture(horizontalRightArrowButtonTexture);
    UnloadTexture(horizontalLeftArrowButtonTexture);    
}

//Other Fuctions
void Game::PadCollisionBall(Pad* player, Ball* ball)
{
    player->SetTopRec({ player->GetStructure().x, player->GetStructure().y, player->GetStructure().width, 1 });
    player->SetDownRec({ player->GetStructure().x, player->GetStructure().y - 1 + player->GetStructure().height, player->GetStructure().width, 1 });
    player->SetRightRec({ player->GetStructure().x + player->GetStructure().width, player->GetStructure().y, 1, player->GetStructure().height });
    player->SetLeftRec({ player->GetStructure().x, player->GetStructure().y, 1, player->GetStructure().height });
   
    if (CheckCollisionCircleRec(ball->GetPosition(), ball->GetRadius(), player->GetTopRec()) || CheckCollisionCircleRec(ball->GetPosition(), ball->GetRadius(), player->GetDownRec()))
    {
        if (!player->GetIsCollidingBall())
        {  
            ball->SetNewRandomVelocityWithSameOldSign();

            ball->SetVelocity({ ball->GetVelocity().x * -1, ball->GetVelocity().y * -1 });

            if (player->GetIsCollidingBall() != true)
            {
                player->SetIsCollidingBall(true);
            }
        }
    }
    else if (CheckCollisionCircleRec(ball->GetPosition(), ball->GetRadius(), player->GetRightRec()) || CheckCollisionCircleRec(ball->GetPosition(), ball->GetRadius(), player->GetLeftRec()))
    {
        if (!player->GetIsCollidingBall())
        {
            ball->SetNewRandomVelocityWithSameOldSign();

            ball->SetVelocity({ ball->GetVelocity().x * -1, ball->GetVelocity().y });

            if (ball->GetPosition().y < (player->GetRightRec().y + (player->GetRightRec().height / 2)))
            {
                if (ball->GetVelocity().y > 0)
                {
                    ball->SetVelocity({ ball->GetVelocity().x, ball->GetVelocity().y * -1 });
                }
            }
            else
            {
                if (ball->GetVelocity().y < 0)
                {
                    ball->SetVelocity({ ball->GetVelocity().x, ball->GetVelocity().y * -1 });
                }
            }

            if (player->GetIsCollidingBall() != true)
            {
                player->SetIsCollidingBall(true);
            }
        }
    }
    else
    {
        if (player->GetIsCollidingBall() != false)
        {
            player->SetIsCollidingBall(false);
        }
    }    
}
void Game::GameOver(SceneManager* sceneManager)
{
    if (playerOne->playerWin(GetScoreToWin()) || playerTwo->playerWin(GetScoreToWin()) || (aTimer[2] == zero && (aTimer[1] == zero && aTimer[0] == zero)))
    {        
        sceneManager->SetActualScene(scenes::endGame);        
    }
}
void Game::PauseGameWithInput(SceneManager* sceneManager)
{
    if (IsKeyPressed(GetPauseGameKey())) 
    {
        sceneManager->SetActualScene(scenes::paused);
    }
}
void Game::ResetGameValues() 
{
    playerOne->SetPadY(270);
    playerTwo->SetPadY(270);
    playerOne->ResetScore();
    playerTwo->ResetScore();
    ball->SetX(640);
    ball->SetY(360);
    ball->SetMoving(false);
    SetDTimer(initDTimer);
    SetATimer(initATimer[0], initATimer[1], initATimer[2]);
    arrowsWorking = true;
    playerOne->SetTexturePad(TexturesPad::one);
    playerTwo->SetTexturePad(TexturesPad::one);
    ball->SetTextureBall(TexturesBall::one);
    SetScoreToWin(initScoreToWin[0], initScoreToWin[1]);
}
void Game::ShowTimer() 
{      
    DrawTextCodepoint(GetFontDefault(), aTimer[0], leftTimerPosition, 80, VIOLET);
    DrawTextCodepoint(GetFontDefault(), aTimer[1], middleTimerPosition, 80, VIOLET);
    DrawTextCodepoint(GetFontDefault(), aTimer[2], rightTimerPosition, 80, VIOLET);
}
void Game::UpdateTimer() 
{
    if (ball->GetMoving()) 
    {
        dTimer -= GetFrameTime();
    }   

    if (GetDTimer() <= 0)
    {
        dTimer = initDTimer;

        aTimer[2] -= 1;

        if (aTimer[2] < zero)
        {
            aTimer[2] = nine;
            aTimer[1] -= 1;
        }

        if (aTimer[1] < zero)
        {
            aTimer[1] = nine;
            aTimer[0] -= 1;
        }

        if (aTimer[0] < zero)
        {
            aTimer[0] = zero;
        }
    }
}
void Game::ShowKeysUI() 
{      
    DrawText("P(pause)", GetScreenWidth() - 120, 40, 25, WHITE);
    DrawText("ESC(exit)", 5, 40, 25, WHITE);

    if (playerOne->GetMovementStatus() == Movement::none) 
    {
        DrawText("W", static_cast<int>(playerOne->GetStructure().x), static_cast<int>(playerOne->GetStructure().y - 25), 25, WHITE);
        DrawText("S", static_cast<int>(playerOne->GetStructure().x), static_cast<int>(playerOne->GetStructure().y + playerOne->GetStructure().height + 10), 25, WHITE);
    }

    if (playerTwo->GetMovementStatus() == Movement::none)
    {
        DrawText("UP", static_cast<int>(playerTwo->GetStructure().x), static_cast<int>(playerTwo->GetStructure().y - 25), 25, WHITE);
        DrawText("DOWN", static_cast<int>(playerTwo->GetStructure().x), static_cast<int>(playerTwo->GetStructure().y + playerTwo->GetStructure().height + 10), 25, WHITE);
    }    
    
    if (!ball->GetMoving()) 
    {
        DrawText("SPACE(Launch)", static_cast<int>(ball->GetPosition().x - 80), static_cast<int>(ball->GetPosition().y - 70), 25, WHITE);
    }    
}
void Game::UpdateScrollingValues() 
{
    scrollingBack -= 0.1f;
    scrollingMid -= 0.5f;
    scrollingFore -= 1.0f;
    
    if (scrollingBack <= -background.width * 2) 
    {
        scrollingBack = 0;
    }
    if (scrollingMid <= -midgroundOne.width * 2) 
    { 
        scrollingMid = 0; 
    }
    if (scrollingFore <= -foregroundOne.width * 2) 
    {
        scrollingFore = 0; 
    }
}
void Game::DrawBackground() 
{   
    DrawTextureEx(background, { scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(background, { background.width * 2 + scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
        
    DrawTextureEx(midgroundOne, { scrollingMid, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(midgroundOne, { midgroundOne.width * 2 + scrollingMid, 0 }, 0.0f, 2.0f, WHITE);

    DrawTextureEx(midgroundTwo, { scrollingMid, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(midgroundTwo, { midgroundTwo.width * 2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);

    DrawTextureEx(midgroundThree, { scrollingMid, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(midgroundThree, { midgroundThree.width * 2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
       
    DrawTextureEx(foregroundOne, { scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(foregroundOne, { foregroundOne.width * 2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);

    DrawTextureEx(foregroundTwo, { scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(foregroundTwo, { foregroundTwo.width * 2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);

    DrawTextureEx(foregroundThree, { scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(foregroundThree, { foregroundThree.width * 2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
}
void Game::LoadTexturesAndSetUp() 
{
    background = LoadTexture("assets/textures/game_background/one.png");
    background.width = GetScreenWidth() / 2;
    background.height = GetScreenHeight() / 2;
    midgroundOne = LoadTexture("assets/textures/game_background/two.png");
    midgroundOne.width = GetScreenWidth() / 2;
    midgroundOne.height = GetScreenHeight() / 2;
    midgroundTwo = LoadTexture("assets/textures/game_background/three.png");
    midgroundTwo.width = GetScreenWidth() / 2;
    midgroundTwo.height = GetScreenHeight() / 2;
    midgroundThree = LoadTexture("assets/textures/game_background/four.png");
    midgroundThree.width = GetScreenWidth() / 2;
    midgroundThree.height = GetScreenHeight() / 2;
    foregroundOne = LoadTexture("assets/textures/game_background/five.png");
    foregroundOne.width = GetScreenWidth() / 2;
    foregroundOne.height = GetScreenHeight() / 2;
    foregroundTwo = LoadTexture("assets/textures/game_background/six.png");
    foregroundTwo.width = GetScreenWidth() / 2;
    foregroundTwo.height = GetScreenHeight() / 2;
    foregroundThree = LoadTexture("assets/textures/game_background/seven.png");
    foregroundThree.width = GetScreenWidth() / 2;
    foregroundThree.height = GetScreenHeight() / 2;

    scrollingBack = 0.0f;
    scrollingMid = 0.0f;
    scrollingFore = 0.0f;

    ballTextureOne = LoadTexture("assets/textures/ball/ball_one.png");
    ballTextureOne.width = static_cast<int>(ball->GetRadius() * 2);
    ballTextureOne.height = static_cast<int>(ball->GetRadius() * 2);
    ballTextureTwo = LoadTexture("assets/textures/ball/ball_two.png");
    ballTextureTwo.width = static_cast<int>(ball->GetRadius() * 2);
    ballTextureTwo.height = static_cast<int>(ball->GetRadius() * 2);
    ballTextureThree = LoadTexture("assets/textures/ball/ball_three.png");
    ballTextureThree.width = static_cast<int>(ball->GetRadius() * 2);
    ballTextureThree.height = static_cast<int>(ball->GetRadius() * 2);
    ballTextureFour = LoadTexture("assets/textures/ball/ball_four.png");
    ballTextureFour.width = static_cast<int>(ball->GetRadius() * 2);
    ballTextureFour.height = static_cast<int>(ball->GetRadius() * 2);
    ballTextureFive = LoadTexture("assets/textures/ball/ball_five.png");
    ballTextureFive.width = static_cast<int>(ball->GetRadius() * 2);
    ballTextureFive.height = static_cast<int>(ball->GetRadius() * 2);

    padTextureOne = LoadTexture("assets/textures/pads/pad_one.png");
    padTextureOne.width = static_cast<int>(playerOne->GetStructure().width);
    padTextureOne.height = static_cast<int>(playerOne->GetStructure().height);
    padTextureTwo = LoadTexture("assets/textures/pads/pad_two.png");
    padTextureTwo.width = static_cast<int>(playerOne->GetStructure().width);
    padTextureTwo.height = static_cast<int>(playerOne->GetStructure().height);
    padTextureThree = LoadTexture("assets/textures/pads/pad_three.png");;;
    padTextureThree.width = static_cast<int>(playerOne->GetStructure().width);
    padTextureThree.height = static_cast<int>(playerOne->GetStructure().height);
    padTextureFour = LoadTexture("assets/textures/pads/pad_four.png");;;
    padTextureFour.width = static_cast<int>(playerOne->GetStructure().width);
    padTextureFour.height = static_cast<int>(playerOne->GetStructure().height);
    padTextureFive = LoadTexture("assets/textures/pads/pad_five.png");;;
    padTextureFive.width = static_cast<int>(playerOne->GetStructure().width);
    padTextureFive.height = static_cast<int>(playerOne->GetStructure().height);

    verticalUpArrowButtonTexture = LoadTexture("assets/textures/UI/flecha_vertical_arriba.png");
    verticalUpArrowButtonTexture.width = arrowButtonsWidth;
    verticalUpArrowButtonTexture.height = arrowButtonsHeight;
    verticalDownArrowButtonTexture = LoadTexture("assets/textures/UI/flecha_vertical_abajo.png");
    verticalDownArrowButtonTexture.width = arrowButtonsWidth;
    verticalDownArrowButtonTexture.height = arrowButtonsHeight;
    horizontalRightArrowButtonTexture = LoadTexture("assets/textures/UI/flecha_horizontal_derecha.png");
    horizontalRightArrowButtonTexture.width = arrowButtonsWidth;
    horizontalRightArrowButtonTexture.height = arrowButtonsHeight;
    horizontalLeftArrowButtonTexture = LoadTexture("assets/textures/UI/flecha_horizontal_izquierda.png");
    horizontalLeftArrowButtonTexture.width = arrowButtonsWidth;
    horizontalLeftArrowButtonTexture.height = arrowButtonsHeight;
}
void Game::DrawArrows() 
{    
    /*leftPadLeftArrowButton->DrawButton();
    leftPadRightArrowButton->DrawButton();
    rightPadLeftArrowButton->DrawButton();
    rightPadRightArrowButton->DrawButton();
    ballLeftArrowButton->DrawButton();
    ballRightArrowButton->DrawButton();
    scoreUpArrowButton->DrawButton();
    scoreDownArrowButton->DrawButton();
    timerUpArrowButton->DrawButton();
    timerDownArrowButton->DrawButton();*/
    DrawTextureEx(horizontalLeftArrowButtonTexture, { leftPadLeftArrowButton->GetStructure().x, leftPadLeftArrowButton->GetStructure().y }, 0.0f, 1.0f, WHITE);//<-
   DrawTextureEx(horizontalRightArrowButtonTexture, { leftPadRightArrowButton->GetStructure().x, leftPadRightArrowButton->GetStructure().y }, 0.0f, 1.0f, WHITE);//->
    DrawTextureEx(horizontalLeftArrowButtonTexture, { rightPadLeftArrowButton->GetStructure().x, rightPadLeftArrowButton->GetStructure().y }, 0.0f, 1.0f, WHITE);//<-
    DrawTextureEx(horizontalRightArrowButtonTexture, { rightPadRightArrowButton->GetStructure().x, rightPadRightArrowButton->GetStructure().y }, 0.0f, 1.0f, WHITE);//->
    DrawTextureEx(horizontalLeftArrowButtonTexture, { ballLeftArrowButton->GetStructure().x, ballLeftArrowButton->GetStructure().y }, 0.0f, 1.0f, WHITE);//<-
    DrawTextureEx(horizontalRightArrowButtonTexture, { ballRightArrowButton->GetStructure().x, ballRightArrowButton->GetStructure().y }, 0.0f, 1.0f, WHITE);//->
    DrawTexture(verticalUpArrowButtonTexture, static_cast<int>(scoreUpArrowButton->GetStructure().x), static_cast<int>(scoreUpArrowButton->GetStructure().y), WHITE);//0 
    DrawTextureEx(verticalDownArrowButtonTexture, { scoreDownArrowButton->GetStructure().x, scoreDownArrowButton->GetStructure().y }, 0.0f, 1.0f,WHITE);//Abajo
    DrawTexture(verticalUpArrowButtonTexture, static_cast<int>(timerUpArrowButton->GetStructure().x), static_cast<int>(timerUpArrowButton->GetStructure().y), WHITE); //0
    DrawTextureEx(verticalDownArrowButtonTexture, { timerDownArrowButton->GetStructure().x, timerDownArrowButton->GetStructure().y }, 0.0f, 1.0f,WHITE);//Abajo
}
void Game::InputArrows() 
{
    if (leftPadLeftArrowButton->ButtonPressed())
    { 
        playerOne->ChangeTexturePadLeft();
    }
    if (leftPadRightArrowButton->ButtonPressed())
    {
        playerOne->ChangeTexturePadRight();
    }
    if (rightPadLeftArrowButton->ButtonPressed())
    {
        playerTwo->ChangeTexturePadLeft();
    }
    if (rightPadRightArrowButton->ButtonPressed())
    {
        playerTwo->ChangeTexturePadRight();
    }
    if (ballLeftArrowButton->ButtonPressed())
    {
        ball->ChangeTexturePadLeft();
    }
    if (ballRightArrowButton->ButtonPressed())
    {
        ball->ChangeTexturePadRight();
    }
    if (scoreUpArrowButton->ButtonPressed())
    {
        IncrementScoreToWin();
    }
    if (scoreDownArrowButton->ButtonPressed())
    {
        DecrementScoreToWin();
    }
    if (timerUpArrowButton->ButtonPressed())
    {
        IncrementTimerInTen();
    }
    if (timerDownArrowButton->ButtonPressed())
    {
        DecrementTimerInTen();
    }
}
void Game::DrawBall() 
{
    switch (ball->GetTextureBall())
    {         
    case TexturesBall::one:

        DrawTexture(ballTextureOne, static_cast<int>(ball->GetPosition().x - ball->GetRadius()), static_cast<int>(ball->GetPosition().y - ball->GetRadius()), WHITE);

        break;
    case TexturesBall::two:

        DrawTexture(ballTextureTwo, static_cast<int>(ball->GetPosition().x - ball->GetRadius()), static_cast<int>(ball->GetPosition().y - ball->GetRadius()), WHITE);

        break;
    case TexturesBall::three:

        DrawTexture(ballTextureThree, static_cast<int>(ball->GetPosition().x - ball->GetRadius()), static_cast<int>(ball->GetPosition().y - ball->GetRadius()), WHITE);

        break;
    case TexturesBall::four:

        DrawTexture(ballTextureFour, static_cast<int>(ball->GetPosition().x - ball->GetRadius()), static_cast<int>(ball->GetPosition().y - ball->GetRadius()), WHITE);

        break;
    case TexturesBall::five:

        DrawTexture(ballTextureFive, static_cast<int>(ball->GetPosition().x - ball->GetRadius()), static_cast<int>(ball->GetPosition().y - ball->GetRadius()), WHITE);

        break;    
    }
}
void Game::DrawPlayer(Pad* pad) 
{
    switch (pad->GetTexturePad())
    {
    case TexturesPad::one:

        DrawTexture(padTextureOne, static_cast<int>(pad->GetStructure().x), static_cast<int>(pad->GetStructure().y), WHITE);

        break;
    case TexturesPad::two:

        DrawTexture(padTextureTwo, static_cast<int>(pad->GetStructure().x), static_cast<int>(pad->GetStructure().y), WHITE);

        break;
    case TexturesPad::three:

        DrawTexture(padTextureThree, static_cast<int>(pad->GetStructure().x), static_cast<int>(pad->GetStructure().y), WHITE);

        break;
    case TexturesPad::four:

        DrawTexture(padTextureFour, static_cast<int>(pad->GetStructure().x), static_cast<int>(pad->GetStructure().y), WHITE);

        break;
    case TexturesPad::five:

        DrawTexture(padTextureFive, static_cast<int>(pad->GetStructure().x), static_cast<int>(pad->GetStructure().y), WHITE);

        break;
    }
}
void Game::IncrementTimerInTen() 
{
    if (aTimer[0] < nine || aTimer[1] < nine) 
    {
        aTimer[1] += 1;
    }

    if (aTimer[1] > nine) 
    {
        aTimer[1] = zero;
        aTimer[0] += 1;
    }
    
}
void Game::DecrementTimerInTen()
{
    if (aTimer[0] > zero || aTimer[1] > one)
    {
        aTimer[1] -= 1;
    }

    if (aTimer[1] < one)
    {
        aTimer[0] -= 1;
        aTimer[1] = nine;
    }    
}
void Game::IncrementScoreToWin() 
{
    if (scoreToWin[0] < nine || scoreToWin[1] < nine) 
    {
        scoreToWin[1] += 1;
    }

    if (scoreToWin[1] > nine) 
    {
        scoreToWin[1] = zero;
        scoreToWin[0] += 1;
    }
}
void Game::DecrementScoreToWin()
{
    if (scoreToWin[0] > zero || scoreToWin[1] > one)
    {
        scoreToWin[1] -= 1;
    }

    if (scoreToWin[1] < one)
    {
        scoreToWin[0] -= 1;
        scoreToWin[1] = nine;
    }
}