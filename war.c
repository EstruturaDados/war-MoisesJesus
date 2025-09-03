#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define TAM_NOME 30
#define TAM_COR 10


//Uma estrutura que junta um nome, uma cor e um número de tropas
struct Territorio{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};


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


void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void atacar(struct Territorio* atacante, struct Territorio* defensor){

    srand(time(NULL));
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou o dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou o dado e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor){
        printf("VITORIA DO ATAQUE!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas = atacante->tropas / 2 + atacante->tropas % 2;
    } else {
        printf("VITORIA DA DEFESA!\n");
        atacante->tropas--;
    }
}

void liberarMemoria(struct Territorio* mapa){
    free(mapa);
    mapa = NULL;
    printf("Memoria liberada!\n");
}


int main(){

    titulo("WAR ESTRUTURADO - CADASTRO ESTRUTURAL");
    //Pedindo o número de territórios que serão cadastrados
    int numTerritorios;
    char input[10];
    printf("Quantos territorios cadastraras: ");
    while(fgets(input, sizeof(input), stdin)){
        if(sscanf(input, "%d", &numTerritorios)){
            if(numTerritorios > 0){
                break;
            }
        } else{
            printf("Use um numero inteiro maior que zero!\nQuantos territorios cadastraras: ");
        }
    }
    struct Territorio* mapa = (struct Territorio*) malloc(numTerritorios * sizeof(struct Territorio));

    //Um laço for para o cadastro dos territórios
    for (int i = 0; i < numTerritorios; i++){
        
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        
        printf("Nome do Territorio: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);

        printf("Cor do Exercito: (ex: Azul, Verde): ");
        fgets(mapa[i].cor, TAM_COR, stdin);

        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Numero de Tropas: ");
        while(fgets(input, sizeof(input), stdin)){
            if(sscanf(input, "%d", &mapa[i].tropas)){
                if(mapa[i].tropas > 0){
                    break;
                }
            } else{
            printf("Use um numero inteiro maior que zero!\nNumero de tropas: ");
            }
        }
    }
    
    printf("\nCadastro inicial concluido com sucesso!\n\n");

    while(1){
        titulo("MAPA DO MUNDO - ESTADO ATUAL");

        //Um laço for para mostrar cada um dos territórios cadastrados
        for (int i = 0; i < numTerritorios; i++){
            printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }

        printf("\n--- FASE DE ATAQUE ---\n");

        int indiceAtacante;
        int indiceDefensor;
        while(1){
            printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", numTerritorios);
            scanf("%d", &indiceAtacante);
            limparBufferEntrada();
                
            if (indiceAtacante == 0){
                liberarMemoria(mapa);
                exit(0);
            }

            printf("Escolha o territorio defensor (1 a %d): ", numTerritorios);
            scanf("%d", &indiceDefensor);
            limparBufferEntrada();

            int i = 0;
            char chrAtacante;
            char chrDefensor;
            int corDiferente = 0;
            do{
                chrAtacante = mapa[indiceAtacante-1].cor[i];
                chrDefensor = mapa[indiceDefensor-1].cor[i];
                if(chrAtacante != chrDefensor){
                    corDiferente = 1;
                    break;
                }
                i++;

            }while(mapa[indiceAtacante-1].cor[i] != '\0' && mapa[indiceDefensor-1].cor[i] != '\0');

            if(corDiferente){
                break;
            }
            printf("Nao e possivel atacar um exercito da mesma cor!\n");
        }
    atacar(&mapa[indiceAtacante-1], &mapa[indiceDefensor-1]);

    printf("Pressione Enter para continuar para o proximo turno...");
    getchar();
    }

    liberarMemoria(mapa);

}