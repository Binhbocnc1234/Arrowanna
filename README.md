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
-Player:
Attributes : gameObject, currentDirection
update()
HandleEvent(): receive SDL_Event and process it
-Boss: 
Attributes: gameObject
update()
-Wave:
update()
-Projectile:
Attributes: speed, gameObject
Functions:
hasHitBoss()
hasHitPlayer()
hasHitObstacles():
