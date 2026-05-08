# Roguelike Game

| Group Members  |
|----------------|
| Dustin Bellina |
| Ian Flores     |
| Alir Louis     |
| Armani Ruffin  |
 
# About the Game

This project is a roguelite adventure, where you as the hero set out on an adventure to slay the Vampire King and free the local town of his evil reign. As you travel through the various environments you will reveal more of your surroundings. Try to fight your way through and make your hometown proud!


# How to Play

Press `/` in game to get a complete list of controls and some more useful information

Controls

-   Use the `arrow keys` to move
-   Press `i` to open your inventory
-   Press `e` to eat some food
-   Press `s` to view your stats  
-   Press `ENTER` to interact with signs, entrances, and shops
- Press `SPACE` to clear the MORE message
- Press `/` to bring up the help menu

Gameplay

-   To attack an enemy, simply move into the enemy. If you try to run away they will follow you to the ends of the earth!
    
-   You will be healed some amount every 10 turns when you are out of combat. The turn count resets when you are in combat

Symbology

-   A-Z : Enemies
-   ☼ : Enterances. Enter to proceed to the next level
-   ⌂ : Shops. Enter to purchase potions and bread
-   ╔,╚,╗,╝,║,═ : Walls
-   ╬ : Doors
-   ▒ : Hallways
-   . : Floors
-   @ : Hero
-   ☉ : Gold pieces
-   ↑ : Signs. Interact to read
-   ♣ : Bread
-   ♪ : Potions


# About the Code

All functions are described in the file headers, but the absolute basics are:

-   [main() @ main.cpp](https://github.com/Dustin-Bellina/CST117-Final-Project/blob/main/main.cpp#L17)
	-   This runs the main loop of the game, including taking the player’s turn, taking the enemies’ turns, printing messages, and more.

-   [inputDetector() @ input_detection.cpp](https://github.com/Dustin-Bellina/CST117-Final-Project/blob/main/input_detection.cpp#L22)
	-   Handles user input and performs the corresponding action

-   [movementHandler() @ movement.cpp](https://github.com/Dustin-Bellina/CST117-Final-Project/blob/main/movement.cpp#L21)
	-   This function handles what happens when the user attempts to move in a direction. If there’s an enemy in that space, attack the enemy. If there’s an item, pick it up. Etcetc.

-   [enemyTurn() @ enemies.cpp](https://github.com/Dustin-Bellina/CST117-Final-Project/blob/main/enemies.cpp#L61)
	-   This function handles taking the enemies’ turns, including attacking the player and moving

-   [loadLevel() @ map_generation.cpp](https://github.com/Dustin-Bellina/CST117-Final-Project/blob/main/map_generation.cpp#L184)
	-   This function loads the necessary level to the map array
 
 
# Screenshots
<img width="1115" height="628" alt="Main Menu" src="https://github.com/user-attachments/assets/ff20e0a8-aa96-486b-90d2-3ccf475f866c" />
<img width="1115" height="628" alt="Town" src="https://github.com/user-attachments/assets/e11c66eb-d161-45d3-9738-dd45fe2b252e" />
<img width="1115" height="628" alt="Sewer" src="https://github.com/user-attachments/assets/606aaaee-7fa9-4e4a-917d-795fee5210a8" />
<img width="1115" height="628" alt="Cave" src="https://github.com/user-attachments/assets/5206cf2a-4d08-4b9b-9bf8-247859da4bd9" />
<img width="1115" height="628" alt="Death" src="https://github.com/user-attachments/assets/92a887a9-7cc1-4b38-900c-8d8d3b18641e" />
