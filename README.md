## **Script dependencies:**
Main.cpp
#include <SDL2/SDL.h>
#include "Player.h"
#include "Wave.h"
Player.cpp
#include "Player.h"
#include <bits/stdc++.h>
Player.h
#include "Ultilities.h"
Projectile.cpp
#include "Projectile.h"
#include "Player.h"
Projectile.h
#include <SDL2/SDL.h>
#include "Ultilities.h"
Ultilities.h
#include <SDL2/SDL.h>
#include <cmath>
Ultilities.cpp
#include "Ultilities.h"
Wave.h
#include "Projectile.h"

## **How to play the game:**
Player will stand still in the center position
Arrows go from 4 directions: up, down, left, right. From outside the screen, they fly straight to the player
Players will need to use 4 keys W, S, A, D, corresponding to building shields in 4 directions: up, down, left, right.
The longer you play, the harder the game will be, the more arrows will be and the faster they will go. The player's goal is to live long and become a legend