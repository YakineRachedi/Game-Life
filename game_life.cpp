#include "game_life.hpp"
#include <algorithm>
using namespace std;

/*===================================================*** Constructors ***====================================================================*/

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

game_life::game_life(ifstream & input) {
    // Read the height and width of the grid from the input stream
    input >> this->H;
    input >> this->W;

    // Resize the outer vector to hold 'H' rows
    this->config.resize(H);

    string reading;
    for(int h = 0; h < H; h++) {
        // Resize each row to have 'W' columns
        this->config[h].resize(W);

        // Read a line from the input stream containing the cell states
        input >> reading;

        for(int w = 0; w < W; w++) {
            // If the character is 'X', the cell is alive (true), otherwise it's dead (false)
            if(reading[w] == 'X') {
                config[h][w] = true;
            } else {
                config[h][w] = false;
            }
        }
    }
}

game_life::game_life(int _H, int _W, double p, std::mt19937 & G) : game_life(_H,_W){
    bernoulli_distribution B(p);
    for(int i = 0; i <H; i++){
        for(int j = 0; j < W; j++){
            config[i][j] = B(G);   
        }
    }
}

/*===================================================*** Methods ***====================================================================*/
int game_life::neighbors(int i, int j) const {
    int nb_neighbors = 0;

    // Loop over the 3x3 neighborhood surrounding the cell (i, j)

    for(int h = i - 1; h <= i + 1; h++) {
        for(int w = j - 1; w <= j + 1; w++) {
    
            // Check if the neighboring cell is within grid boundaries and is not the cell itself
    
            if((h >= 0 && h < H) && (w >= 0 && w < W) && !(h == i && w == j)) {
    
                // Add to the neighbor count if the cell is alive (true)
    
                nb_neighbors += config[h][w];
            }
        }
    }

    return nb_neighbors; // Return the total number of live neighbors
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
            else if( (n <= 1) || (n >= 4) ){
                new_state.config[h][w] = false;
            }
            else{
                new_state.config[h][w] = config[h][w];
            }
        }
    }
    config = move(new_state.config);
}

void game_life::display(ostream & stream) const {
    stream << this->H << " " << this->W << "\n";
    for(int h = 0; h < H; h++){
        for(int w = 0; w < W; w++){
            config[h][w] == true ? stream << "X " : stream << ". ";
        }
        stream << "\n";
    }
}

// Note : we cannot use the algorithm count for a 2D vector we need to flatten it into a single range, or we can use std::accumulate + std::count
int game_life::occupied_cells_count() const {
    int count = 0;
    for (const auto& row : this->config) {
        count += std::count(row.begin(), row.end(), true);
    }
    return count;
}

// Method to obtain the coordinates of occupied cells
std::vector<std::tuple<int, int, std::string>> game_life::get_state_from_cells() const {
    std::vector<std::tuple<int, int, std::string>> occupied_cells;
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            config[i][j] == true ? occupied_cells.emplace_back(i, j, "gray") : occupied_cells.emplace_back(i, j, "white");
        }
    }
    return occupied_cells;
}

/*================================================================END====================================================================*/