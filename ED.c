#include <stdio.h>
#include <stdlib.h>


// Definição da estrutura do nó da lista
struct No {
    int dado;
    struct No* prox;
};

// Definição da estrutura da lista com descritor
struct DescritorLista {
    struct No* inicio;  // Ponteiro para o início da lista
};

// Função para inicializar a lista com descritor
void inicializarLista(struct DescritorLista* lista) {
    lista->inicio = NULL;  // Define o início da lista como NULL (lista vazia)
}

// Função para criar um novo nó
struct No* criarNo(int dado) {
    // Aloca memória para um novo nó
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = dado;   // Define o dado do novo nó como o valor recebido
    novoNo->prox = NULL;   // Define o próximo nó como NULL (final da lista)
    return novoNo;         // Retorna o ponteiro para o novo nó criado
}

// Função para inserir um nó na lista com descritor de forma ordenada
void inserirOrdenado(struct DescritorLista* lista, int dado) {
    struct No* novoNo = criarNo(dado);  // Cria um novo nó com o dado recebido
    struct No* atual = lista->inicio;   // Ponteiro para percorrer a lista
    struct No* anterior = NULL;         // Ponteiro para o nó anterior ao atual

    // Encontra a posição correta para inserir o novo nó mantendo a ordem crescente
    while (atual != NULL && atual->dado < dado) {
        anterior = atual;               // Atualiza o nó anterior
        atual = atual->prox;            // Avança para o próximo nó
    }

    // Insere o novo nó na posição correta
    if (anterior == NULL) {
        novoNo->prox = lista->inicio;   // Novo nó aponta para o início da lista
        lista->inicio = novoNo;         // Atualiza o início da lista
    } else {
        anterior->prox = novoNo;        // Nó anterior aponta para o novo nó
        novoNo->prox = atual;           // Novo nó aponta para o nó atual
    }
}

// Função para imprimir os elementos da lista com descritor
void imprimirLista(struct DescritorLista* lista) {
    struct No* atual = lista->inicio;   // Ponteiro para percorrer a lista

    // Percorre a lista e imprime os dados dos nós
    while (atual != NULL) {
        printf("%d -> ", atual->dado);  // Imprime o dado do nó atual
        atual = atual->prox;            // Avança para o próximo nó
    }
    printf("NULL\n");                   // Indica o final da lista
}

// Função para calcular o valor médio dos elementos da lista
float calcularMedia(struct DescritorLista* lista) {
    float soma = 0;                     // Inicializa a variável para somar os dados
    int quantidade = 0;                 // Inicializa a variável para contar os elementos
    struct No* atual = lista->inicio;   // Ponteiro para percorrer a lista

    // Percorre a lista para calcular a soma e a quantidade de elementos
    while (atual != NULL) {
        soma += atual->dado;            // Adiciona o dado do nó à soma
        quantidade++;                   // Incrementa a quantidade de elementos
        atual = atual->prox;            // Avança para o próximo nó
    }

    // Retorna a média dos dados da lista
    return soma / quantidade;
}

// Função para remover o primeiro nó imediatamente superior ao valor médio
void removerPrimeiroNoAcimaDaMedia(struct DescritorLista* lista, float media) {
    struct No* atual = lista->inicio;   // Ponteiro para percorrer a lista
    struct No* anterior = NULL;         // Ponteiro para o nó anterior ao atual

    // Encontra o primeiro nó com valor maior que a média
    while (atual != NULL && atual->dado <= media) {
        anterior = atual;               // Atualiza o nó anterior
        atual = atual->prox;            // Avança para o próximo nó
    }

    // Remove o nó encontrado (se existir)
    if (atual != NULL) {
        if (anterior == NULL) {
            lista->inicio = atual->prox;    // Atualiza o início da lista
        } else {
            anterior->prox = atual->prox;   // Remove o nó da lista
        }
        free(atual);                        // Libera a memória do nó removido
    }
}

// Função principal (main)
int main() {
    struct DescritorLista lista;            // Declara uma lista com descritor
    inicializarLista(&lista);               // Inicializa a lista (vazia)

    int numNos;
    printf("Quantos nós você deseja inserir na lista? ");
    scanf("%d", &numNos);                   // Lê o número de nós a serem inseridos

    // Loop para inserir os nós na lista
    int i;
    for (i = 0; i < numNos; i++) {
        int dado;
        printf("Insira o valor do nó %d: ", i + 1);
        scanf("%d", &dado);                 // Lê o valor do nó a ser inserido
        inserirOrdenado(&lista, dado);      // Insere o nó na lista de forma ordenada
    }

    printf("Lista criada:\n");
    imprimirLista(&lista);                  // Imprime a lista após inserção dos nós

    float media = calcularMedia(&lista);     // Calcula a média dos elementos na lista
    printf("O valor médio dos elementos da lista é: %.2f\n", media);

    // Remove o primeiro nó imediatamente superior à média
    removerPrimeiroNoAcimaDaMedia(&lista, media);
    printf("Lista após remover o primeiro nó imediatamente superior à média:\n");
    imprimirLista(&lista);                  // Imprime a lista após remoção do nó

    return 0;                               // Retorna 0 para indicar que o programa foi executado com sucesso
}

