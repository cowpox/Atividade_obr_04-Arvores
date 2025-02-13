/*
  EP: Árvore Binária de Busca (BST)
  Professor Anderson Ávila - UEL
  Descrição: Completar as funções solicitadas, sem alterar suas assinaturas.
  
  A main() contém testes que exibem resultados esperados como comentário.
  Quando as funções estiverem corretamente implementadas, esses testes
  devem produzir a saída indicada.
*/

#include <stdio.h>
#include <stdlib.h>




#include <string.h>
#include <math.h>

// Estrutura do nó
typedef struct no {
    int chave;
    int contador;           // número de cópias (frequência) dessa chave
    struct no* esq;         // ponteiro para subárvore esquerda
    struct no* dir;         // ponteiro para subárvore direita
} NO, *PONT;

// Protótipos das funções
void inicializar(PONT* raiz);
PONT criarNo(int valor);
PONT inserir(PONT raiz, int valor);
PONT removerUmaOcorrencia(PONT raiz, int valor);
PONT removerTodasOcorrencias(PONT raiz, int valor);
PONT buscar(PONT raiz, int valor);
void exibirInOrder(PONT raiz);
int contarNos(PONT raiz);
int contarTotalElementos(PONT raiz);
int kEsimoMenor(PONT raiz, int k);
void imprimirIntervalo(PONT raiz, int min, int max);
PONT lowestCommonAncestor(PONT raiz, int val1, int val2);
// funções opcionais
void exibirArvore(PONT raiz);
void exibirPreOrder(PONT raiz);
void exibirPostOrder(PONT raiz);

//------------------------------------------------------------------------------
// 1) Inicializar
void inicializar(PONT* raiz) {
    // defina a raiz como NULL (árvore vazia)
    *raiz = NULL;
}

//------------------------------------------------------------------------------
// 2) Criar nó
PONT criarNo(int valor) {
    // aloca memória para o novo nó
    PONT novo = (PONT) malloc(sizeof(NO));
    if(novo) {
        // preenche os campos do novo nó
        novo->chave = valor;
        novo->contador = 1;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    // retorna ponteiro para o novo nó
    return novo;
}

//------------------------------------------------------------------------------
// 3) Buscar
PONT buscar(PONT raiz, int valor) {
    // Retorna ponteiro para nó com chave == valor ou NULL se não existir.
    if (raiz == NULL || raiz->chave == valor) 
        return raiz;
    
        // Usar a lógica de BST:
    //  - se valor < raiz->chave => buscar à esquerda
    if (valor < raiz->chave)
        return buscar(raiz->esq, valor);
    
        //  - se valor > raiz->chave => buscar à direita
    return buscar(raiz->dir, valor);
    

    //  - se valor == raiz->chave => retorna raiz ???

    return NULL;
}

//------------------------------------------------------------------------------
// 4) Inserir
PONT inserir(PONT raiz, int valor) {
    // Se raiz == NULL (árvore vazia) => cria nó e retorna
    if (raiz == NULL) {
        return criarNo(valor);
    }
    
    // Se valor < raiz->chave => raiz->esq = inserir(raiz->esq, valor)
    if (valor < raiz->chave) {
        raiz->esq = inserir(raiz->esq, valor);  // Insere na esquerda
    // Se valor > raiz->chave => raiz->dir = inserir(raiz->dir, valor)
    } else if (valor > raiz->chave) {
        raiz->dir = inserir(raiz->dir, valor);  // Insere na direita
    // Se valor == raiz->chave => incrementa raiz->contador
    } else {
        raiz->contador++;  // Se já existe, incrementa o contador
    }
    
    // retorna a nova raiz (importante para recursão)
    return raiz;
}

//------------------------------------------------------------------------------
// 5) Remover UMA ocorrência
PONT removerUmaOcorrencia(PONT raiz, int valor) {
    if (raiz == NULL) 
        return NULL; // Se a árvore está vazia, nada a fazer
    
    // 1) Buscar nó do valor (enquanto percorre para exluir):
    if (valor < raiz->chave) {
        raiz->esq = removerUmaOcorrencia(raiz->esq, valor);
    } else if (valor > raiz->chave) {
        raiz->dir = removerUmaOcorrencia(raiz->dir, valor);
    } else {
        // Encontrou o nó com a chave desejada
        // 2) contador>1 => decrementa
        if (raiz->contador > 1) {
            raiz->contador--; // Apenas decrementa o contador
        // 3) se contador==1 => remoção clássica de BST (casos 0,1,2 filhos)
        } else {
            // Caso o contador seja 1, removemos o nó da BST
            // caso 1: nó sem filho esquerdo (ou sem filhos) => ou é folha ou só tem filho à direita
            // solução: remove o nó e substitui pelo filho à direita
            if (raiz->esq == NULL) {
                PONT temp = raiz->dir;
                free(raiz);
                return temp;
            // caso 2: nó sem filho direito (ou sem filhos) => ou é folha ou só tem filho à esquerda
            // solução: remove o nó e substitui pelo filho à esquerda
            } else if (raiz->dir == NULL) {
                PONT temp = raiz->esq;
                free(raiz);
                return temp;
            } else {
                // Nó com dois filhos: encontrar o sucessor in-order (menor da subárvore direita)
                PONT temp = raiz->dir;
                while (temp->esq != NULL)
                    temp = temp->esq;
                
                // Copia os valores do sucessor para o nó atual
                raiz->chave = temp->chave;
                raiz->contador = temp->contador;
                
                // Remove o sucessor da subárvore direita
                raiz->dir = removerUmaOcorrencia(raiz->dir, temp->chave);
            }
        }
    }
    return raiz; //importante para retornar a raiz em caso de não encontrar o valor nas recursivas
}

//------------------------------------------------------------------------------
// 6) Remover TODAS ocorrências
PONT removerTodasOcorrencias(PONT raiz, int valor) {
    if (raiz == NULL)
        return NULL;  // Se a árvore está vazia ou o valor não foi encontrado
    
        // 1) Buscar nó do valor (enquanto percorre para exluir):
    if (valor < raiz->chave) {
        raiz->esq = removerTodasOcorrencias(raiz->esq, valor);
    } else if (valor > raiz->chave) {
        raiz->dir = removerTodasOcorrencias(raiz->dir, valor);
    } else {
        // Encontrou o nó - agora vamos removê-lo completamente
        if (raiz->esq == NULL) {
            PONT temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            PONT temp = raiz->esq;
            free(raiz);
            return temp;
        } else {
            // Nó com dois filhos: encontrar o sucessor in-order (menor da subárvore direita)
            PONT temp = raiz->dir;
            while (temp->esq != NULL) temp = temp->esq;

            // Copia os valores do sucessor para o nó atual
            raiz->chave = temp->chave;
            raiz->contador = temp->contador;

            // Remove o sucessor da subárvore direita
            raiz->dir = removerTodasOcorrencias(raiz->dir, temp->chave);
        }
    }
    return raiz; //importante para retornar a raiz em caso de não encontrar o valor nas recursivas
}

//------------------------------------------------------------------------------
// 7) Exibir InOrder
void exibirInOrder(PONT raiz) {
    if (raiz != NULL) {
        exibirInOrder(raiz->esq);  // Visita a subárvore esquerda

        // Imprime a chave `contador` vezes
        for (int i = 0; i < raiz->contador; i++) {
            printf("%d ", raiz->chave);
        }

        exibirInOrder(raiz->dir);  // Visita a subárvore direita
    }
}

//------------------------------------------------------------------------------
// 8) Contar nós distintos
int contarNos(PONT raiz) {
    // Se raiz==NULL => 0
    if (raiz == NULL)
        return 0; // Se a árvore estiver vazia, não há nós distintos

    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

//------------------------------------------------------------------------------
// 9) Contar total de elementos (somando contadores)
int contarTotalElementos(PONT raiz) {
    // Se raiz==NULL => 0
    if (raiz == NULL)
        return 0; // Se a árvore estiver vazia, não há elementos

    return raiz->contador + contarTotalElementos(raiz->esq) + contarTotalElementos(raiz->dir);
}

//------------------------------------------------------------------------------
// 10) k-ésimo menor
int kEsimoMenorAux(PONT raiz, int k, int *contador) {
    if (raiz == NULL)
        return -1; // Se a árvore estiver vazia ou k for inválido

    // Primeiro, busca na subárvore esquerda
    int resultado = kEsimoMenorAux(raiz->esq, k, contador);
    if (resultado != -1) 
        return resultado; // Se encontrou na esquerda, retorna

    // Contabiliza o nó atual considerando sua frequência
    *contador += raiz->contador;

    // Se o k-ésimo menor está dentro do contador atual, encontramos o valor
    if (*contador >= k)
        return raiz->chave;

    // Se ainda não foi encontrado, busca na subárvore direita
    return kEsimoMenorAux(raiz->dir, k, contador);
}


int kEsimoMenor(PONT raiz, int k) {
    int contador = 0;
    // utilizar uma função auxiliar (kEsimoMenorAux)
    return kEsimoMenorAux(raiz, k, &contador);
}

//------------------------------------------------------------------------------
// 11) Imprimir Intervalo [min, max]
void imprimirIntervalo(PONT raiz, int min, int max) {
    if (raiz == NULL)
        return; // Caso base: árvore vazia

    // Se a chave atual for menor que min, ignora a subárvore esquerda e busca apenas na direita
    if (raiz->chave < min) {
        imprimirIntervalo(raiz->dir, min, max);
        return; // Importante para evitar verificações desnecessárias
    }

    // Se a chave atual for maior que max, ignora a subárvore direita e busca apenas na esquerda
    if (raiz->chave > max) {
        imprimirIntervalo(raiz->esq, min, max);
        return; // Importante para evitar verificações desnecessárias
    }

    // Se a chave atual está dentro do intervalo, imprime o valor 'contador' vezes
    for (int i = 0; i < raiz->contador; i++) {
        printf("%d ", raiz->chave);
    }

    // Chama recursivamente para a subárvore esquerda e direita
    imprimirIntervalo(raiz->esq, min, max);
    imprimirIntervalo(raiz->dir, min, max);
}

//------------------------------------------------------------------------------

PONT lowestCommonAncestor(PONT raiz, int val1, int val2) {
    if (raiz == NULL)
        return NULL; // Caso base: árvore vazia ou não encontrou os valores

    // Se um dos valores for igual à raiz, a raiz já é o LCA
    if (raiz->chave == val1 || raiz->chave == val2) return raiz;

    // Se ambos os valores são menores que a raiz, o LCA está na esquerda
    if (val1 < raiz->chave && val2 < raiz->chave)
        return lowestCommonAncestor(raiz->esq, val1, val2);

    // Se ambos os valores são maiores que a raiz, o LCA está na direita
    if (val1 > raiz->chave && val2 > raiz->chave)
        return lowestCommonAncestor(raiz->dir, val1, val2);

    // Se os valores estão em lados diferentes ou um deles é a raiz, encontramos o LCA
    return raiz;
}

//------------------------------------------------------------------------------
// FUNÇÕES OPCIONAIS (EXTRAS)
//------------------------------------------------------------------------------

// 1 - Função exibirArvore: permite a visualização da árvore no formato:
// raiz - subárvore esquerda - subárvore direita
void exibirArvore(PONT raiz) {
    if (raiz == NULL) {
        printf("NULL");
        return;
    }
    
    // Imprime a chave do nó
    printf("%i", raiz->chave);
    
    // Se houver pelo menos um filho, imprime as subárvores entre parênteses
    if (raiz->esq != NULL || raiz->dir != NULL) {
        printf("(");
        exibirArvore(raiz->esq);
        printf(", ");
        exibirArvore(raiz->dir);
        printf(")");
    }
}


// 2 - Função exibirPreOrder: permite a visualização da árvore no formato:
void exibirPreOrder(PONT raiz){
    if (raiz == NULL) return; // Caso base: árvore vazia

    // Imprime a chave atual 'contador' vezes
    for (int i = 0; i < raiz->contador; i++) {
        printf("%d ", raiz->chave);
    }

    // Chama recursivamente para a subárvore esquerda
    exibirPreOrder(raiz->esq);

    // Chama recursivamente para a subárvore direita
    exibirPreOrder(raiz->dir);
}


// 3 - Função exibirPostOrder: permite a visualização da árvore no formato:
void exibirPostOrder(PONT raiz) {
    if (raiz == NULL) return;  // Caso base: árvore vazia

    // Chama recursivamente para a subárvore esquerda
    exibirPostOrder(raiz->esq);

    // Chama recursivamente para a subárvore direita
    exibirPostOrder(raiz->dir);

    // Imprime a chave atual 'contador' vezes
    for (int i = 0; i < raiz->contador; i++) {
        printf("%d ", raiz->chave);
    }
}



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
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// main() para testes com expectativas de resultado
int main() {
    PONT raiz;
    inicializar(&raiz);

    // -------------------------------------------------------
    // 1) Testa inicialização da árvore
    printf("\n--- TESTE: Inicialização da árvore ---\n");
    if (raiz == NULL)
        printf("Árvore inicializada corretamente! (esperado)\n");
    else
        printf("Erro na inicialização! (inesperado)\n");

    // -------------------------------------------------------
    // 2) Testa função criar nó
    printf("\n--- TESTE: Criar nó ---\n");
    PONT no = criarNo(42);
    if (no != NULL) {
        printf("Nó criado com chave = %d, contador = %d (esperado: chave=42, contador=1)\n", no->chave, no->contador);
    } else {
        printf("Erro ao criar nó. (inesperado)\n");
    }
    free(no);  // Evita vazamento de memória

    // -------------------------------------------------------
    // 3) Inserção com valores repetidos
    printf("\n--- TESTE: Inserção de 20 valores (com repetições) ---\n");
    int valores[] = {10, 5, 15, 10, 5, 5, 18, 7, 12, 6, 8, 2, 25, 30, 1, 20, 12, 6, 40, 15};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    printf("InOrder após inserção:\n");
    printf("Esperado: 1 2 5 5 5 6 6 7 8 10 10 12 12 15 15 18 20 25 30 40\n");
    printf("Obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    exibirArvore(raiz);

    // -------------------------------------------------------
    // 4) Teste de busca
    printf("\n--- TESTE: Busca por elementos existentes e inexistentes ---\n");
    int buscarValores[] = {10, 5, 25, 40, 100}; // 100 não existe
    int esperados[] = {2, 3, 1, 1, -1}; // Contadores esperados
    for (int i = 0; i < 5; i++) {
        PONT resultado = buscar(raiz, buscarValores[i]);
        if (resultado)
            printf("Busca(%d) encontrado, contador = %d (esperado: %d)\n", buscarValores[i], resultado->contador, esperados[i]);
        else
            printf("Busca(%d) não encontrado. (esperado)\n", buscarValores[i]);
    }

    // -------------------------------------------------------
    // 5) Teste de remoção de UMA ocorrência
    printf("\n--- TESTE: Remoção de UMA ocorrência ---\n");
    printf("Removendo uma ocorrência do valor 5...\n");
    raiz = removerUmaOcorrencia(raiz, 5);
    printf("InOrder após remover uma ocorrência de 5:\n");
    printf("Esperado: 1 2 5 5 6 6 7 8 10 10 12 12 15 15 18 20 25 30 40\n");
    printf("Obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    // -------------------------------------------------------
    // 6) Teste de remoção de TODAS as ocorrências
    printf("\n--- TESTE: Remoção de TODAS as ocorrências ---\n");
    printf("Removendo todas as ocorrências do valor 10...\n");
    raiz = removerTodasOcorrencias(raiz, 10);
    printf("InOrder após remover todas as ocorrências de 10:\n");
    printf("Esperado: 1 2 5 5 6 6 7 8 12 12 15 15 18 20 25 30 40\n");
    printf("Obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    // -------------------------------------------------------
    // 7) Teste de contagem de nós distintos e total de elementos
    printf("\n--- TESTE: Contagem de nós distintos e total de elementos ---\n");
    int qtdNos = contarNos(raiz);
    int totalElem = contarTotalElementos(raiz);
    printf("Total de nós distintos = %d (esperado: 13)\n", qtdNos);
    printf("Total de elementos = %d (esperado: 17)\n", totalElem);

    // -------------------------------------------------------
    // 8) Teste de k-ésimo menor elemento
    printf("\n--- TESTE: k-ésimo menor elemento ---\n");
    printf("Esperado: 1 2 5 5 6 6 7 8 12 12\n");
    printf("Obtido:   ");
    for (int k = 1; k <= 10; k++) {
        int resultado = kEsimoMenor(raiz, k);
        printf("%d ", resultado);
    }
    printf("\n");

    // -------------------------------------------------------
    // 9) Teste de impressão de intervalo [5, 20]
    printf("\n--- TESTE: Impressão de intervalo [5, 20] ---\n");
    printf("Esperado: 5 5 6 6 7 8 12 12 15 15 18 20\n");
    printf("Obtido:   ");
    imprimirIntervalo(raiz, 5, 20);
    printf("\n");

    // -------------------------------------------------------
    // 10) Teste de Lowest Common Ancestor (LCA)
    printf("\n--- TESTE: Lowest Common Ancestor (LCA) ---\n");
    int lcaTestes[][2] = {{6, 8}, {2, 12}, {20, 40}, {1, 30}, {12, 25}};
    int esperadosLCA[] = {7, 5, 25, 10, 15};
    for (int i = 0; i < 5; i++) {
        PONT lca = lowestCommonAncestor(raiz, lcaTestes[i][0], lcaTestes[i][1]);
        printf("LCA(%d, %d) = %d (esperado: %d)\n", lcaTestes[i][0], lcaTestes[i][1], lca ? lca->chave : -1, esperadosLCA[i]);
    }

    // -------------------------------------------------------
    // 11) Teste de exibição da árvore em diferentes ordens
    printf("\n--- TESTE: Percursos da árvore ---\n");
    printf("PreOrder (esperado): 12 5 2 1 7 6 6 8 15 18 25 20 30 40\n");
    printf("Obtido:   ");
    exibirPreOrder(raiz);
    printf("\n");

    printf("PostOrder (esperado): 1 2 6 6 8 7 5 18 25 20 30 40 15 12 12\n");
    printf("Obtido:   ");
    exibirPostOrder(raiz);
    printf("\n");

    // -------------------------------------------------------
    // 12) Teste de exibição gráfica da árvore
    printf("\n--- TESTE: Exibição gráfica da árvore ---\n");
    printPrettyTree(raiz);

    printf("\n--- FIM DOS TESTES ---\n");

    return 0;
}

