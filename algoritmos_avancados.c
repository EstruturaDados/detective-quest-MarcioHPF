#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala (nó da árvore binária)
struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
};

// Cria uma nova sala com o nome informado
struct Sala* criarSala(const char *nome) {
    struct Sala *novaSala = (struct Sala*) malloc(sizeof(struct Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Permite o jogador explorar a mansão de forma interativa
void explorarSalas(struct Sala *atual) {
    char escolha;

    // Chega em uma sala sem saída
    while (atual != NULL) {
        printf("\nVocê está em: %s\n", atual->nome);

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho! Você chegou a um cômodo sem saídas.\n");
            break;
        }

        printf("Escolha um caminho:\n");
        if (atual->esquerda != NULL)
            printf("  [e] Ir para a esquerda (%s)\n", atual->esquerda->nome);
        if (atual->direita != NULL)
            printf("  [d] Ir para a direita (%s)\n", atual->direita->nome);
        printf("  [s] Sair da exploração\n");

        printf("Opção: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Não há caminho à esquerda!\n");
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("Não há caminho à direita!\n");
        } 
        else if (escolha == 's' || escolha == 'S') {
            printf("Saindo da exploração...\n");
            break;
        } 
        else {
            printf("Opção inválida! Escolha e, d ou s.\n");
        }
    }
}

// Função principal que cria a árvore (mapa fixo da mansão)
int main() {
    /*
        Estrutura do mapa da mansão (exemplo):

                   Hall de Entrada
                  /               \
         Sala de Estar         Cozinha
          /       \              /     \
    Biblioteca  Garagem      Despensa  Jardim
        /   \                              \
   Quarto  Banheiro                         Estufa
    
    */

    struct Sala *hall = criarSala("Hall de Entrada");
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Cozinha");

    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Garagem");

    hall->direita->esquerda = criarSala("Despensa");
    hall->direita->direita = criarSala("Jardim");

    hall->esquerda->esquerda->esquerda = criarSala("Quarto");
    hall->esquerda->esquerda->direita = criarSala("Banheiro"); 

    hall->direita->direita->esquerda = criarSala("Estufa"); 

    printf("=== DETECTIVE QUEST - EXPLORAÇÃO DA MANSÃO ===\n");
    explorarSalas(hall);

    // Libera memória alocada
    free(hall->direita->direita->esquerda);
    free(hall->esquerda->esquerda->esquerda);
    free(hall->esquerda->esquerda->direita);
    free(hall->esquerda->esquerda);
    free(hall->esquerda->direita);
    free(hall->direita->esquerda);
    free(hall->direita->direita);
    free(hall->esquerda);
    free(hall->direita);
    free(hall);

    printf("\nExploração encerrada. Obrigado por jogar!\n");
    return 0;
}
