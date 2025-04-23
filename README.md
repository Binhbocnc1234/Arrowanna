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

# 🎯 Arrowanna - Boss Battle Defense Game

**Name:** Nguyễn Thanh Bình  
**Student ID:** 24021391  
**Class:** K69I-CS3  
**Video link:** [Watch on YouTube](https://www.youtube.com/watch?v=rE4IkQR0AJg)

---

## 🧩 Game Elements

### 🧠 Boss

- **BossTurn**: Attacks the player with a series of projectiles.
- **PlayerTurn**: Defends itself with 4 flipping shields that distract the player.

### 🔥 Laser

A special attack tool used by the Boss, activated when Boss health drops below half.

- Every **6 seconds**, a Laser attack occurs.
- Laser goes through 4 states:

| State        | Description                                                                 |
|--------------|-----------------------------------------------------------------------------|
| `Charge`     | Lasts around 2 seconds. The width of the laser gradually increases. Color: white with a red tint, alpha = 90. |
| `Firing`     | Lasts 0.75 seconds. Laser turns red and deals **3 damage**, once every 0.25s. |
| `Collapsing` | The laser shrinks its width down to 0. Then transitions to `InActive`.      |
| `InActive`   | No rendering, no laser, no actions.                                         |

---

## 🌊 Wave

As Boss HP drops, the play area gets narrower — arrows spawn closer to the player, requiring faster reflexes.

### 4 Wave Types:

- **Normal wave**: As the name suggests — easy to defend.
- **Fast-faced wave**: Arrows move faster.
- **Slowmotion wave**: Arrows move slowly but appear very densely.
- **Tricky wave**: Many `TrickyProjectile` objects appear to confuse the player.

---

## 🌟 Other Awesome Features

### 🏠 Lobby:
*(<image link>, no need to include)*

### ⏸️ Pause Menu:
*(<image link>, no need to include)*

---

## 🔊 Sound

- Sound effect when player blocks a projectile with shield.
- Sound effect when player collects **energy orbs**.
- Most importantly: **Background music inspired by Undertale**!

---

## 💥 Cool Effects in Game

- **Explosion effect**: Appears when a projectile explodes.
- **Lerp effect**: Smooth transition when moving the player to bottom of screen during `PlayerTurn`.
- **Boss hurt effect**: Boss shakes on hit, damage numbers and HP bar appear.
- **Player hurt effect**: Heart icon flashes between red and white.

Also includes:
- **Floating damage text** when hit

---

## 📚 References

- **Idea & gameplay inspiration**: Based on **Undyne Boss Fight** from Undertale with additional mechanics:  
  https://www.youtube.com/watch?v=MFLnSfrDD4w
- **Source code**: Fully built from scratch — **not based on any existing template**
- **Graphics**: Pixel-art style, drawn manually or rendered using `SDL_DrawRect()`
- **Sound**: Sourced from **Pixabay**, includes copyrighted music from Undertale
- **Font**: Radiant-Kingdom
- **Applied knowledge**: Game Design, OOP, Design Patterns, core SDL2 concepts
- **Tech Support**: ChatGPT  
  > Thanks to AI, I don’t need to visit SDL2 official docs anymore — just ask and get function explanations instantly.

---

🎮 **Objective**: Block every incoming projectile. Fill your energy bar. Unleash your counterattack. Defeat the Boss. Good luck!

