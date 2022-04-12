#ifndef __UTILS__
#define __UTILS__

#include <iostream>

using namespace std;

class Random {
    private:
        
    public:
        static int random(int l, int r) { srand(time(NULL)); return l + rand() % (r - l + 1); }
};

#endif // __UTILS__
