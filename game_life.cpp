#include "game_life.hpp"
using namespace std;

game_life::game_life(int _H, int _W) : H(_H), W(_W), config(H,vector<bool>(W,false)) {}
/* 
// This is equivalent to : 
game_life::game_life(int _H,int _W): H(_H), W(_W), config(H) {
    for(int i = 0; i < H; i++){
        config[i].resize(W);
        for(int j = 0; j < W; j++){
            config[i][j] = false;
        }
    }
} */


int game_life::neighbors(int i, int j) const {
    int nb_neighbors = 0;
    for(int h = i-1; h <= i+1; h++){
        for(int w = j-1; w <= j+1; w++){
            if( (h >= 0 && h < H) && (w >= 0 && w < W) && !(h == i && w == j) ){
                nb_neighbors += config[h][w];
            }
        }
    }
    return nb_neighbors;
}

/*
    Note :
    Negative indices are already handled correctly. Specifically:
    For (h < 0) and (w < 0), the conditions h >= 0 and w >= 0 prevent these indices from being used. 
    Therefore, if h or w equals -1, they will not satisfy h >= 0 or w >= 0, respectively, 
                        and the code will avoid accessing these invalid indices.

*/


void game_life::iteration(){
    game_life new_state(H,W);
    for(int h = 0; h < H; h++){
        for(int w = 0; w < W; w++){
            int n = neighbors(h, w);
            if(n == 3){
               new_state.config[h][w] = true; 
            }
            else if( (n >= 1) || (n <= 4) ){
                new_state.config[h][w] = false;
            }
            else{
                continue;
            }
        }
    }
    move(new_state.config.begin(),new_state.config.end(),config.begin());
}