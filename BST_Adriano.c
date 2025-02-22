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

// 4 - Função liberarArvore: desaloca cada nó da árvore
void liberarArvore(PONT raiz) {
    if (raiz == NULL) return;  // Caso base: árvore vazia

    // Primeiro libera a subárvore esquerda e direita
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);

    // Depois libera o nó atual
    free(raiz);
}


//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// main() para testes com expectativas de resultado
int main() {
    //
    // As funções a serem implementadas:
    //   - criarNo
    //   - inserir
    //   - removerUmaOcorrencia
    //   - removerTodasOcorrencias
    //   - buscar
    //   - exibirInOrder
    //   - contarNos
    //   - contarTotalElementos
    //   - kEsimoMenor
    //   - imprimirIntervalo
    //   - lowestCommonAncestor

    // PONT raiz;                    // ponteiro para a raiz da BST
    // inicializar(&raiz);           // deixa a árvore vazia
    PONT raiz;
    inicializar(&raiz);
    
    // testa inicialização da árvore (Adriano)
    if (raiz == NULL)
        printf("Árvore inicializada corretamente!\n");
    else
        printf("Erro na inicialização!\n");


    // testa função criar nó (Adriano)
    PONT no = criarNo(42);

    if (no != NULL) {
        printf("Nó criado com chave = %d, contador = %d\n", no->chave, no->contador);
    } else {
        printf("Erro ao criar nó.\n");
    }

    free(no);  // Evita vazamento de memória

    // -------------------------------------------------------
    // 1) Inserção com valores repetidos
    //    Esperado que:
    //      - nó 10 tenha contador=2
    //      - nó 5  tenha contador=3
    //      - nó 15 tenha contador=1
    //      - nó 18 tenha contador=1
    //
    // InOrder final esperado (antes de quaisquer remoções):
    //     "5 5 5 10 10 15 18"
    //

    // não estava atualizando o nó raiz
    // inserir(raiz, 10); 
    // inserir(raiz, 5);
    // inserir(raiz, 15);
    // inserir(raiz, 10); // repetido => contador(10)++
    // inserir(raiz, 5);  // repetido => contador(5)++
    // inserir(raiz, 5);  // repetido => contador(5)++
    // inserir(raiz, 18);

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 10); // repetido => contador(10)++
    raiz = inserir(raiz, 5);  // repetido => contador(5)++
    raiz = inserir(raiz, 5);  // repetido => contador(5)++
    raiz = inserir(raiz, 18);




    printf("\n--- APÓS INSERIR (10,5,15,10,5,5,18) ---\n");
    printf("InOrder esperado: 5 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz); 
    printf("\n");

    exibirArvore(raiz);

    // -------------------------------------------------------
    // 2) Busca por valores
    PONT node5 = buscar(raiz, 5);
    if(node5) {
        printf("\nBuscar(5): encontrado com contador=%d (esperado=3)\n", node5->contador);
    } else {
        printf("\nBuscar(5): não encontrado (inesperado)\n");
    }

    PONT nodeX = buscar(raiz, 999); // valor não existente
    if(!nodeX) {
        printf("Buscar(999): não encontrado (esperado)\n");
    } else {
        printf("Buscar(999): encontrado??? (inesperado)\n");
    }

    // -------------------------------------------------------
    // 3) Remover UMA ocorrência 
    //    removerUmaOcorrencia(5) => contador(5) deve passar de 3 para 2
    removerUmaOcorrencia(raiz, 5);

    printf("\n--- APÓS removerUmaOcorrencia(5) ---\n");
    printf("Esperado InOrder: 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    node5 = buscar(raiz, 5);
    if(node5) {
        printf("Agora contador(5)=%d (esperado=2)\n", node5->contador);
    }

    // -------------------------------------------------------
    // 4) Remover TODAS ocorrências
    //    removerTodasOcorrencias(10) => remove nó com chave=10 por completo
    removerTodasOcorrencias(raiz, 10);

    printf("\n--- APÓS removerTodasOcorrencias(10) ---\n");
    printf("Esperado InOrder: 5 5 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    // -------------------------------------------------------
    // 5) Contagem de nós e total de elementos
    //    Árvores resultante: {5(cont=2), 15(cont=1), 18(cont=1)}
    //      => contarNos=3   (chaves distintas: 5,15,18)
    //      => contarTotalElementos=4   (5,5,15,18)
    int qtdNos = contarNos(raiz);
    int totalElem = contarTotalElementos(raiz);
    printf("\ncontarNos => %d (esperado=3)\n", qtdNos);
    printf("contarTotalElementos => %d (esperado=4)\n", totalElem);

    // -------------------------------------------------------
    // 6) k-ésimo menor (considerando contadores)
    //    InOrder real: [5,5,15,18]
    //       k=1 => 5
    //       k=2 => 5
    //       k=3 => 15
    //       k=4 => 18
    //       k=5 => -1 (não existe)
    printf("\n--- Teste k-ésimo menor ---\n");
    printf("k=1 => %d (esperado=5)\n", kEsimoMenor(raiz,1));
    printf("k=2 => %d (esperado=5)\n", kEsimoMenor(raiz,2));
    printf("k=3 => %d (esperado=15)\n", kEsimoMenor(raiz,3));
    printf("k=4 => %d (esperado=18)\n", kEsimoMenor(raiz,4));
    printf("k=5 => %d (esperado=-1)\n", kEsimoMenor(raiz,5));

    // -------------------------------------------------------
    // 7) imprimirIntervalo [6..18]
    //    InOrder da árvore: 5,5,15,18
    //    Filtrando [6..18], esperamos: 15 18
    printf("\n--- Teste imprimirIntervalo [6..18] ---\n");
    printf("Esperado: 15 18\nObtido:   ");
    imprimirIntervalo(raiz, 6, 18);
    printf("\n");

    // -------------------------------------------------------
    // 8) Testar LCA (lowestCommonAncestor) - não é opcional
    //    Vamos inserir mais alguns valores para teste de LCA
    //    Situação final da árvore atual: 5(cont=2),15(cont=1),18(cont=1)
    //    Inserir(12), Inserir(16), Inserir(3)
    //    Nova BST (com contadores):
    //       5 (cont=2)
    //           /    \
    //         3(1)   15(1)
    //                /  \
    //              12(1) 18(1)
    //                  \
    //                  16(1)

    //    Correção da nova BST (alocação correta do 16):
    //            15(1)
    //           /    \
    //         5(2)   18(1)
    //        /  \     /  \
    //    3(1) 12(1) 16(1)
    //                  

    inserir(raiz, 12);
    inserir(raiz, 16);
    inserir(raiz, 3);

    printf("\n--- Árvore após inserir(12,16,3) ---\n");
    printf("InOrder esperado: 3 5 5 12 15 16 18\n");
    printf("Obtido:          ");
    exibirInOrder(raiz);
    printf("\n");
    exibirArvore(raiz);
    printf("\n");
    printf("PreOrder\n");
    exibirPreOrder(raiz);
    printf("\n");
    printf("PostOrder\n");
    exibirPostOrder(raiz);
    printf("\n");



    PONT nLCA;

    nLCA = lowestCommonAncestor(raiz, 3, 5);

    if(nLCA) {
        printf("\nLCA(3,5) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 3, 12);
    if(nLCA) {
        printf("LCA(3,12) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 16, 18);
    if(nLCA) {
        printf("LCA(16,18) => chave=%d (esperado=18)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 5, 18);
    if(nLCA) {
        printf("LCA(5,18) => chave=%d (esperado=15)\n", nLCA->chave);
    }

    // Por fim, buscar um LCA com valor inexistente
    nLCA = lowestCommonAncestor(raiz, 100, 3);
    if(!nLCA) {
        printf("LCA(100,3) => NULL (esperado=chave nao existe)\n");
    }

    printf("\n--- FIM DOS TESTES ---\n");

    liberarArvore(raiz);
    raiz = NULL; // evita acessos inválidos pós-liberação
    printf("Memória liberada com sucesso!\n");

    return 0;
}
