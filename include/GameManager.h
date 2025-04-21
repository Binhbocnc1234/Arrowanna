#pragma once
#include "Ultilities.h"
#include "Player.h"
#include "UIManager.h"
#include "Boss.h"
#include <SDL2/SDL.h>
enum GameState
{
    BossTurn,
    PlayerTurn,
    Lose,
    Win
};
class GameManager{
public:
    static GameManager *getInstance();
    GameManager();
    void Update();
    void ProcessInput(SDL_Event e);
    void InPlayerTurn();
    void InBossTurn();
    void Win();
    void Lose();
    void ChangeGameState(GameState state);
    void HandleEvent(SDL_Event e);
    int score = 0;
    GameState gameState;

private:
    static GameManager *instance;
    Boss boss ;
    Player player ;
    UIManager m_UIManager ;
    Uint32 gameOverStart = 0;
};
