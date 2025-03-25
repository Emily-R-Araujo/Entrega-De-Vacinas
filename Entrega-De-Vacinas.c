#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int cityAmount;

// Creates a function to calculate the distance between two points.
int calculateDistance(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

int sumDistances(int distanceMatrix[][cityAmount], int city[], int n)
{
    int distance = 0;

    for (int i = 0; i < n - 1; i++)
    {
        distance += distanceMatrix[city[i]][city[i + 1]];
    }
    distance += distanceMatrix[city[n - 1]][city[0]];
    return distance;
}

// Uses the function above to calculate all possible sums of distances between cities, returning the sequence with the lowest distance.
void *permute(int matrix[][cityAmount], int cities[], int beginning, int end, int *lowestDistance, int bestSequence[])
{
    if (beginning == end)
    {
        int tempDistance = sumDistances(matrix, cities, end + 1);
        if (tempDistance < *lowestDistance)
        {
            *lowestDistance = tempDistance;
            for (int k = 0; k < cityAmount; k++)
            {
                bestSequence[k] = cities[k];
            }
        }
    }
    else
    {
        for (int i = beginning; i <= end; i++)
        {
            int temp = cities[beginning];
            cities[beginning] = cities[i];
            cities[i] = temp;

            permute(matrix, cities, beginning + 1, end, lowestDistance, bestSequence);

            temp = cities[beginning];
            cities[beginning] = cities[i];
            cities[i] = temp;
        }
    }
}

int main()
{
    // Chooses the file to open based on user input.
    FILE *citiesInput;
    char buffer[255];
    int file;
    printf("Choose the file:\n1:maranha10\n2:berlin52\n3:att48\n");
    scanf("%d", &file);

    if (file == 1)
    {
        citiesInput = fopen("maranhao10.txt", "r");
    }
    else if (file == 2)
    {
        citiesInput = fopen("berlin52.txt", "r");
    }
    else if (file == 3)
    {
        citiesInput = fopen("att48.txt", "r");
    } else {
        printf("No file matches the integer %d; please, try again.\n", file);
        return 0;
    }
    
    printf("Amount of cities that make up the route:");
    scanf("%d", &cityAmount);

    struct cityOrder
    {
        int orderOfCities[cityAmount];
    };

    // Creates a matrix with each city's coordinates.
    int **listOfCities = NULL;
    listOfCities = (int **)malloc(sizeof(int *) * cityAmount);
    if (listOfCities == NULL)
    {
        return -1;
    }

    for (int i = 0; i < cityAmount; i++)
    {
        listOfCities[i] = (int *)malloc(sizeof(int) * 2);
        if (listOfCities == NULL)
        {
            return -1;
        }
    }

    // Takes the coordinates from the chosen file to add to listOfCities matrix.
    int indexOfY;
    char *takeCoordinates;
    for (int i = 0; i < cityAmount; i++)
    {
        fgets(buffer, 255, citiesInput);
        for (int j = 0; j < 255; j++)
        {
            if (buffer[j] == ' ')
            {
                indexOfY = j;
                break;
            }
        }
        takeCoordinates = &buffer[0];
        listOfCities[i][0] = atoi(takeCoordinates);
        takeCoordinates = &buffer[indexOfY];
        listOfCities[i][1] = atoi(takeCoordinates);
    }

    int choice;
    printf("Precise result (not recommended for routes with more than 10 cities):1\nImprecise result (recommended for routes with large amounts of cities):2\n");
    scanf("%d", &choice);
    // Uses the permute function to calculate the best possible sequence, then returns the total distance.
    if (choice == 1)
    {
        int distanceMatrix[cityAmount][cityAmount];
        for (int i = 0; i < cityAmount; i++)
        {
            for (int j = 0; j < cityAmount; j++)
            {
                distanceMatrix[i][j] = calculateDistance(listOfCities[i][0], listOfCities[i][1], listOfCities[j][0], listOfCities[j][1]);
            }
        }
        int matrixLength = cityAmount;
        int cities[cityAmount];
        int sequenceOfCities[cityAmount];
        for (int i = 0; i < cityAmount; i++)
        {
            cities[i] = i;
        }
        int lowestDistance = __INT_MAX__;

        permute(distanceMatrix, cities, 1, cityAmount - 1, &lowestDistance, sequenceOfCities);
        struct cityOrder citySequence;
        citySequence.orderOfCities[cityAmount];
        for (int i = 0; i < cityAmount; i++)
        {
            citySequence.orderOfCities[i] = sequenceOfCities[i];
        }

        printf("Lowest possible distance:%dkm \n", lowestDistance);
        printf("Best sequence of cities: ");
        for (int i = 0; i < matrixLength; i++)
        {
            printf("%d ", citySequence.orderOfCities[i] + 1);
        }
        printf("%d", 1);
    }
    // Uses the logic from Dijkstra's algorithm to calculate the best sequence based on the immediately closest city, then returns the total distance.
    else if (choice == 2)
    {
        unsigned long long int totalDistance = 0, lowestDistanceBetweenCities = 1000000000000, distance;
        int visitedCities = 1, destinationCity, originCity = 0;
        int firstCity = originCity;
        int lastVisitedCity;
        int listOfVisits[cityAmount];
        for (int i = 0; i < cityAmount; i++)
        {
            listOfVisits[i] = 0;
        }
        listOfVisits[0] = originCity;
        int visitIndex = 1, wasVisited = 0;

        while (visitedCities != cityAmount)
        {
            for (int j = 0; j < cityAmount; j++)
            {
                distance = calculateDistance(listOfCities[originCity][0], listOfCities[originCity][1], listOfCities[j][0], listOfCities[j][1]);

                if ((distance < lowestDistanceBetweenCities) && (j != originCity) && (j != lastVisitedCity))
                {
                    for (int k = 0; k < cityAmount; k++)
                    {

                        if (j == listOfVisits[k])
                        {
                            wasVisited = 1;
                        }
                    }

                    if (wasVisited == 0)
                    {
                        lowestDistanceBetweenCities = distance;
                        destinationCity = j;
                    }
                    else
                    {
                        wasVisited = 0;
                        continue;
                    }
                }
            }

            wasVisited = 0;

            listOfVisits[visitIndex] = destinationCity;
            visitIndex++;

            lastVisitedCity = destinationCity;

            totalDistance += lowestDistanceBetweenCities;

            originCity = destinationCity;

            visitedCities++;

            lowestDistanceBetweenCities = 10000000000000000;
        }

        unsigned long long int lastOne = calculateDistance(listOfCities[firstCity][0], listOfCities[firstCity][1], listOfCities[lastVisitedCity][0], listOfCities[lastVisitedCity][1]);

        totalDistance += lastOne;
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
        printf("%d", firstCity + 1);
    }
    // End of program.
    fclose(citiesInput);
    for (int i = 0; i < cityAmount; i++)
    {
        free(listOfCities[i]);
    }
    free(listOfCities);
    return 0;
}