#pragma once

#define IsKeyDown(x) GetKeyState(x) & 0x8000

const unsigned appleChance = 10;
const unsigned boardWidth = 50, boardHeight = 25;
const unsigned tileWidth = 10, tileHeight = 10;