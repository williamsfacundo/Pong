#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "sceneManager.h"
#include "Button.h"

class Game
{
private:
	Pad* playerOne;
	Pad* playerTwo;
	Ball* ball;	
	int scoreToWin[2];	
	int pauseGameKey;
	double dTimer;
	short aTimer[3];
	Texture2D background;
	Texture2D midgroundOne;
	Texture2D midgroundTwo;
	Texture2D midgroundThree;
	Texture2D foregroundOne;
	Texture2D foregroundTwo;
	Texture2D foregroundThree;
	float scrollingBack = 0.0f;
	float scrollingMid = 0.0f;
	float scrollingFore = 0.0f;
	Texture2D ballTextureOne;
	Texture2D ballTextureTwo;
	Texture2D ballTextureThree;
	Texture2D ballTextureFour;
	Texture2D ballTextureFive;
	Texture2D padTextureOne;
	Texture2D padTextureTwo;
	Texture2D padTextureThree;
	Texture2D padTextureFour;
	Texture2D padTextureFive;
	bool arrowsWorking;
	Button* leftPadLeftArrowButton;	 
	Button* leftPadRightArrowButton;
	Button* rightPadLeftArrowButton;
	Button* rightPadRightArrowButton;
	Button* ballLeftArrowButton;
	Button* ballRightArrowButton;
	Button* scoreUpArrowButton;
	Button* scoreDownArrowButton;
	Button* timerUpArrowButton;
	Button* timerDownArrowButton;	
	Texture2D verticalUpArrowButtonTexture;
	Texture2D verticalDownArrowButtonTexture;
	Texture2D horizontalRightArrowButtonTexture;
	Texture2D horizontalLeftArrowButtonTexture;
public:
	//Setters
	Game(int screenWidth, int screenHeight);
	~Game();		
	void SetScoreToWin(short scoreLeft, short scoreRight);
	void SetPauseGameKey(int pausedGameKey);
	void SetDTimer(double timer);	
	void SetATimer(short scoreLeft, short scoreMedium, short scoreRight);
	
	//Getter	
	int* GetScoreToWin();
	int GetPauseGameKey();
	double GetDTimer();	

	//Game Flow
	void Init();
	void Input(SceneManager* sceneManager, Music gameMusic, Music programMusic);
	void Update(int screenWidth, int screenHeight, SceneManager* sceneManager, Music music);
	void Draw(int screenWidth, int screenHeight);
	void DrawForEndGame();
	void DeInit();
			
	//Other Fuctions
	void PadCollisionBall(Pad* player, Ball* ball);	
	void GameOver(SceneManager* sceneManager);
	void PauseGameWithInput(SceneManager* sceneManager);
	void ResetGameValues();
	void ShowTimer();
	void UpdateTimer();	
	void ShowKeysUI();
	void UpdateScrollingValues();
	void DrawBackground();
	void LoadTexturesAndSetUp();
	void DrawArrows();
	void InputArrows();
	void DrawBall();
	void DrawPlayer(Pad* pad);
	void IncrementTimerInTen();
	void DecrementTimerInTen();
	void IncrementScoreToWin();
	void DecrementScoreToWin();
};

#endif
