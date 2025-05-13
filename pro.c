#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void readGraph(int **graph, int N) {
    printf("Enter the adjacency matrix (%dx%d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
}

int tsp(int setOfCities, int city, int **dp, int **graph, int **parent, int N, int startCity) {
    if (setOfCities == (1 << N) - 1) {
        return graph[city][startCity];
    }

    if (dp[city][setOfCities] != -1) {
        return dp[city][setOfCities];
    }

    int answer = INT_MAX;

    for (int nextCity = 0; nextCity < N; nextCity++) {
        if ((setOfCities & (1 << nextCity)) == 0) {
            int newAnswer = graph[city][nextCity] + tsp(setOfCities | (1 << nextCity), nextCity, dp, graph, parent, N, startCity);
            if (newAnswer < answer) {
                answer = newAnswer;
                parent[city][setOfCities] = nextCity;
            }
        }
    }

    dp[city][setOfCities] = answer;
    return answer;
}

void printTour(int startCity, int **dp, int **parent, FILE *outputFile, int N) {
    int currentCity = startCity;
    int setOfCities = 1 << startCity;
    fprintf(outputFile, "Optimal Tour:\n");

    do {
        fprintf(outputFile, "%c ", 'a' + currentCity);
        currentCity = parent[currentCity][setOfCities];
        setOfCities |= (1 << currentCity);
    } while (currentCity != startCity);

    fprintf(outputFile, "%c\n", 'a'); // Complete the cycle by returning to starting city
}

int main() {
    int N;
    printf("Enter the number of cities: ");
    scanf("%d", &N);

    // Allocate memory for graph, dp, and parent matrices
    int *graph = (int *)malloc(N * sizeof(int *));
    int *dp = (int *)malloc(N * sizeof(int *));
    int *parent = (int *)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        graph[i] = (int *)malloc(N * sizeof(int));
        dp[i] = (int *)malloc((1 << N) * sizeof(int));
        parent[i] = (int *)malloc((1 << N) * sizeof(int));
    }

    // Input adjacency matrix
    readGraph(graph, N);

    // Ask for the starting city
    char startCityChar;
    printf("Enter the starting city (e.g., a, b, c, ...): ");
    scanf(" %c", &startCityChar);

    // Convert character to index
    int startCity = startCityChar - 'a';

    // Validate the starting city index
    if (startCity < 0 || startCity >= N) {
        printf("Invalid starting city.\n");
        return 1;
    }

    // Write the adjacency matrix and starting city to a file
    FILE *inputFile = fopen("input_graph.txt", "w");
    if (inputFile == NULL) {
        perror("Error opening input_graph.txt");
        return 1;
    }

    // Write the starting city
    fprintf(inputFile, "%c\n", startCityChar);

    // Write the adjacency matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(inputFile, "%d ", graph[i][j]);
        }
        fprintf(inputFile, "\n");
    }
    fclose(inputFile);

    // Initialize the dp and parent arrays
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < (1 << N); j++) {
            dp[i][j] = -1;
            parent[i][j] = -1;
        }
    }

    // Compute the minimum cost using Dynamic Programming
    int minCost = tsp(1 << startCity, startCity, dp, graph, parent, N, startCity);

    // Write the minimum cost to output
    printf("The minimum cost using Dynamic Programming is %d\n", minCost);

    // Write the result to a file
    FILE *outputFile = fopen("pkpk.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening pkpk.txt");
        return 1;
    }

    fprintf(outputFile, "%d\n", minCost);

    // Print and store the optimal tour
    printTour(startCity, dp, parent, outputFile, N);

    fclose(outputFile);

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(graph[i]);
        free(dp[i]);
        free(parent[i]);
    }
    free(graph);
    free(dp);
    free(parent);

    return 0;
}
