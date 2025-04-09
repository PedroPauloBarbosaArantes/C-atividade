/*Crie duas estruturas(verotes) com N posi??es coda.
Cada estrutura ser? um estacionamento que ter? 2.n vagas.
Criar um vetor auxiliar de tamanho N para servir como local de manobra.
Crie menu com as opera??es estacionar e retirar um carro.*/
#include <stdio.h>
#include <stdbool.h> 

#define N 5

int est1[N] = {0,0,0,0,0};
int est2[N] = {0,0,0,0,0};
int manobra[N] = {0,0,0,0,0};
int vagas = 2 * N;
int livres = 2 * N;


bool estaCheio();
bool estacionar_recursive_est1(int index, int placa);
bool estacionar_recursive_est2(int index, int placa);
void estacionar(int placa);
bool retirar_recursive_est1(int index, int placa);
bool retirar_recursive_est2(int index, int placa);
void retirar(int placa);
void exibir_vagas_recursive(int arr[], int index);
void exibir_estacionamentos();

bool estaCheio() {
    return livres == 0;
}

bool estacionar_recursive_est1(int index, int placa) {
    if (index == N) {
        return false;
    }
    if (est1[index] == 0) {
        est1[index] = placa; 
        livres--;
        printf("Carro %d estacionado na vaga E1-%d.\n", placa, index + 1);
        return true;
    }
    return estacionar_recursive_est1(index + 1, placa);
}

bool estacionar_recursive_est2(int index, int placa) {
    if (index == N) {
        return false;
    }
    if (est2[index] == 0) {
        est2[index] = placa;
        livres--;
        printf("Carro %d estacionado na vaga E2-%d.\n", placa, index + 1);
        return true;
    }
    return estacionar_recursive_est2(index + 1, placa);
}

void estacionar(int placa) {
    if (estaCheio()) {
        printf("Estacionamento cheio!\n");
        return;
    }
    if (!estacionar_recursive_est1(0, placa)) {
        if (!estacionar_recursive_est2(0, placa)) {
            printf("Erro: Nao foi possivel encontrar vaga, apesar de haver vagas livres.\n");
        }
    }
}

bool retirar_recursive_est1(int index, int placa) {
    if (index == N) {
        return false;
    }
    if (est1[index] == placa) {
        est1[index] = 0;
        livres++;
        printf("Carro %d retirado da vaga E1-%d.\n", placa, index + 1);
        return true;
    }
    return retirar_recursive_est1(index + 1, placa);
}

bool retirar_recursive_est2(int index, int placa) {
    if (index == N) {
        return false;
    }
    if (est2[index] == placa) {
        int posicao_carro = index;
        int i = 0;
        
        while (posicao_carro + 1 < N && est2[posicao_carro + 1] != 0) {
            manobra[i] = est2[posicao_carro + 1];
            est2[posicao_carro + 1] = 0;
            posicao_carro++;
            i++;
        }
        
        est2[index] = 0;
        livres++;
        printf("Carro %d retirado da vaga E2-%d.\n", placa, index + 1);
        
        posicao_carro = index;
        i = 0;
        while (manobra[i] != 0) {
            est2[posicao_carro] = manobra[i];
            manobra[i] = 0;
            posicao_carro++;
            i++;
        }
        
        return true;
    }
    return retirar_recursive_est2(index + 1, placa);
}


void retirar(int placa) {
    if (!retirar_recursive_est1(0, placa)) {
        if (!retirar_recursive_est2(0, placa)) {
            printf("Carro %d nao encontrado no estacionamento.\n", placa);
        }
    }
}

void exibir_vagas_recursive(int arr[], int index) {
    if (index == N) {
        printf("\n");
        return;
    }
    printf("| %-5d ", arr[index]);
    exibir_vagas_recursive(arr, index + 1);
}

void exibir_estacionamentos() {
    printf("\n--- Estado Atual ---\n");
    printf("Estacionamento 1:\n");
    exibir_vagas_recursive(est1, 0);
    printf("Estacionamento 2:\n");
    exibir_vagas_recursive(est2, 0);
    printf("Area de Manobra:\n");
    exibir_vagas_recursive(manobra, 0);
    printf("--------------------\n");
}


int main() {
    int opcao, placa;

    do {
        exibir_estacionamentos();
        printf("Vagas totais: %d | Vagas livres: %d\n", vagas, livres);
        printf("\nMenu:\n");
        printf("1 - Estacionar Carro\n");
        printf("2 - Retirar Carro\n");
        printf("0 - Fechar Programa\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
             printf("Entrada invalida. Por favor, insira um numero.\n");
             while (getchar() != '\n');
             opcao = -1;
             continue;
        }

        switch (opcao) {
            case 1:
                if (estaCheio()) {
                    printf("Estacionamento cheio! Nao e possivel estacionar.\n");
                } else {
                    printf("Digite a placa do carro para estacionar: ");
                     if (scanf("%d", &placa) != 1) {
                        printf("Entrada invalida para placa.\n");
                         while (getchar() != '\n');
                    } else {
                         if (placa <= 0) {
                            printf("Placa invalida. Use um numero positivo.\n");
                         } else {
                            estacionar(placa);
                         }
                    }
                }
                break;
            case 2:
                 if (livres == vagas) {
                     printf("Estacionamento vazio! Nao ha carros para retirar.\n");
                 } else {
                    printf("Digite a placa do carro para retirar: ");
                    if (scanf("%d", &placa) != 1) {
                        printf("Entrada invalida para placa.\n");
                         while (getchar() != '\n');
                    } else {
                        if (placa <= 0) {
                            printf("Placa invalida. Use um numero positivo.\n");
                         } else {
                             retirar(placa);
                         }
                    }
                 }
                break;
            case 0:
                printf("Fechando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
        printf("\nPressione Enter para continuar...");
        while (getchar() != '\n');
        getchar();

    } while (opcao != 0);

    return 0;
}
