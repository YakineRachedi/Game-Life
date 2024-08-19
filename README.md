The goal of this project is to program an implementation of the Game of Life. This "game" consists of the evolution of a set of cells placed on a grid. Specifically, we have a finite grid made up of empty cells and cells occupied by a living cell. The state of the grid evolves in discrete time steps according to the following rules:

The state (empty or occupied by a cell) of each grid cell in the next step is determined by its current state and the number of currently occupied neighboring cells among its 8 adjacent neighbors:
- If an empty cell is adjacent to exactly three occupied cells, a cell will appear in that position in the next round.
- If a cell has one or fewer neighbors or four or more neighbors, the cell will disappear in the next round.
- All other cells retain their current state in the next round.

![Example of Game of Life Rules](Example.png)

<figcaption style="text-align: center; font-weight: bold;">
Figure 1 – Two iterations of the Game of Life. Empty cells where a new cell will appear in the next round (cells with three neighbors) are indicated by dotted lines. Cells that will die (having fewer than two or more than three neighbors) are shaded.
</figcaption>