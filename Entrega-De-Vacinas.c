#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// General variable to store the number of cities that make up a route.
int cityAmount;

// Function to calculate the distance between two cities on the Cartesian plane.
// Reads the x and y coordinates of two cities as integers.
// Returns the distance between them as an integer (the square root).
int calculateDistance(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

// Function to calculate the total distance of a specific route of cities.
// Reads the distance matrix between the cities, an array representing the order of cities on the route, and the total number of cities.
// Returns the total distance of the route as an integer.
int sumDistances(int distanceMatrix[][cityAmount], int city[], int n)
{
    // Initializes the total distance of the route as zero.
    int distance = 0;

    // Iterates over the cities in the given order, adding up the distance between adjacent cities.
    for (int i = 0; i < n - 1; i++)
    {
        // Adds up the distance between the current city (city[i]) and the next city (city[i + 1]) to the total distance.
        distance += distanceMatrix[city[i]][city[i + 1]];
    }

    // Adds up the distance between the last city and back to the first city to finish the cycle.
    distance += distanceMatrix[city[n - 1]][city[0]];

    // Returns the total distance of the route.
    return distance;
}

// Recursive function to generate all possible permutations of the cities and find the route with the shortest distance (brute force).
// Reads the matrix of distances, an array representing the current order of cities, the indexes of beginning and end of the permutation, a pointer to the shortest distance found up to this point, and an array to store the best sequence of cities.
void *permute(int matrix[][cityAmount], int cities[], int beginning, int end, int *shortestDistance, int bestSequence[])
{
    // Base case of recursion: when 'beginning' reaches 'end', a complete permutation was generated.
    if (beginning == end)
    {
        // Calculates the total distance of the route for the current permutation.
        int tempDistance = sumDistances(matrix, cities, end + 1);
        // Verifies if the current distance is shorter than the shortest distance found up to this point.
        if (tempDistance < *shortestDistance)
        {
            // Updates the shortest found distance.
            *shortestDistance = tempDistance;
            // Copies the sequence of cities from the current permutation to the best sequence array.
            for (int k = 0; k < cityAmount; k++)
            {
                bestSequence[k] = cities[k];
            }
        }
    }
    // Recursive case: generates permutations by swapping each city in the non-fixed part with the city in the 'beginning' position.
    else
    {
        for (int i = beginning; i <= end; i++)
        {
            // Swaps the city in the 'beginning' position with the city in the 'i' position.
            int temp = cities[beginning];
            cities[beginning] = cities[i];
            cities[i] = temp;

            // Calls the permute function recursively to the next position (beginning + 1).
            permute(matrix, cities, beginning + 1, end, shortestDistance, bestSequence);

            // Restore the 'cities' array to the state before swapping (backtracking) to generate other permutations.
            temp = cities[beginning];
            cities[beginning] = cities[i];
            cities[i] = temp;
        }
    }
}

// Function to get the user's file choice from standard input.
// Receive the total number of available files as a parameter.
// Returns the number corresponding to the file choice made by the user.
int takeUserInput(int fileAmount)
{
    int choice;
    printf("Choose the file:\n1:maranha10\n2:berlin52\n3:att48\n");
    // Reads an integer from standard input.
    if (scanf("%d", &choice) == 1)
    {
        // Checks if the user's choice is within the valid range of files.         
        if (choice >= 1 && choice <= fileAmount)
        {
            return choice;
        }
        else
        {
            // Informs the user about the invalid choice and calls the function recursively to try again.
            printf("Invalid choice. Please enter a number between 1 and %d.\n", fileAmount);
            return takeUserInput(fileAmount); // Recursion on invalid input
        }
    }
    else
    {
        // Informa o usuário sobre a entrada inválida (não inteiro) e limpa o buffer de entrada.
        // Informs the user about the invalid (non integer) input and clears the input buffer.
        printf("Invalid input. Please enter an integer.\n");
        // Limpa o buffer de entrada para evitar loops infinitos com entradas não numéricas.
        // Clears the input buffer to avoid infinite loops with non-numeric inputs.
        while (getchar() != '\n')
            ;
        return takeUserInput(fileAmount); // Recursion on invalid input
    }
}

int main()
{
    // Declares a pointer to the cities input file.
    FILE *citiesInput;
    // Declares a buffer for reading lines from the file.
    char buffer[255];
    // Declares a variable to store the user's file choice.
    int fileChoice;

    // Calls the function to get the user's file choice.
    fileChoice = takeUserInput(3);

    // Opens the file corresponding to the user's choice.
    switch (fileChoice)
    {
    case 1:
        citiesInput = fopen("maranhao10.txt", "r");
        break;
    case 2:
        citiesInput = fopen("berlin52.txt", "r");
        break;
    case 3:
        citiesInput = fopen("att48.txt", "r");
        break;
    default:
        printf("Invalid file choice.\n");
        return 1; // Indicates an error in file choice.
    }

    // Checks if the file was opened correctly.    
    if (citiesInput == NULL)
    {
        perror("Error opening file");
        return 1; // Indicates an error when opening the file.
    }

    // Asks the user for the number of cities on the route.    
    printf("Amount of cities that make up the route:");
    scanf("%d", &cityAmount);

    // Defines a struct to represent the order of cities on the route.    
    struct cityOrder
    {
        int orderOfCities[cityAmount];
    };

    // Dynamically allocates memory to store city coordinates (list of lists of integers).
    int **listOfCities = NULL;
    listOfCities = (int **)malloc(sizeof(int *) * cityAmount);
    // Checks if memory allocation was successful.
    if (listOfCities == NULL)
    {
        perror("Memory allocation failed.");
        fclose(citiesInput);
        return -1; // Indicates failure in memory allocation
    }

    // Allocates memory for the x and y coordinates of each city.     
    for (int i = 0; i < cityAmount; i++)
    {
        listOfCities[i] = (int *)malloc(sizeof(int) * 2);
        // Checks if memory allocation for each city was successful.
        if (listOfCities[i] == NULL)
        {
            perror("Memory allocation failed");
            fclose(citiesInput);
            // Frees memory allocated to previous cities in case of failure.
            for (int j = 0; j < i; j++)
            {
                free(listOfCities[j]);
            }
            free(listOfCities);
            return -1; // Indicates failure in memory allocation
        }
    }

    // Reads the coordinates of each city from the file and stores them in the listOfCities array.
    int indexOfY;
    char *takeCoordinates;
    for (int i = 0; i < cityAmount; i++)
    {
        // Reads a line from the file into the buffer.        
        if (fgets(buffer, sizeof(buffer), citiesInput) != NULL)
        {
            // Looks for the space character to separate the x and y coordinates.
            char *space = strchr(buffer, ' ');
            if (space != NULL)
            {
                *space = '\0'; // Ends the first part of the string in space.
                takeCoordinates = buffer; // Points to the beginning of the string (x coordinate).
                listOfCities[i][0] = atoi(takeCoordinates); // Converts the x coordinate to an integer.
                takeCoordinates = space + 1; // Points to the character after the space (start of the y coordinate).
                listOfCities[i][1] = atoi(takeCoordinates); // Converts the y coordinate to an integer.
            }
            else
            {
                fprintf(stderr, "Invalid format in input file at line %d\n", i + 1);
            }
        }
        else
        {
            fprintf(stderr, "Error reading line %d from input file\n", i + 1);
        }
    }

    int choice;
    printf("Precise result (not recommended for routes with more than 10 cities):1\nImprecise result (recommended for routes with large amounts of cities):2\n");
    scanf("%d", &choice);
    // If the user chooses option 1, the program will calculate the accurate solution using brute force (permuting all possible routes).
    if (choice == 1)
    {
        // Creates a matrix to store the distances between pair of cities.
        int distanceMatrix[cityAmount][cityAmount];
        // Fills the distance matrix calculating the distance between each pair of cities.
        for (int i = 0; i < cityAmount; i++)
        {
            for (int j = 0; j < cityAmount; j++)
            {
                distanceMatrix[i][j] = calculateDistance(listOfCities[i][0], listOfCities[i][1], listOfCities[j][0], listOfCities[j][1]);
            }
        }
        int matrixLength = cityAmount;
        // Creates an array to represent cities (indexes from 0 to cityAmount -1).
        int cities[cityAmount];
        // Creates an array to store the best found sequence of cities.        
        int sequenceOfCities[cityAmount];
        // Initializes the 'cities' array with the indexes of the cities.
        for (int i = 0; i < cityAmount; i++)
        {
            cities[i] = i;
        }
        // Initializes the shortest distance with the highest possible value for an integer.
        int shortestDistance = __INT_MAX__;

        // Calls the permute function to find the shortest distance and the best sequence of cities.
        // The permutation starts from the second city (index 1) because the first city is considered the fixed starting point of the cycle.
        permute(distanceMatrix, cities, 1, cityAmount - 1, &shortestDistance, sequenceOfCities);
        // Creates a struct to store the final sequence of cities.
        struct cityOrder citySequence;
        citySequence.orderOfCities[cityAmount];
        // Copies the best found sequence of cities to the struct.        
        for (int i = 0; i < cityAmount; i++)
        {
            citySequence.orderOfCities[i] = sequenceOfCities[i];
        }

        // Prints the shortest possible distance found.
        printf("Shortest possible distance:%dkm \n", shortestDistance);
        // Prints the best sequence of cities found.        
        printf("Best sequence of cities: ");
        for (int i = 0; i < matrixLength; i++)
        {
            printf("%d ", citySequence.orderOfCities[i] + 1); // Adds up 1 to show the number of the cities starting from 1.
        }
        printf("%d", 1); // Completes the cycle going back to the first city (cidade 1).
    }

    // If the user chooses option 2, the program will use a greedy heuristic (nearest neighbor) to find an approximate solution.
    else if (choice == 2)
    {
        unsigned long long int totalDistance = 0, shortestDistanceBetweenCities = 1000000000000, distance;
        int visitedCities = 1, destinationCity, originCity = 0; // Starts from city 0.
        int firstCity = originCity; // Saves the first city to return at the end.
        int lastVisitedCity;
        int listOfVisits[cityAmount];
        // Initializes the list of visited cities with 0 (no visited city initially).
        for (int i = 0; i < cityAmount; i++)
        {
            listOfVisits[i] = 0;
        }
        listOfVisits[0] = originCity; // Marks the starting city as visited.
        int visitIndex = 1, wasVisited = 0;

        // While not all cities were visited.        
        while (visitedCities != cityAmount)
        {
            // Iterates over every city to find the one closest to the current city.            
            for (int j = 0; j < cityAmount; j++)
            {
                // Calculates the distance between the current city ('originCity') and 'j' city.
                distance = calculateDistance(listOfCities[originCity][0], listOfCities[originCity][1], listOfCities[j][0], listOfCities[j][1]);

                // Verifies if the distance is shorter than the shortest distance found up to this point, if 'j' city isn't the current city ('origin city'), and if it isn't the last visited city (to avoid going back immediately).
                if ((distance < shortestDistanceBetweenCities) && (j != originCity) && (j != lastVisitedCity))
                {
                    // Checks if 'j' city was already visited.                    
                    for (int k = 0; k < cityAmount; k++)
                    {

                        if (j == listOfVisits[k])
                        {
                            wasVisited = 1;  // Marks as visited.
                        }
                    }
                    // If 'j' city wasn't visited.                    
                    if (wasVisited == 0)
                    {
                        shortestDistanceBetweenCities = distance; // Updates the shortest distance.
                        destinationCity = j; // Defines 'j' city as the next destination.
                    }
                    else
                    {
                        wasVisited = 0; // Resets the flag for the next iteration.
                        continue; // Skips to the next 'j' city.
                    }
                }
            }

            wasVisited = 0;  // Guarantees that the flag is reset for the next search.

            listOfVisits[visitIndex] = destinationCity; // Adds the destined city to the list of visits.
            visitIndex++;

            lastVisitedCity = destinationCity; // Updates the last visited city.

            totalDistance += shortestDistanceBetweenCities; // Adds up traveled distance to total distance.

            originCity = destinationCity; // Defines the destined city as the new city of origin.

            visitedCities++; // Increments the counter of visited cities.

            shortestDistanceBetweenCities = 10000000000000000; // Resets the shortest distance for the next search.
        }

        // Calculates the distance from the last visited city to the first city to finish the cycle.        
        unsigned long long int lastOne = calculateDistance(listOfCities[firstCity][0], listOfCities[firstCity][1], listOfCities[lastVisitedCity][0], listOfCities[lastVisitedCity][1]);

        totalDistance += lastOne; // Adds up return distance to total distance.
        struct cityOrder citySequence;
        citySequence.orderOfCities[cityAmount];
        for (int i = 0; i < cityAmount; i++)
        {
            citySequence.orderOfCities[i] = listOfVisits[i];
        }
        printf("Total distance: %llukm", totalDistance);
        printf("\nOrder of cities: ");
        for (int i = 0; i < cityAmount; i++)
        {
            printf("%d ", citySequence.orderOfCities[i] + 1);
        }
        printf("%d", firstCity + 1); // Prints out the first city to finish the cycle.
    }
    // Closes the input file.
    fclose(citiesInput);
    // Frees the memory allocated for city coordinates.    
    for (int i = 0; i < cityAmount; i++)
    {
        free(listOfCities[i]);
    }
    free(listOfCities);
    return 0; // Indica que o programa terminou com sucesso.
}