#include "game_life.cpp"
#include <ctime>
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

    cout << "Second part : Random ! \n";
    
    // testing for a random values of height, width, parameter p :

    mt19937 G(time(nullptr));
    const int Height = 15;
    const int Width = 25;
    const double p = 0.3;
    game_life test_game_random(Height,Width,p,G);

    for(int i = 1; i <= 100; i++){
        test_game_random.iteration();
    }
    cout << "Displaying the 100-th iteration : \n";
    test_game_random.display(cout);

    cout << "Number of occupied cells for this time : " << test_game_random.occupied_cells_count() << "\n";

    const int nb_iter = 100;
    const int nb_realizations = 100;

    for(double p = 0.1; p < 0.95; p += 0.1) {
        int total_cells = 0;
        //for(int h = 0; h < Height; h++){
        //    for(int w = 0; w < Width; w++){
                for(int realization = 0; realization < nb_realizations; realization++) {

                    // Create a new game with dimensions, probability p, and random number generator G
                    //game_life New_game_test(h, w, p, G);
                    game_life New_game_test(Height, Width, p, G);

                    // Perform the iterations for the game
                    for(int i = 0; i < nb_iter; i++) {
                        New_game_test.iteration();
                    }

                    // Add the count of occupied cells from this realization
                    total_cells += New_game_test.occupied_cells_count(); // Ensure occupied_cells_count returns the number of occupied cells
                }
            // Calculate and print the average number of occupied cells
            cout << "p=" << p << " ; average number of cells: " << (total_cells / static_cast<double>(nb_realizations)) << "\n";
        //    }
        //}

    }
    return 0;
}