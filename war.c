#include <stdio.h>
#include <string.h>

const int NumeroTerritorios = 5;

//Uma função para imprimir títulos de uma forma mais destacada
void titulo(char texto[38]){
    for (int i = 0; i < 38; i++){
        printf("=");
    }
    printf("\n");
    for (int i = 0; i < (38 - strlen(texto)) / 2; i++){
        printf(" ");
    }
    printf("%s\n", texto);
    for (int i = 0; i < 38; i++){
        printf("=");
    }
    printf("\n\n");
}

//Uma estrutura que junta um nome, uma cor e um número de tropas
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main(){
    //Um vetor de structs Territorios
    struct Territorio territorios[NumeroTerritorios];

    titulo("WAR ESTRUTURADO - CADASTRO ESTRUTURAL");

    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");

    //Um laço for para o cadastro dos territórios
    for (int i = 0; i < NumeroTerritorios; i++){
        printf("\n");
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        
        printf("Nome do Territorio: ");
        scanf("%s", &territorios[i].nome);

        printf("Cor do Exercito: (ex: Azul, Verde): ");
        scanf("%s", &territorios[i].cor);

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    printf("\n");
    printf("Cadastro inicial concluido com sucesso!\n");

    printf("\n");
    titulo("MAPA DO MUNDO - ESTADO ATUAL");

    //Um laço for para mostrar cada um dos territórios cadastrado
    for (int i = 0; i < NumeroTerritorios; i++){
        printf("TERRITORIO %d:\n", i + 1);
        printf("   - Nome: %s\n", territorios[i].nome);
        printf("   - Dominado por: Exercito %s\n", territorios[i].cor);
        printf("   - Tropas: %d\n", territorios[i].tropas);
        printf("\n");
    }
}