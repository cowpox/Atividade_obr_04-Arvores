# Árvore Binária de Busca (BST) - Estrutura de Dados

## Descrição do Projeto

Este projeto implementa uma **Árvore Binária de Busca (BST)** com suporte a contagem de frequência de chaves repetidas. Ele faz parte da disciplina de **Estrutura de Dados** e tem como objetivo a prática das operações fundamentais de uma BST, além de algumas funcionalidades avançadas.

## Autor

Desenvolvido por **Adriano Brandão** como parte de um projeto acadêmico da disciplina de **Estrutura de Dados** (Professor Anderson Paulo Avila Santos - Universidade Estadual de Londrina) para estudar  **árvores binárias de busca** .

## Funcionalidades Implementadas

O projeto segue um  **plano de implementação progressivo** , das funções mais básicas para as mais avançadas:

### **1. Funções Básicas**

* `inicializar(PONT* raiz)`: Inicializa a árvore como vazia.
* `criarNo(int valor)`: Cria um novo nó com a chave fornecida.
* `buscar(PONT raiz, int valor)`: Busca um valor na árvore e retorna um ponteiro para o nó encontrado (ou `NULL` se não existir).

### **2. Inserção e Remoção**

* `inserir(PONT raiz, int valor)`: Insere um valor na BST. Se a chave já existir, apenas incrementa seu contador.
* `removerUmaOcorrencia(PONT raiz, int valor)`: Remove **uma** ocorrência do valor na árvore (decrementa o contador se >1, remove o nó se =1).
* `removerTodasOcorrencias(PONT raiz, int valor)`: Remove **todas** as ocorrências do valor na árvore.

### **3. Percursos da Árvore**

* `exibirInOrder(PONT raiz)`: Exibe os elementos em  **ordem crescente** .
* `exibirPreOrder(PONT raiz)`: Exibe os elementos em  **ordem pré-fixa** .
* `exibirPostOrder(PONT raiz)`: Exibe os elementos em  **ordem pós-fixa** .

### **4. Funções de Contagem**

* `contarNos(PONT raiz)`: Conta o **número de chaves distintas** na árvore.
* `contarTotalElementos(PONT raiz)`: Conta o  **número total de elementos** , considerando repetições.

### **5. Funções Avançadas**

* `kEsimoMenor(PONT raiz, int k)`: Retorna o  **k-ésimo menor elemento** , considerando repetições.
* `imprimirIntervalo(PONT raiz, int min, int max)`: Exibe os elementos que pertencem ao intervalo `[min, max]`.
* `lowestCommonAncestor(PONT raiz, int val1, int val2)`: Retorna o **ancestral comum mais próximo** de dois valores na BST.

### **6. Função para Depuração**

* `exibirArvore(PONT raiz)`: Exibe a estrutura da árvore no formato textual.

### **7. Liberação de Memória**

* `liberarArvore(PONT raiz)`: Libera recursivamente a memória alocada para a árvore.

## Como Compilar e Executar

### **Compilação**

```sh
gcc BST_Adriano.c -o BST_Adriano
```

### **Execução**

```sh
./BST_Adriano
```

## Exemplo de Uso

### **Inserindo elementos**

```c
PONT raiz;
inicializar(&raiz);
raiz = inserir(raiz, 10);
raiz = inserir(raiz, 5);
raiz = inserir(raiz, 15);
raiz = inserir(raiz, 10); // Incrementa contador de 10
```

### **Exibindo elementos em ordem**

```c
exibirInOrder(raiz); // Saída esperada: 5 10 10 15
```

### **Removendo uma ocorrência**

```c
raiz = removerUmaOcorrencia(raiz, 10);
exibirInOrder(raiz); // Saída esperada: 5 10 15
```

### **Liberando Memória**

```c
liberarArvore(raiz);
raiz = NULL;
printf("Memória liberada com sucesso!\n");
```

## Estrutura de Desenvolvimento

O desenvolvimento seguiu a seguinte abordagem:

1. Implementação das funções básicas ( **inicializar, criarNo, buscar** ).
2. Implementação das operações principais ( **inserir, remover, percursos** ).
3. Implementação das funções auxiliares ( **contar, kEsimoMenor, imprimirIntervalo** ).
4. Testes exaustivos de cada funcionalidade.
5. Implementação da liberação de memória ( **liberarArvore** ).

## Testes Realizados

Os testes incluíram:
✅ Inserção de elementos com repetição.
✅ Busca de elementos existentes e inexistentes.
✅ Remoção de uma e todas as ocorrências.
✅ Impressão in-order, pre-order e post-order.
✅ Contagem de elementos distintos e totais.
✅ k-ésimo menor corretamente identificado.
✅ Impressão de elementos dentro de um intervalo.
✅ Determinação do Lowest Common Ancestor.
✅ Liberação correta de memória.

## Possíveis Melhorias Futuras

* Implementar balanceamento da BST (AVL, Red-Black Tree).
* Criar interface gráfica para visualização dinâmica da árvore.
* Otimizar a remoção para evitar duplicidade de código.

## Licença

Este projeto foi desenvolvido para fins acadêmicos e pode ser livremente utilizado para estudo e aprendizado.
