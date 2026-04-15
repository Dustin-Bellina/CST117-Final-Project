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
