#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// // Estrutura do nó
// typedef struct no {
//     int chave;
//     int contador;           // número de cópias (frequência) dessa chave
//     struct no* esq;         // ponteiro para subárvore esquerda
//     struct no* dir;         // ponteiro para subárvore direita
// } NO, *PONT;


// Função para calcular a altura da árvore
int altura(PONT root) {
    if (root == NULL)
        return 0;
    int altEsq = altura(root->esq);
    int altDir = altura(root->dir);
    return (altEsq > altDir ? altEsq : altDir) + 1;
}

// Função para imprimir espaços
void printEspacos(int n) {
    for (int i = 0; i < n; i++)
        printf(" ");
}

// Função para imprimir um nível da árvore
void printNivel(PONT root, int nivel, int largura) {
    if (nivel == 1) {
        if (root == NULL) {
            printEspacos(largura);
            return;
        }
        char buf[20];
        sprintf(buf, "%d", root->chave);
        int len = strlen(buf);
        int pad = (largura - len) / 2;
        printEspacos(pad);
        printf("%s", buf);
        printEspacos(largura - len - pad);
    } else {
        if (root == NULL) {
            // Se o nó está ausente, imprimi espaços para os dois filhos
            printNivel(NULL, nivel - 1, largura);
            printNivel(NULL, nivel - 1, largura);
        } else {
            printNivel(root->esq, nivel - 1, largura);
            printNivel(root->dir, nivel - 1, largura);
        }
    }
}

// Função principal para imprimir a árvore no formato clássico
void printPretty(PONT root) {
    int h = altura(root);
    int maxNodes = (int)pow(2, h) - 1;
    // largura mínima de cada nó (pode ser ajustada)
    int largura = 4;
    
    // A largura total para o nível mais baixo:
    int totalWidth = maxNodes * largura;
    
    // Para cada nível, calcula o espaço entre nós
    for (int nivel = 1; nivel <= h; nivel++) {
        // Espaçamento entre nós neste nível:
        int espacoEntre = totalWidth / ((int)pow(2, nivel));
        printNivel(root, nivel, espacoEntre);
        printf("\n");
        
        // Impressão das linhas de conexão (exceto no último nível)
        if (nivel < h) {
            int numInterv = (int)pow(2, nivel - 1);
            for (int i = 0; i < espacoEntre/2; i++) {
                for (int j = 0; j < numInterv; j++) {
                    printEspacos(espacoEntre - i);
                    // Para cada nó, se existir filho à esquerda imprime '/', se existir filho à direita imprime '\'
                    if (root != NULL) { // Essa parte pode ser aprimorada para conectar os nós corretos
                        printf("/");
                        printEspacos(i * 2);
                        printf("\\");
                    } else {
                        printEspacos(espacoEntre + i * 2);
                    }
                    printEspacos(espacoEntre - i);
                }
                printf("\n");
            }
        }
    }
}
