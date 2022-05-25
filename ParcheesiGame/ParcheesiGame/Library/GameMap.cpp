#include "GameMap.h"

void GameMap::buildMap() {
    idLeaderboard[0] = { 515, 147 - 70 };
    idLeaderboard[1] = { 292, 300 - 70};
    idLeaderboard[2] = { 727, 300 - 70};

    idStartPosition[0] = 17;
    idStartPosition[1] = 31;
    idStartPosition[2] = 45;
    idStartPosition[3] = 59;

    idStartDestination[0] = 72;
    idStartDestination[1] = 78;
    idStartDestination[2] = 84;
    idStartDestination[3] = 90;

    // Start green
    mapChessboard[0] = { 433, 478 };
    mapChessboard[1] = { 630, 478 };
    mapChessboard[2] = { 532, 421 };
    mapChessboard[3] = { 532, 534 };

    // Start yellow
    mapChessboard[4] = { 895, 210 };
    mapChessboard[5] = { 895, 323 };
    mapChessboard[6] = { 796, 265 };
    mapChessboard[7] = { 993, 265 };

    // Start red
    mapChessboard[8] = { 436,   56 };
    mapChessboard[9] = { 633,   56 };
    mapChessboard[10] = { 535,  113 };
    mapChessboard[11] = { 535,   -1 };

    // Start blue 
    mapChessboard[12] = { 74, 264 };
    mapChessboard[13] = { 271, 264 };
    mapChessboard[14] = { 173, 209 };
    mapChessboard[15] = { 173, 322 };

    int dx = 33, dy = 19;
    int  x = 268, y = 382;

    // Green
    x += dx; y += dy; mapChessboard[16] = { x, y - 3 };
    x += dx; y += dy; mapChessboard[17] = { x, y };
    for (int i = 18; i <= 23; ++i) { x += dx; y -= dy; mapChessboard[i] = { x, y }; }
    for (int i = 24; i <= 29; ++i) { x += dx; y += dy; mapChessboard[i] = { x, y }; }

    // Yellow
    x += dx; y -= dy; mapChessboard[30] = { x, y - 6 };
    x += dx; y -= dy; mapChessboard[31] = { x, y };
    for (int i = 32; i <= 37; ++i) { x -= dx; y -= dy; mapChessboard[i] = { x, y }; }
    for (int i = 38; i <= 43; ++i) { x += dx; y -= dy; mapChessboard[i] = { x, y }; }

    // Red
    x -= dx - 2; y -= dy + 2; mapChessboard[44] = { x, y - 8 };
    x -= dx - 2; y -= dy + 2; mapChessboard[45] = { x, y };
    for (int i = 46; i <= 51; ++i) { x -= dx; y += dy; mapChessboard[i] = { x, y }; }
    for (int i = 52; i <= 57; ++i) { x -= dx; y -= dy; mapChessboard[i] = { x, y }; }

    // Blue
    x -= dx + 2; y += dy + 0; mapChessboard[58] = { x , y - 7 };
    x -= dx + 2; y += dy + 1; mapChessboard[59] = { x, y };
    for (int i = 60; i <= 65; ++i) { x += dx; y += dy; mapChessboard[i] = { x, y }; }
    for (int i = 66; i <= 71; ++i) { x -= dx; y += dy; mapChessboard[i] = { x, y }; }

    // Set id destination 
    x = mapChessboard[16].first; y = mapChessboard[16].second + 5;
    for (int i = 72; i <= 77; ++i) { x += dx; y -= dy + 3; mapChessboard[i] = { x, y }; }

    x = mapChessboard[30].first; y = mapChessboard[30].second + 6;
    for (int i = 78; i <= 83; ++i) { x -= dx; y -= dy + 3; mapChessboard[i] = { x, y }; }

    x = mapChessboard[44].first; y = mapChessboard[44].second + 8;
    for (int i = 84; i <= 89; ++i) { x -= dx; y += dy - 3; mapChessboard[i] = { x, y }; }

    x = mapChessboard[58].first; y = mapChessboard[58].second + 8;
    for (int i = 90; i <= 95; ++i) { x += dx; y += dy - 3; mapChessboard[i] = { x, y }; }
}
