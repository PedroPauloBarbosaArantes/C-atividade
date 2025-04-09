#include <stdio.h>
#include <locale.h>

int est1[5] = {0, 0, 0, 0, 0};  
int est2[5] = {0, 0, 0, 0, 0}; 
int vagas = 10;
int livres = 10;

int estaCheio() {
    return livres == 0;  
}

int estaVazio() {
    return livres == 10;  
}

void manobrar() {
    int i = 0, j = 0;

    while (i < 5 && est1[i] == 0) i++; 
    if (i < 5) { 
        while (j < 5 && est2[j] != 0) j++; 
        if (j < 5) { 
            est2[j] = est1[i];  
            est1[i] = 0;         
            livres++;           
            printf("Carro com placa %d movido de est1 para est2, vaga %d.\n\n", est2[j], j);
            return;
        }
    }

    i = 0;
    while (i < 5 && est2[i] == 0) i++; 
    if (i < 5) { 
        while (j < 5 && est1[j] != 0) j++; 
        if (j < 5) { 
            est1[j] = est2[i];  
            est2[i] = 0;         
            livres++;            
            printf("Carro com placa %d movido de est2 para est1, vaga %d.\n\n", est1[j], j);
            return;
        }
    }
    
    printf("Nao foi possivel realizar a manobra. Estacionamentos cheios!\n\n");
}

void estacionar(int placa) {
    if (estaCheio()) {
        printf("Estacionamento cheio! Nao eh possivel estacionar.\n\n");
        return;
    }

    int i = 0;
    while (i < 5 && est1[i] != 0) i++;  
    if (i < 5) {
        est1[i] = placa; 
        livres--;
        printf("Carro com placa %d estacionado em est 1, vaga %d.\n\n", placa, i);
        return;
    }

    i = 0;
    while (i < 5 && est2[i] != 0) i++; 
    if (i < 5) {
        est2[i] = placa;  
        livres--;
        printf("Carro com placa %d estacionado em est 2, vaga %d.\n\n", placa, i);
        return;
    }
}

void retirar(int placa) {
    int i = 0;
    while (i < 5 && est1[i] != placa) i++;  
    if (i < 5) {
        est1[i] = 0;  
        livres++;
        printf("Carro com placa %d retirado de est1, vaga %d.\n\n", placa, i);
        return;
    }

    i = 0;
    while (i < 5 && est2[i] != placa) i++;  
    if (i < 5) {
        est2[i] = 0;  
        livres++;
        printf("Carro com placa %d retirado de est2, vaga %d.\n\n", placa, i);
        return;
    }

    printf("Carro com placa %d nao encontrado.\n\n", placa);
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opcao, placa;

    while (1) {
        printf("Vagas disponiveis: %d\n\n", livres);
        printf("1 -> Inserir Carro\n\n");
        printf("2 -> Retirar Carro\n\n");
        printf("3 -> Realizar Manobra\n\n");
        printf("0 -> Fechar Sistema\n\n");
        printf("Escolha uma das opcoes! ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Informe a placa do carro para estacionar\n\n: ");
            scanf("%d", &placa);
            estacionar(placa);
        } else if (opcao == 2) {
            printf("Informe a placa do carro para retirar\n\n: ");
            scanf("%d", &placa);
            retirar(placa);
        } else if (opcao == 3) {
            manobrar();
        } else if (opcao == 0) {
            break;
        } else {
            printf("Opcao invalida!\n\n");
        }
    }

    printf("Sistema fechado.\n\n");
    return 0;
}

