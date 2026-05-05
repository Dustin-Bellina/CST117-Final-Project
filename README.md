Changelog
# 4/14/2026 12:49AM
## Modularity and Readability Update

\+ Create map_generation.cpp
- Contains the functions for map generation

\+ Create movement.cpp
- Contains the functins for movement and key handling

\+ Create prototypes.h
- Mostly for code readability
- Contains all function prototypes.  /!\ IMPORTANT: Be sure to `#include "prototypes.h"` in each file you create. /!\
- All function prototypes should be placed here when you're finished testing and such

: Modify main.cpp
- Only calls `generateTown()` and `keyDetector()` now

---
---
# 4/14/2026 11:27PM
## Menus 'n' Such

\+ Create input_detection.cpp
- Relocated keyDetector() here
- Renamed keyDetector() -> inputDetector()

\+ Added some comments to make some things clearer and more readable

: Renamed Main Menu!.cpp to menus.cpp

: Modify menu.cpp
- \+ Add function menuHandler() to detect and redirect player to proper menu from the level (shop, Sewer, etc.)
- : Modified most functions to match, integrate, and read better

### Additional Notes:
- Can now enter the shop, purchase things, and use items!
- No Sewer for now :( Coming hopefully next update

---
---
# 4/16/2026 2:52PM
## The Text Engine Update
### main.cpp
\+ Added proper debug mode implementation - To remove in final project

: Accounted for playerType changes

### menus.cpp
\+ Created signHandler() to display sign text

: Added onto menuHandler()

: Prettified the help menu and implemented text engine

: Changed how text gets outputted for a cleaner result and to account for the added text engine

: Moved initializePlayer(), saveGame(), and loadGame() to data_management.cpp

### data_management.cpp
\+ Created file

### input_detection.cpp
\+ Added various inputs

: Modified function to account for playerType change

### movement.cpp
: Modified function to account for the playerType change

: Added all walls and empty space as an unmovable object for the player

### map_generation.cpp
\+ Created generateSewer() and filled out sublevel 1

\+ Created generateHall()

: Modified functions to account for the playerType change

: Modified clearScreen() to not spam the console

### text_engine.cpp
\+ Created file

\+ Created te_print()

\+ Created te_error()

\+ Created more()


---
---
# 5/5/2026 10:02AM
## Endgame Update
Finished the game!  Added WAY too much to actually remember (including 9 shiny new files) so just trust me bro™