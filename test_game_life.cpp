#include "game_life.cpp"
using namespace std;

int main(){
    game_life test_game(4,4);
    cout << test_game.neighbors(0,0) << "\n";
    
    ifstream input("glider.dat");
    test_game = game_life(input);
    input.close();
    
    cout << "Initial state \n ========== \n";
	test_game.display(cout);
	cout << "\n =========== \n";

    cout << "Displaying 20 intial states consecutive of this test \n";
    for(int i = 1; i <= 20; i++){
        test_game.iteration();
        cout << "Iteration : " << i << "\n * * * \n";
        test_game.display(cout);
        cout << "\n ======== \n";
    }
    cout << "\n\n";
    return 0;
}