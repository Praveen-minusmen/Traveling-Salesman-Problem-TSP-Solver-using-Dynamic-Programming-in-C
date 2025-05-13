# Traveling-Salesman-Problem-TSP-Solver-using-Dynamic-Programming-in-C

This project provides a C implementation of the Traveling Salesman Problem (TSP) using dynamic programming and bitmasking. The program finds the minimum cost tour that visits all cities exactly once and returns to the starting city.

## Features

- **Dynamic Programming with Bitmasking:** Efficiently solves TSP for small to medium-sized graphs.
- **User Input:** Reads the number of cities, adjacency matrix, and starting city from the user.
- **File Output:** Saves the adjacency matrix, starting city, minimum cost, and optimal tour to files.
- **Tour Reconstruction:** Prints and saves the optimal tour path.

## Usage

1. **Compile the program:**
   ```sh
   gcc -o tsp_solver pro.c
   ```

2. **Run the program:**
   ```sh
   ./tsp_solver
   ```

3. **Follow the prompts:**
   - Enter the number of cities.
   - Enter the adjacency matrix (costs between cities).
   - Enter the starting city (as a lowercase letter, e.g., `a`, `b`, ...).

4. **Output:**
   - The minimum cost and optimal tour are displayed on the console.
   - The minimum cost and tour are saved to `pkpk.txt`.
   - The input graph and starting city are saved to `input_graph.txt`.

