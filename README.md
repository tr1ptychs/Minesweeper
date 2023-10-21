# Minimal-Minesweeper

Minesweeper clone with a minimal art style made as a fun little project while I wait for more programming assignments in school.

## how to run

As of right now, Minimal Minesweeper is only buildable on osx. I plan to add windows support soon.

To play, use "make" to compile and then "./bin/build_osx" in the main folder to run.

## how to play

Press 1 on keyboard for a new beginner game, 2 for a new intermediate game, or 3 for a new expert game at any time.

Left click will reveal the tile you're hovering over.

Colors represent hint colors in the original minesweeper. Blue is 1, green is 2, red 3, dark blue 4, etc.

Right click to place a "flag" (circle).

If you left click a tile with a hint and there is the same number of flags in the surrounding tiles, all other surrounding tiles will be revealed.

When you win (or lose), you may left click again to start a new game.
