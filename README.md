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
