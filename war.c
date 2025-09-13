#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define TAM_NOME 30
#define TAM_COR 10

const int numTerritorios = 5;


//Uma estrutura que junta um nome, uma cor e um número de tropas
struct Territorio{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
    char missao[];
};

void limparBufferEntrada();
void cadastrar(struct Territorio* mapa);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void atribuirMissao(char* destino, char* missoes[]);
int verificarMissao(char* missao, struct Territorio* mapa);
void exibirMissao(char* missao);
void exibirMapa(struct Territorio* mapa);
void liberarMemoria(struct Territorio* mapa, char* missao);


int main(){
    struct Territorio* mapa = (struct Territorio*) malloc(numTerritorios * sizeof(struct Territorio));
    char* missoes[] = {"Eliminar o exercito vermelho", "Conquistar 3 territorios", "Eliminar o exercito Amarelo", "Conquistar 4 territorios", "Eliminar o exercito verde"};
    char* missaoJogador = malloc(30 * sizeof(char));


    cadastrar(mapa);
    atribuirMissao(missaoJogador, missoes);

    while(1){
        exibirMapa(mapa);
        exibirMissao(missaoJogador);
        int missaoCumprida = 0;

        int indiceAtacante;
        int indiceDefensor;
        printf("\n--- FASE DE ATAQUE ---\n");

        while(1){
            printf("Escolha o territorio atacante (1 a %d): ", numTerritorios);
            scanf("%d", &indiceAtacante);
            limparBufferEntrada();
                
            if (indiceAtacante == 0){
                liberarMemoria(mapa, missaoJogador);
                exit(0);
            }

            printf("Escolha o territorio defensor (1 a %d): ", numTerritorios);
            scanf("%d", &indiceDefensor);
            limparBufferEntrada();

            if(strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) != 0){
                break;
            }
            printf("Nao e possivel atacar um exercito da mesma cor!\n");
        }
        atacar(&mapa[indiceAtacante-1], &mapa[indiceDefensor-1]);
        missaoCumprida = verificarMissao(missaoJogador, mapa);

        if(missaoCumprida){
            printf("PARABENS, VOCE VENCEU!!\n");
            break;
        }

        printf("Pressione Enter para continuar para o proximo turno...");
        getchar();
    }

    liberarMemoria(mapa, missaoJogador);


}


void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void atribuirMissao(char* destino, char* missoes[]){
    srand(time(NULL));
    strcpy(destino, missoes[rand() % 5]);
    
}


void cadastrar(struct Territorio* mapa){

    char* nomes[] = {"America", "Europa", "Asia", "Africa", "Oceania"};
    char* cores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Branco"};

    //Um laço for para o cadastro dos territórios
    for (int i = 0; i < numTerritorios; i++){
        
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = i + 1;
    }
}


void exibirMapa(struct Territorio* mapa){
    printf("\n==============MAPA DO MUNDO - ESTADO ATUAL==============\n");

    //Um laço for para mostrar cada um dos territórios cadastrados
    for (int i = 0; i < numTerritorios; i++){
        printf("%d. %s \t(Exercito: %s \t, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("========================================================\n");
}


void exibirMissao(char* missao){
    printf("\n--- SUA MISSAO (Exercito Azul) ---\n");
    printf("%s.\n", missao);
}


void atacar(struct Territorio* atacante, struct Territorio* defensor){

    srand(time(NULL));
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Ataque (%s): %d", atacante->nome, dadoAtacante);
    printf(" | ");
    printf("Defesa (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor){
        printf("VITORIA DO ATAQUE!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas = atacante->tropas / 2 + atacante->tropas % 2;
    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu uma tropa.\n");
        atacante->tropas--;
    }
}


int verificarMissao(char* missao, struct Territorio* mapa){
    if(strcmp(missao, "Eliminar o exercito vermelho") == 0){
        for(int i = 0; i < numTerritorios; i++){
            if(strcmp(mapa[i].cor, "Vermelho") == 0){
                return 0;
            }
        }
        return 1;
    }
    if(strcmp(missao, "Conquistar 3 territorios") == 0){
        int azuis = 0;
        for(int i = 0; i < numTerritorios; i++){
            if(strcmp(mapa[i].cor, "Azul") == 0){
                azuis++;
            }
        }
        return(azuis > 3);
    }
    if(strcmp(missao, "Eliminar o exercito Amarelo") == 0){
        for(int i = 0; i < numTerritorios; i++){
            if(strcmp(mapa[i].cor, "Amarelo") == 0){
                return 0;
            }
        }
        return 1;
    }
    if(strcmp(missao, "Conquistar 4 territorios") == 0){
        int azuis = 0;
        for(int i = 0; i < numTerritorios; i++){
            if(strcmp(mapa[i].cor, "Azul") == 0){
                azuis++;
            }
        }
        return(azuis > 4);
    }
    if(strcmp(missao, "Eliminar o exercito verde") == 0){
        for(int i = 0; i < numTerritorios; i++){
            if(strcmp(mapa[i].cor, "Verde") == 0){
                return 0;
            }
        }
        return 1;
    }
}


void liberarMemoria(struct Territorio* mapa, char* missao){
    free(mapa);
    free(missao);
    mapa = NULL;
    missao = NULL;
    printf("Memoria liberada!\n");
}
