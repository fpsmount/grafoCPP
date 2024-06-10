#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <limits.h>

int tamanho;
int matriz[100][100];
int escolha;

void menu(){
    system("cls");
    printf("\n---------- MENU DE GRAFO ----------");
    printf("\n- 1 TAMANHO DO GRAFO              -");
    printf("\n- 2 IMPRIMIR GRAFO                -");
    printf("\n- 3 INSERIR VALOR NA MATRIZ       -");
    printf("\n- 4 PREENCHER AUTOMATICO          -");
    printf("\n- 5 PERCORRER O GRAFO             -");
    printf("\n- 6 IDENTIFICAR MENOR CAMINHO     -");
    printf("\n- 7 SAIR                          -");
    printf("\n-----------------------------------\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);
}

void limparMatriz(){
    for (int linha = 0; linha < tamanho; linha++){
        for (int coluna = 0; coluna < tamanho; coluna++){
            matriz[linha][coluna] = 0;
        }
    }
}

void imprimirMatriz(){
    printf("\n");
    for (int linha = 0; linha < tamanho; linha++){
        for (int coluna = 0; coluna < tamanho; coluna++){
            printf("%d   ", matriz[linha][coluna]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Pressione qualquer tecla para prosseguir.");
    getch();
}

void setarValor(int x, int y, int z){
    matriz[x][y] = z;
    printf("O valor %d foi gravado na matriz.\n", z);
    printf("Pressione qualquer tecla para prosseguir.");
    getch();
}

void preencherMatriz(){
    srand(time(NULL));
    for (int linha = 0; linha < tamanho; linha++){
        for (int coluna = 0; coluna < tamanho; coluna++){
            if(linha != coluna){
                int valor = rand() % 8 + 1;
                matriz[linha][coluna] = valor;
            }
        }
    }
    printf("Matriz preenchida automaticamente com sucesso!\n");
    printf("Pressione qualquer tecla para prosseguir.");
    getch();
}

void percorreGrafo(int v, int visitado[]){
    visitado[v] = 1;
    printf("%d   ", v);

    for (int i = 0; i < tamanho; i++){
        if (matriz[v][i] != 0 && !visitado[i]){
            percorreGrafo(i, visitado);
        }
    }
}

void percorrido(int v){
    int visitado[tamanho];
    for (int i = 0; i < tamanho; i++){
        visitado[i] = 0;
    }
    percorreGrafo(v, visitado);
}

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < tamanho; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf("%d ", j);
}

void printSolution(int dist[], int n, int parent[], int src) {
    printf("Vertice\t Distancia\tCaminho");
    for (int i = 0; i < tamanho; i++) {
        if (i != src) {
            printf("\n%d -> %d\t\t%d\t\t%d ", src, i, dist[i], src);
            printPath(parent, i);
        }
    }
    printf("\nPressione qualquer tecla para prosseguir.");
    getch();
}

void dijkstra(int grafo[100][100], int src) {
    int dist[tamanho];
    int sptSet[tamanho];
    int parent[tamanho];

    for (int i = 0; i < tamanho; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < tamanho - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        for (int v = 0; v < tamanho; v++) {
            if (!sptSet[v] && grafo[u][v] && dist[u] != INT_MAX
                && dist[u] + grafo[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + grafo[u][v];
            }
        }
    }

    printSolution(dist, tamanho, parent, src);
}

int main(){
    do {
        menu();
        if(escolha == 1){
            system("cls");
            printf("Informe o tamanho do grafo: ");
            scanf("%d", &tamanho);
            limparMatriz();
            printf("Grafo inicializado com sucesso! (Tamanho: %d)\n", tamanho);
            printf("Pressione qualquer tecla para prosseguir.");
            getch();
        } else if (escolha == 2){
            imprimirMatriz();
        } else if (escolha == 3){
            int coluna, linha, valor;
            printf("Digite a linha que voce deseja inserir algum valor: ");
            scanf("%d", &linha);
            if(linha >= tamanho){
                printf("A linha nao pode exceder o tamanho!!");
                getch();
                system("cls");
                continue;
            }
            printf("Digite a coluna que voce deseja inserir algum valor: ");
            scanf("%d", &coluna);
            if (coluna >= tamanho){
                printf("A coluna nao pode exceder o tamanho!!\n");
                getch();
                system("cls");
                continue;
            }
            if(linha == coluna){
                printf("A linha e a coluna nao podem ter os mesmos valores!");
                getch();
                system("cls");
            } else {
                printf("Digite o valor de [%d][%d]: ", linha, coluna);
                scanf("%d", &valor);
                setarValor(linha, coluna, valor);
            }
        } else if (escolha == 4){
            preencherMatriz();
        } else if (escolha == 5){
            int verticeInicial;
            printf("Digite o vertice inicial para iniciar: \n");
            scanf("%d", &verticeInicial);
            if(verticeInicial >= tamanho){
                printf("O vertice inicial nao pode exceder o tamanho!");
                printf("\n");
                printf("Pressione qualquer tecla para prosseguir.");
                getch();
            } else {
                printf("Percorrendo o grafo a partir do vertice: %d\n", verticeInicial);
                percorrido(verticeInicial);
                printf("\n");
                printf("Pressione qualquer tecla para prosseguir.");
                getch();
            }
        } else if (escolha == 6){
            int verticeInicial;
            printf("Digite o vertice inicial para identificar o menor caminho: \n");
            scanf("%d", &verticeInicial);
            if(verticeInicial >= tamanho){
                printf("O vertice inicial nao pode exceder o tamanho!");
                printf("\n");
                printf("Pressione qualquer tecla para prosseguir.");
                getch();
            } else {
                dijkstra(matriz, verticeInicial);
            }
        }
    } while(escolha != 7);
}
