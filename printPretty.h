#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Função principal para exibir a árvore visualmente
void printPrettyTree(PONT root);

// Função para calcular a altura da árvore
int treeHeight(PONT root);

// Função auxiliar para preencher o buffer com os nós e as barras
void fillBuffer(PONT root, int level, int left, int right, char **buffer);

