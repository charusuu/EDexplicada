#include <stdio.h>
#include <stdlib.h>


// Defini��o da estrutura do n� da lista
struct No {
    int dado;
    struct No* prox;
};

// Defini��o da estrutura da lista com descritor
struct DescritorLista {
    struct No* inicio;  // Ponteiro para o in�cio da lista
};

// Fun��o para inicializar a lista com descritor
void inicializarLista(struct DescritorLista* lista) {
    lista->inicio = NULL;  // Define o in�cio da lista como NULL (lista vazia)
}

// Fun��o para criar um novo n�
struct No* criarNo(int dado) {
    // Aloca mem�ria para um novo n�
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = dado;   // Define o dado do novo n� como o valor recebido
    novoNo->prox = NULL;   // Define o pr�ximo n� como NULL (final da lista)
    return novoNo;         // Retorna o ponteiro para o novo n� criado
}

// Fun��o para inserir um n� na lista com descritor de forma ordenada
void inserirOrdenado(struct DescritorLista* lista, int dado) {
    struct No* novoNo = criarNo(dado);  // Cria um novo n� com o dado recebido
    struct No* atual = lista->inicio;   // Ponteiro para percorrer a lista
    struct No* anterior = NULL;         // Ponteiro para o n� anterior ao atual

    // Encontra a posi��o correta para inserir o novo n� mantendo a ordem crescente
    while (atual != NULL && atual->dado < dado) {
        anterior = atual;               // Atualiza o n� anterior
        atual = atual->prox;            // Avan�a para o pr�ximo n�
    }

    // Insere o novo n� na posi��o correta
    if (anterior == NULL) {
        novoNo->prox = lista->inicio;   // Novo n� aponta para o in�cio da lista
        lista->inicio = novoNo;         // Atualiza o in�cio da lista
    } else {
        anterior->prox = novoNo;        // N� anterior aponta para o novo n�
        novoNo->prox = atual;           // Novo n� aponta para o n� atual
    }
}

// Fun��o para imprimir os elementos da lista com descritor
void imprimirLista(struct DescritorLista* lista) {
    struct No* atual = lista->inicio;   // Ponteiro para percorrer a lista

    // Percorre a lista e imprime os dados dos n�s
    while (atual != NULL) {
        printf("%d -> ", atual->dado);  // Imprime o dado do n� atual
        atual = atual->prox;            // Avan�a para o pr�ximo n�
    }
    printf("NULL\n");                   // Indica o final da lista
}

// Fun��o para calcular o valor m�dio dos elementos da lista
float calcularMedia(struct DescritorLista* lista) {
    float soma = 0;                     // Inicializa a vari�vel para somar os dados
    int quantidade = 0;                 // Inicializa a vari�vel para contar os elementos
    struct No* atual = lista->inicio;   // Ponteiro para percorrer a lista

    // Percorre a lista para calcular a soma e a quantidade de elementos
    while (atual != NULL) {
        soma += atual->dado;            // Adiciona o dado do n� � soma
        quantidade++;                   // Incrementa a quantidade de elementos
        atual = atual->prox;            // Avan�a para o pr�ximo n�
    }

    // Retorna a m�dia dos dados da lista
    return soma / quantidade;
}

// Fun��o para remover o primeiro n� imediatamente superior ao valor m�dio
void removerPrimeiroNoAcimaDaMedia(struct DescritorLista* lista, float media) {
    struct No* atual = lista->inicio;   // Ponteiro para percorrer a lista
    struct No* anterior = NULL;         // Ponteiro para o n� anterior ao atual

    // Encontra o primeiro n� com valor maior que a m�dia
    while (atual != NULL && atual->dado <= media) {
        anterior = atual;               // Atualiza o n� anterior
        atual = atual->prox;            // Avan�a para o pr�ximo n�
    }

    // Remove o n� encontrado (se existir)
    if (atual != NULL) {
        if (anterior == NULL) {
            lista->inicio = atual->prox;    // Atualiza o in�cio da lista
        } else {
            anterior->prox = atual->prox;   // Remove o n� da lista
        }
        free(atual);                        // Libera a mem�ria do n� removido
    }
}

// Fun��o principal (main)
int main() {
    struct DescritorLista lista;            // Declara uma lista com descritor
    inicializarLista(&lista);               // Inicializa a lista (vazia)

    int numNos;
    printf("Quantos n�s voc� deseja inserir na lista? ");
    scanf("%d", &numNos);                   // L� o n�mero de n�s a serem inseridos

    // Loop para inserir os n�s na lista
    int i;
    for (i = 0; i < numNos; i++) {
        int dado;
        printf("Insira o valor do n� %d: ", i + 1);
        scanf("%d", &dado);                 // L� o valor do n� a ser inserido
        inserirOrdenado(&lista, dado);      // Insere o n� na lista de forma ordenada
    }

    printf("Lista criada:\n");
    imprimirLista(&lista);                  // Imprime a lista ap�s inser��o dos n�s

    float media = calcularMedia(&lista);     // Calcula a m�dia dos elementos na lista
    printf("O valor m�dio dos elementos da lista �: %.2f\n", media);

    // Remove o primeiro n� imediatamente superior � m�dia
    removerPrimeiroNoAcimaDaMedia(&lista, media);
    printf("Lista ap�s remover o primeiro n� imediatamente superior � m�dia:\n");
    imprimirLista(&lista);                  // Imprime a lista ap�s remo��o do n�

    return 0;                               // Retorna 0 para indicar que o programa foi executado com sucesso
}

