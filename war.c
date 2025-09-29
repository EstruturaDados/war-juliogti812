#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para armazenar os dados dos territórios
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios dinamicamente
Territorio* cadastrarTerritorios(int n) {
    Territorio *mapa = (Territorio*)calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastro do Territorio %d ===\n", i+1);
        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);
        printf("Cor (dono): ");
        scanf(" %9[^\n]", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    return mapa;
}

// Função para exibir todos os territórios
void exibirTerritorios(Territorio *mapa, int n) {
    printf("\n--- ESTADO ATUAL DOS TERRITORIOS ---\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque (usa ponteiros para atacante e defensor)
void atacar(Territorio *atacante, Territorio *defensor) {
    // Impedir ataque do próprio território
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Voce nao pode atacar um territorio da mesma cor!\n");
        return;
    }

    // Rolagem de dados (1 a 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n",
           dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");
        // Transferir dono e metade das tropas do atacante
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // metade das tropas do atacante
        atacante->tropas -= defensor->tropas;    // o atacante perde as tropas transferidas
    } else {
        printf("Defensor resistiu. Atacante perde 1 tropa.\n");
        if (atacante->tropas > 0)
            atacante->tropas--;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // inicializa a aleatoriedade

    int n;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &n);

    Territorio *mapa = cadastrarTerritorios(n);

    int opcao;
    do {
        exibirTerritorios(mapa, n);

        printf("\nMENU:\n");
        printf("1 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int iAtacante, iDefensor;
            printf("Escolha o indice do territorio atacante: ");
            scanf("%d", &iAtacante);
            printf("Escolha o indice do territorio defensor: ");
            scanf("%d", &iDefensor);

            if (iAtacante >= 0 && iAtacante < n &&
                iDefensor >= 0 && iDefensor < n) {
                atacar(&mapa[iAtacante], &mapa[iDefensor]);
            } else {
                printf("Indice invalido!\n");
            }
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    printf("Memoria liberada. Fim do programa.\n");
    return 0;
}
