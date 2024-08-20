#include "game_life.cpp"
using namespace std;

int main(){
    game_life test_games_1(4,4);
    cout << test_games_1.neighbors(0,0) << "\n";

    return 0;
}