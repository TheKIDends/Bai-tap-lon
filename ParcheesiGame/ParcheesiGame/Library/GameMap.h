#ifndef __GAMEMAP__
#define __GAMEMAP__

#include "CommonFunction.h"

#include <iostream>

using namespace std;

class GameMap {
    protected:
        int idStartPosition[MAX_PLAYERS];
        int idStartDestination[MAX_PLAYERS];
        
        pair <int, int> mapChessboard[MAX_ID_MAP];
        pair <int, int> idLeaderboard[MAX_PLAYERS];

    public:
        GameMap() {}
        void buildMap();
};

#endif // __GAMEMAP__
