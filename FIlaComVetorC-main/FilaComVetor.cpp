#include <stdio.h>
#include <stdlib.h>
#define MAX 10  

typedef struct {
    int fila[MAX];
    int frente;
    int tras;
} Fila;

void inicializarFila(Fila* f) {
    for (int i = 0; i < MAX; i++) {
        f->fila[i] = 0; 
    }
    f->frente = -1;  
    f->tras = -1;
}

int filaCheia(Fila* f) {
    return f->tras == MAX - 1;
}

int filaVazia(Fila* f) {
    return f->frente == -1;
}

void inserir(Fila* f, int valor) {
    if (filaCheia(f)) {
        printf("Fila cheia! N�o � poss�vel inserir elementos.\n");
        return;
    }
    if (f->frente == -1) { 
        f->frente = 0;
    }
    f->tras++;
    f->fila[f->tras] = valor;
    printf("Elemento %d inserido na fila.\n", valor);
}

void retirar(Fila* f) {
    if (filaVazia(f)) {
        printf("Fila vazia! N�o h� elementos para remover.\n");
        return;
    }
    printf("Elemento %d retirado da fila.\n", f->fila[f->frente]);
    f->frente++;
    if (f->frente > f->tras) {  
        f->frente = f->tras = -1;
    }
}

void mostrarFila(Fila* f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    printf("Conte�do da fila: ");
    for (int i = f->frente; i <= f->tras; i++) {
        printf("%d ", f->fila[i]);
    }
    printf("\n");
}
void exibirMenu() {
    printf("\nEscolha uma opera��o:\n");
    printf("1. Inserir elemento\n");
    printf("2. Retirar elemento\n");
    printf("3. Mostrar fila\n");
    printf("4. Sair\n");
}

int main() {
    Fila f;
    int opcao, valor;

    inicializarFila(&f);

    do {
        exibirMenu();
        printf("Digite sua escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                inserir(&f, valor);
                break;
            case 2:
                retirar(&f);
                break;
            case 3:
                mostrarFila(&f);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida! Tente novamente.\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}

