#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10


//Uma estrutura que junta um nome, uma cor e um número de tropas
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;


//Uma função para imprimir títulos de uma forma mais destacada
void titulo(char* texto){
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


int main(){
    //Um vetor de structs Territorios
    Territorio* mapa = (Territorio*) calloc(NUM_TERRITORIOS, sizeof(Territorio));

    titulo("WAR ESTRUTURADO - CADASTRO ESTRUTURAL");

    cadastrar(mapa);

    printf("\n");
    printf("Cadastro inicial concluido com sucesso!\n");

    printf("\n");
    exibirMapa(mapa);

    int indiceAtacante;
    int indiceDefensor;
    printf("--- FASE DE ATAQUE ---\n");

    printf("Escolha o territorio atacante (1 a 5, ou 0 para sair): ");
    scanf("%d", &indiceAtacante);

    printf("Escolha o territorio defensor (1 a 5): ");
    scanf("%d", &indiceDefensor);
    atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);

    liberarMemoria(mapa);

}


void cadastrar(Territorio* mapa){
    //Um laço for para o cadastro dos territórios
    for (int i = 0; i < NUM_TERRITORIOS; i++){
        printf("\n");
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        
        printf("Nome do Territorio: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);

        printf("Cor do Exercito: (ex: Azul, Verde): ");
        fgets(mapa[i].cor, TAM_COR, stdin);

        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}


void exibirMapa(Territorio* mapa){
    titulo("MAPA DO MUNDO - ESTADO ATUAL");

    //Um laço for para mostrar cada um dos territórios cadastrado
    for (int i = 0; i < NUM_TERRITORIOS; i++){
        printf("%d. %s (Exercito s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}


void atacar(Territorio* atacante, Territorio* defensor){
    srand(time(NULL));
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    printf("O atacante %s rolou o dado e tirou: %d", atacante->nome, dadoAtacante);
    printf("O atacante %s rolou o dado e tirou: %d", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor){
        printf("VITORIA DO ATAQUE! ");
    }
}

void liberarMemoria(Territorio* mapa){
    free(mapa);
}
