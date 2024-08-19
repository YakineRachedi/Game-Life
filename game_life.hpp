#ifndef GAME_LIFE_INCLUDED
#define GAME_LIFE_INCLUDED

#include <iostream>
#include <vector>

class jeu_vie {
    private:
        int H, W;
        std::vector<std::vector<bool> > config;
    public:
        jeu_vie(int _H, int _W); 
};

#endif