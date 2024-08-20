#ifndef GAME_LIFE_INCLUDED
#define GAME_LIFE_INCLUDED

#include <iostream>
#include <vector>

class game_life {
    private:
        int H, W;
        std::vector<std::vector<bool> > config;
    public:
        game_life(int _H, int _W);
        int height() const {return this->H;}
        int width() const {return this->W;}
        int neighbors(int i, int j) const; 
};

#endif