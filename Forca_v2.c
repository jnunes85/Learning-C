#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

//Variáveis globais
char palavraSecreta [TAMANHO_PALAVRA];
char chutes [26];
int chutesDados = 0;

//funções
void abertura() {
    printf("\n");
    printf("*****************************\n");
    printf("*       Jogo de Forca       *\n");
    printf("*****************************\n\n");
}

void adicionapalavra() {

    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo? (S/N)");
    scanf(" %c", &quer);
    
    if (quer == 'S') {

        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra?");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("\n Desculpe, banco de dados não disponível.\n\n");
            exit(1);
        }


        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d",qtd);
        
        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
    
}

void escolhePalavra(){
    FILE* f;

   f = fopen ("palavras.txt", "r");
   if(f ==0) {
        printf("\n Desculpe, banco de dados não disponível.\n\n");
        exit(1);
   }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavraSecreta);
    }

    fclose(f);
}

void chuta(){
    char chute;
        scanf(" %c", &chute);
        chutes [(chutesDados)] = chute;
        (chutesDados)++;
}

int jachutou (char letra){
    int achou = 0;

    for (int j = 0; j < chutesDados; j++) {
        if (chutes[j] == letra) {
            achou = 1;
            break;  
        }
    }
    return achou;
}

int acertou() {
    for (int i=0; i < strlen(palavraSecreta); i++) {
        if(!jachutou(palavraSecreta[i])) {
            return 0;
        }
    }

    return 1;

}


void desenhaForca(){
    for (int i= 0; i < strlen (palavraSecreta); i++) {
        
            int achou = jachutou (palavraSecreta[i]);     

            if (achou) {
                printf("%c ", palavraSecreta[i]);
            }   else {
                    printf("_ ");
            }
    }
    printf("\n");
}

int enforcou (){

    int erros = 0;
    
    for (int i = 0; i < chutesDados; i++){
        int existe = 0;
        
        for (int j = 0; j < strlen (palavraSecreta); j++){
            if (chutes[i] == palavraSecreta[j]){
                
                existe = 1;
                break;
            }
        }
    
        if (!existe) erros++;
    } 

    return erros >=5;  
}

int main(){

    escolhePalavra();
    abertura();

        do{ 
            desenhaForca();
            chuta();
        
        } while (!acertou() && !enforcou());

        if(acertou()) {

            printf("\nParabéns, você ganhou!\n\n");

            printf("      _______________      \n");
            printf("     ' .__==_==__=__.'     \n");
            printf("     .--\\:         /--.   \n");
            printf("    |  (|:.        | ) |   \n");
            printf("     .--|:.        |--     \n");
            printf("         \\::.       /     \n");
            printf("          '::.   . :       \n");
            printf("             )  (          \n");
            printf("             '  '          \n");
            printf("           _'   '_         \n");
            printf("         :'_______':       \n");
            printf("                           \n");

        } else {

            printf("\nPuxa, você foi encforcado!\n");
            printf(" A palavra era **%s**\n\n", palavraSecreta);

        }

    adicionapalavra();
}