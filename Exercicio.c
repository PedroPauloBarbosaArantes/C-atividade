#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N 10
#define M (5 * N)
#define NUM_FILAS 10
#define TEMPO_SIMULACAO 300

typedef struct {
    int *vetor;
    int tamanho;
    int inicio;
    int fim;
} Fila;

void inicializar_fila(Fila *f, int tamanho) {
	int i;
    f->vetor = (int *)malloc(sizeof(int) * tamanho);
    f->tamanho = tamanho;
    f->inicio = 0;
    f->fim = 0;
    for (i = 0; i < tamanho; i++) {
        f->vetor[i] = 0;
    }
}

int fila_cheia(Fila *f) {
    return (f->fim == f->tamanho);
}

int fila_vazia(Fila *f) {
    return (f->inicio == f->fim);
}

int colocar(Fila *f, int valor) {
    if (fila_cheia(f)) {
        return 0;
    }
    f->vetor[f->fim] = valor;
    f->fim = (f->fim + 1) % f->tamanho;
    return 1;
}

int retirar(Fila *f) {
    if (fila_vazia(f)) {
        return -1;
    }
    int valor = f->vetor[f->inicio];
    f->inicio = (f->inicio + 1) % f->tamanho;
    return valor;
}

void liberar_fila(Fila *f) {
    free(f->vetor);
}

void simular_insercao(Fila *filas, int num_filas) {
	int tempo;
    srand(time(NULL));

    for (tempo = 0; tempo < TEMPO_SIMULACAO; tempo++) {
        usleep((rand() % 91 + 10) * 1000);

        int valor = rand() % 100 + 1;
        int fila_index = rand() % num_filas;

        if (fila_index == 9) {
            colocar(&filas[fila_index], valor);
        } else {
            if (valor <= filas[fila_index].tamanho) {
                colocar(&filas[fila_index], valor);
            }
        }
    }
}

void contar_tamanho_e_retira(Fila *filas, int num_filas) {
    int retiradas[NUM_FILAS] = {0};
    int tempo, i;

    for (tempo = 0; tempo < TEMPO_SIMULACAO; tempo++) {
        usleep((rand() % 91 + 10) * 1000);

        for (i = 0; i < num_filas - 1; i++) {
            if (!fila_vazia(&filas[i])) {
                int valor = retirar(&filas[i]);
                retiradas[i]++;
            }
        }
    }

    printf("\nEstado final das filas após 5 minutos:\n");
    for (i = 0; i < NUM_FILAS; i++) {
        printf("Fila %d: ", i + 1);
        if (i == 9) {
            printf("Tamanho %d, Elementos retirados: %d, Restante na fila maior: %d\n",
                   filas[i].fim - filas[i].inicio, retiradas[i], filas[i].fim - filas[i].inicio);
        } else {
            printf("Tamanho %d, Elementos retirados: %d\n",
                   filas[i].fim - filas[i].inicio, retiradas[i]);
        }
    }
}

int main() {
	int i;
    Fila filas[NUM_FILAS];

    for (i = 0; i < NUM_FILAS - 1; i++) {
        inicializar_fila(&filas[i], N);
    }

    inicializar_fila(&filas[NUM_FILAS - 1], M);

    simular_insercao(filas, NUM_FILAS);

    contar_tamanho_e_retira(filas, NUM_FILAS);

    for (i = 0; i < NUM_FILAS; i++) {
        liberar_fila(&filas[i]);
    }

    return 0;
}

