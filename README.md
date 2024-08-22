The goal of this project is to program an implementation of the Game of Life. This "game" consists of the evolution of a set of cells placed on a grid. Specifically, we have a finite grid made up of empty cells and cells occupied by a living cell. The state of the grid evolves in discrete time steps according to the following rules:

The state (empty or occupied by a cell) of each grid cell in the next step is determined by its current state and the number of currently occupied neighboring cells among its 8 adjacent neighbors:
- If an empty cell is adjacent to exactly three occupied cells, a cell will appear in that position in the next round.
- If a cell has one or fewer neighbors or four or more neighbors, the cell will disappear in the next round.
- All other cells retain their current state in the next round.

![Example of Game of Life Rules](Example.png)

<figcaption style="text-align: center; font-weight: bold;">
Figure 1 – Two iterations of the Game of Life. Empty cells where a new cell will appear in the next round (cells with three neighbors) are indicated by dotted lines. Cells that will die (having fewer than two or more than three neighbors) are shaded.
</figcaption>

# Declaration of the class, initial methods, constructors, and accessors :
The variables $H$ and $W$ will correspond to the size of the considered grid (height and width). 

The variable `config`, which is a vector of vectors of booleans, will contain the arrangement of the cells on the grid. More specifically, the boolean `config[i][j]` will be `true` if the cell in the $i$-th row and $j$-th column is occupied, and will be `false` otherwise.

The method:
```cpp
int neighbors(int i, int j) const;
``` 
returns the number of occupied cells that are neighbors of the cell in the $i$-th row and $j$-th column.

The 'iteration' method performs a single iteration of the Game of Life. After calling this function, the 'config' variable is updated to reflect the arrangement of cells in the next time step.

### Display and streams :
The method:

```cpp
void display(std::ostream & stream) const;
```
allows writing the configuration to a stream in the following format:
```cpp
4 4
.X.X
.X..
 X.XX
...X
```
The first line displays the height and width of the grid. 

This example corresponds to the initial state shown in Figure 1.

To use this method, another constructor is needed that takes an input stream (`std::ifstream`) as an argument and creates a `jeu_vie` object from a file with the previous format.

The constructor should read the file as the previous format:

1. The first line contains the height and width of the grid.
2. The following lines describe the grid configuration using `.` for empty cells and `X` for occupied cells.

file : glider.dat is a configuration of cells that moves while maintaining the same shape (to be precise, it moves one cell down and to the right every 4 iterations).

# A more complex development based on the `<random>` library:

Recall that if `gen` is a variable of type `std::mt19937` and `X` is a variable of type `std::bernoulli_distribution` initialized with the value $p$, then calling `X(gen)` returns a random value drawn from a Bernoulli distribution with parameter $p$. This uses the `<random>` library, which is available by compiling with the `-std=c++11` option.

Here is an example of how it can be used:

```cpp
#include <random>

std::mt19937 gen; // Random number generator
std::bernoulli_distribution X(p); // Bernoulli distribution with parameter p

// To generate a random value
bool random_value = X(gen);

```

Next, we need a constructor that takes two integers $H$ and $L$, a parameter $p$, and a reference to a generator $G$, and randomly fills a grid of size $H \times L$ with Bernoulli variables with parameter $p$.

The method `occupied_cells_count` returns the number of occupied cells among the $H \times W$ cells of the grid.

Let's calculate, for each value of $p$ in the set $\{0.1, 0.2, \dots, 0.9\}$, the average number of occupied cells after 100 iterations of the Game of Life. This average will be computed starting from 100 initial conditions randomly drawn independently with Bernoulli distributions with parameter $p$. For example, let's choose a grid size of $15 \times 25$.

A program that calculates (using the Monte Carlo method) the average density of cells on a $15 \times 25$ grid after 100 iterations of the Game of Life, depending on the initial density.

The approximate results are as follows:

- $p = 0.1$; Average number of cells: 9
- $p = 0.2$; Average number of cells: 21
- $p = 0.3$; Average number of cells: 23
- $p = 0.4$; Average number of cells: 23
- $p = 0.5$; Average number of cells: 23
- $p = 0.6$; Average number of cells: 21
- $p = 0.7$; Average number of cells: 13
- $p = 0.8$; Average number of cells: 4
- $p = 0.9$; Average number of cells: 0.5

The cell density is roughly the same for $p$ between 0.2 and 0.6, but it drops significantly if there are initially too many or too few cells.

We can test for different dimensions to observe this, but it requires parallelism or parallel computation due to the large number of loops involved.


# Visualization part :
```cpp 
std::vector<std::tuple<int, int, std::string>> get_occupied_cells() const;
```

This accessor allows us to retrieve both occupied and unoccupied cells. I have also added a tuple that contains a string as the third parameter, which was useful later in my Python script for visualization. Although we could use a structure instead, I preferred to use a tuple with int, int, and string to keep the code shorter.