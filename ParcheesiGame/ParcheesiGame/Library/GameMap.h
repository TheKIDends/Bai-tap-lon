#ifndef __GAMEMAP__
#define __GAMEMAP__

#include "CommonFunction.h"

#include <iostream>

using namespace std;

class GameMap {
    protected:
        int idStartPosition[MAX_NUMBER_PLAYERS];
        int idStartStable[MAX_NUMBER_PLAYERS];
        
        pair <int, int> mapChessboard[MAX_ID_MAP];
        pair <int, int> idLeaderboard[MAX_NUMBER_PLAYERS];

    public:
        GameMap() {}
        void buildMap();
};

#endif // __GAMEMAP__
