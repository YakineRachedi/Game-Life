#ifndef GAME_LIFE_INCLUDED
#define GAME_LIFE_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <random>

class game_life {
    private:
        int H, W;
        std::vector<std::vector<bool> > config;
    public:
        game_life(int _H, int _W);
        game_life(std::ifstream & input);
        game_life(int _H, int _W, double p, std::mt19937 & G);
        int height() const {return this->H;}
        int width() const {return this->W;}
        int occupied_cells_count() const;
        std::vector<std::tuple<int, int, std::string>> get_state_from_cells() const;
        int neighbors(int i, int j) const; 
        void iteration();
        void display(std::ostream & stream) const;
};

#endif