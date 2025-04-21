## **How to play the game Arrowanna:**
BATTLE BEGIN!
Player will stand still in the center position
Arrows go from 4 directions: up, down, left, right. From outside the screen, they fly straight to the player
Players will need to use 4 keys W, S, A, D, corresponding to building shields in 4 directions: up, down, left, right. 
Projectile will be destroyed if you set up your shield in the right direction and at the right time when the bullets are approaching, if you let the Projectile hit you too much and you lose all your health, YOU WILL DIE.
When the player fills up the energy bar, specifically 6 gold energy, the game will switch to the player's turn to attack the boss
The boss will put up a shield to block your bullets, you wait for the boss to be distracted to release the bullet and shoot a critical bullet. Precise shoot take more health from Boss
The lower boss's health, the harder the game will be, the more arrows will be and the faster they will. So you should try to defeat Boss as fast as you can
Objective: Drain boss's health to zero to win the battle

## **Code structure**
Note: all functions and attributes listed below are public

- **Player**
  - Attributes: `gameObject`, `shieldDir`, `projectile`, `health`, `goldEnergy`, etc.
  - Methods:
    - `update()`
    - `HandleEvent(SDL_Event&)`
    - `HandleShoot(SDL_Event&)`
    - `takeDamage(int)`
    - `ReceiveGoldEnergy()`
    - `Shoot()`
    - `InPlayerTurn()`
    - `InBossTurn()`
    - `isAlive()`
    - `PlayGetEnergySound()`
    - `PlayBlockSound()`

- **Boss**
  - Attributes: `gameObject`, `obstacles`, `maxHealth`, `health`, etc.
  - Methods:
    - `update()`
    - `renderBoss(SDL_Renderer*)`
    - `InPlayerTurn()`
    - `InBossTurn()`
    - `GetHealth()`
    - `TakeDamage(int)`

- **Wave**
  - Attributes: `projectiles`, `width`, `height`, etc.
  - Methods:
    - `update()`
    - `spawnProjectile()`
    - `updateProjectiles()`
    - `renderBoundaries()`
    - `renderProjectiles()`
    - `clearProjectiles()`
    - `setMode(WaveMode)`
    - `getMode()`

- **Projectile**
  - Attributes: `gameObject`, `direction`, `speed`, `isAlive`
  - Methods:
    - `update()`
    - `render(SDL_Renderer*)`
    - `hasHitBoss()`
    - `hasHitPlayer()`
    - `hasHitShield()`
    - `isOffScreen()`

- **Explosion**
  - Attributes: `center`, `particles`
  - Methods:
    - `update(float dt)`
    - `render(SDL_Renderer*)`
    - `isAlive()`

- **Particle**
  - Attributes: `position`, `velocity`, `color`, `lifetime`, `age`, `gravity`, `size`
  - Methods:
    - `update(float dt)`
    - `render(SDL_Renderer*)`
    - `isAlive()`

- **GameManager**
  - Attributes: `score`, `gameState`, `player`, `boss`, `m_UIManager`
  - Methods:
    - `Update()`
    - `ProcessInput(SDL_Event)`
    - `InPlayerTurn()`
    - `InBossTurn()`
    - `Win()`
    - `Lose()`
    - `ChangeGameState(GameState)`
    - `HandleEvent(SDL_Event)`

- **UIManager**
  - Methods:
    - `render(int health, int score, int goldEnergy, int maxGoldEnergy)`
    - `renderGameOver()`
    - `renderWin()`
    - `renderGoldEnergyBar(int x, int y, int goldEnergy, int maxEnergy)`
    - `RenderBossHealthBar()`
