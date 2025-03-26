# PT-BR
## Solucionador para o Problema do Caixeiro Viajante (TSP) em C

Este programa em C implementa duas abordagens para resolver o Problema do Caixeiro Viajante (TSP):

1.  **Solução Precisa (Força Bruta):** Calcula a rota mais curta possível ao tentar todas as ordenações possíveis de cidades. Este método garante encontrar a solução ótima, mas tem uma complexidade de tempo de O(n!), tornando-o computacionalmente caro para um grande número de cidades (recomendado para até 10 cidades).

2.  **Solução Imprecisa (Heurística do Vizinho Mais Próximo):** Fornece uma solução mais rápida e aproximada, visitando iterativamente a cidade não visitada mais próxima. Este método tem uma complexidade de tempo menor, mas não garante a solução ótima (recomendado para um número maior de cidades).

## Arquivos

O programa lê as coordenadas das cidades dos seguintes arquivos de texto:

* `maranhao10.txt`: Contém as coordenadas para 10 cidades.
* `berlin52.txt`: Contém as coordenadas para 52 cidades.
* `att48.txt`: Contém as coordenadas para 48 cidades.

Cada linha nesses arquivos deve conter dois inteiros separados por um espaço, representando as coordenadas x e y de uma cidade.

## Como Compilar e Executar

1.  **Salvar o código C:** Salve o código C fornecido como um arquivo `.c` (por exemplo, `tsp_solver.c`).
2.  **Compilar:** Abra um terminal ou prompt de comando e use um compilador C (como o GCC) para compilar o código:

    ```bash
    gcc tsp_solver.c -o tsp_solver -lm
    ```

    A flag `-lm` é necessária para vincular a biblioteca matemática para a função `sqrt()`.

3.  **Executar:** Execute o programa compilado:

    ```bash
    ./tsp_solver
    ```

## Uso

1.  O programa primeiro solicitará que você escolha um arquivo contendo as coordenadas das cidades, inserindo o número correspondente:

    ```
    Escolha o arquivo:
    1:maranha10
    2:berlin52
    3:att48
    ```

2.  Em seguida, será solicitado que você insira o número de cidades que compõem a rota. Isso deve corresponder ao número de cidades no arquivo escolhido.

    ```
    Número de cidades que compõem a rota:
    ```

3.  Finalmente, será solicitado que você escolha entre um resultado preciso e um impreciso:

    ```
    Resultado preciso (não recomendado para rotas com mais de 10 cidades):1
    Resultado impreciso (recomendado para rotas com grande número de cidades):2
    ```

    * Digite `1` para usar a abordagem de força bruta.
    * Digite `2` para usar a heurística do vizinho mais próximo.

4.  O programa calculará e exibirá a distância total da rota e a ordem das cidades na rota com base na sua escolha.

## Descrição do Código

### `calculateDistance(int x1, int y1, int x2, int y2)`

Calcula a distância euclidiana entre duas cidades, dadas suas coordenadas x e y.

### `sumDistances(int distanceMatrix[][cityAmount], int city[], int n)`

Calcula a distância total de uma determinada rota de cidades com base em uma matriz de distâncias pré-calculada.

### `permute(int matrix[][cityAmount], int cities[], int beginning, int end, int *shortestDistance, int bestSequence[])`

Uma função recursiva que gera todas as permutações possíveis das cidades para encontrar a rota mais curta usando a abordagem de força bruta.

### `takeUserInput(int fileAmount)`

Solicita ao usuário que selecione um arquivo e valida a entrada, garantindo que um número de arquivo válido seja escolhido.

### `main()`

A função principal do programa:

* Lida com a entrada do usuário para a seleção de arquivos e o número de cidades.
* Lê as coordenadas das cidades do arquivo escolhido.
* Calcula a matriz de distâncias entre todos os pares de cidades.
* Com base na escolha do usuário, realiza uma das seguintes ações:
    * Chama a função `permute` para encontrar a rota mais curta precisa.
    * Implementa a heurística do vizinho mais próximo para encontrar uma rota mais curta aproximada.
* Imprime a distância total e a ordem das cidades na rota calculada.
* Libera a memória alocada dinamicamente.

## Observação

* A solução precisa usando força bruta tem uma complexidade de tempo muito alta e só deve ser usada para um pequeno número de cidades (idealmente menor ou igual a 10) para evitar tempos de execução extremamente longos.
* A solução imprecisa usando a heurística do vizinho mais próximo é muito mais rápida, mas não garante a solução ótima. A qualidade da solução pode variar dependendo da cidade inicial.

# EN
## Traveling Salesman Problem (TSP) Solver in C

This C program implements two approaches to solve the Traveling Salesman Problem (TSP):

1.  **Precise Solution (Brute Force):** Calculates the shortest possible route by trying all possible orderings of cities. This method is guaranteed to find the optimal solution but has a time complexity of O(n!), making it computationally expensive for a large number of cities (recommended for up to 10 cities).

2.  **Imprecise Solution (Nearest Neighbor Heuristic):** Provides a faster, approximate solution by iteratively visiting the nearest unvisited city. This method has a lower time complexity but does not guarantee the optimal solution (recommended for a larger number of cities).

## Files

The program reads city coordinates from the following text files:

* `maranhao10.txt`: Contains coordinates for 10 cities.
* `berlin52.txt`: Contains coordinates for 52 cities.
* `att48.txt`: Contains coordinates for 48 cities.

Each line in these files should contain two integers separated by a space, representing the x and y coordinates of a city.

## How to Compile and Run

1.  **Save the C code:** Save the provided C code as a `.c` file (e.g., `tsp_solver.c`).
2.  **Compile:** Open a terminal or command prompt and use a C compiler (like GCC) to compile the code:

    ```bash
    gcc tsp_solver.c -o tsp_solver -lm
    ```

    The `-lm` flag is necessary to link the math library for the `sqrt()` function.

3.  **Run:** Execute the compiled program:

    ```bash
    ./tsp_solver
    ```

## Usage

1.  The program will first prompt you to choose a file containing the city coordinates by entering the corresponding number:
    ```
    Choose the file:
    1:maranha10
    2:berlin52
    3:att48
    ```
2.  Next, you will be asked to enter the number of cities that make up the route. This should match the number of cities in the chosen file.
    ```
    Amount of cities that make up the route:
    ```
3.  Finally, you will be asked to choose between a precise and an imprecise result:
    ```
    Precise result (not recommended for routes with more than 10 cities):1
    Imprecise result (recommended for routes with large amounts of cities):2
    ```
    * Enter `1` to use the brute-force approach.
    * Enter `2` to use the nearest neighbor heuristic.

4.  The program will then calculate and display the total distance of the route and the order of the cities in the route based on your choice.

## Code Description

### `calculateDistance(int x1, int y1, int x2, int y2)`

Calculates the Euclidean distance between two cities given their x and y coordinates.

### `sumDistances(int distanceMatrix[][cityAmount], int city[], int n)`

Calculates the total distance of a given route of cities based on a pre-calculated distance matrix.

### `permute(int matrix[][cityAmount], int cities[], int beginning, int end, int *shortestDistance, int bestSequence[])`

A recursive function that generates all possible permutations of the cities to find the shortest route using the brute-force approach.

### `takeUserInput(int fileAmount)`

Prompts the user to select a file and validates the input, ensuring a valid file number is chosen.

### `main()`

The main function of the program:

* Handles user input for file selection and the number of cities.
* Reads city coordinates from the chosen file.
* Calculates the distance matrix between all pairs of cities.
* Based on the user's choice, either:
    * Calls the `permute` function to find the precise shortest route.
    * Implements the nearest neighbor heuristic to find an approximate shortest route.
* Prints the total distance and the order of cities in the calculated route.
* Frees the dynamically allocated memory.

## Note

* The precise solution using brute force has a very high time complexity and should only be used for a small number of cities (ideally less than or equal to 10) to avoid extremely long execution times.
* The imprecise solution using the nearest neighbor heuristic is much faster but does not guarantee the optimal solution. The quality of the solution can vary depending on the starting city.
