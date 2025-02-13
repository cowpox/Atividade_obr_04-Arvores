#include "printPretty.h"


// 4 - Função printPrettyTree: imprimir no formato de diagrama
//------------------------------------------------------------------------------
// Função para calcular a altura da árvore
int treeHeight(PONT root) {
    if(root == NULL)
        return 0;
    int leftH = treeHeight(root->esq);
    int rightH = treeHeight(root->dir);
    return (leftH > rightH ? leftH : rightH) + 1;
}

// Função recursiva para preencher o buffer com os nós e as barras
// Parâmetros:
// - root: nó atual
// - level: nível atual (começando em 0)
// - left e right: limites (colunas) onde o nó deve ser posicionado
// - buffer: matriz de caracteres para desenho
void fillBuffer(PONT root, int level, int left, int right, char **buffer) {
    if(root == NULL)
        return;
    
    // Linha onde o valor do nó será impresso
    int row = level * 2;
    // Cálculo da coluna central entre left e right
    int mid = (left + right) / 2;
    
    // Converte o valor do nó para string
    char val[10];
    sprintf(val, "%d", root->chave);
    int len = (int)strlen(val);
    // Posiciona o valor de forma centralizada
    int start = mid - len / 2;
    for (int i = 0; i < len; i++) {
        if(start + i >= 0 && start + i < right + 1)
            buffer[row][start + i] = val[i];
    }
    
    // Se existir filho à esquerda, desenha a barra e preenche recursivamente
    if(root->esq != NULL) {
        buffer[row + 1][mid - 1] = '/';
        fillBuffer(root->esq, level + 1, left, mid - 1, buffer);
    }
    
    // Se existir filho à direita, desenha a barra e preenche recursivamente
    if(root->dir != NULL) {
        buffer[row + 1][mid + 1] = '\\';
        fillBuffer(root->dir, level + 1, mid + 1, right, buffer);
    }
}

// Função que organiza o buffer e imprime a árvore
void printPrettyTree(PONT root) {
    int h = treeHeight(root);
    if(h == 0)
        return;
    // Define o número de linhas: 2 * h - 1 (uma linha para o nó, uma para a barra, exceto no último nível)
    int rows = h * 2 - 1;
    // Define a largura: usamos 2^h * 2 - 1 (pode ser ajustado conforme o tamanho dos números)
    int width = ((1 << h) * 2) - 1;

    // Aloca e inicializa o buffer com espaços
    char** buffer = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        buffer[i] = (char*)malloc((width + 1) * sizeof(char));
        for (int j = 0; j < width; j++) {
            buffer[i][j] = ' ';
        }
        buffer[i][width] = '\0';
    }

    // Preenche o buffer a partir da raiz
    fillBuffer(root, 0, 0, width - 1, buffer);
    
    // Imprime o buffer linha por linha
    for(int i = 0; i < rows; i++){
         // Remove espaços à direita (opcional)
         int j = width - 1;
         while(j >= 0 && buffer[i][j] == ' ') {
             buffer[i][j] = '\0';
             j--;
         }
         printf("%s\n", buffer[i]);
         free(buffer[i]);
    }
    free(buffer);
}