#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>
#include "codefun.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    bool sair = 0;
while(!sair){
    system("cls");
    int TAM=0, coluna=0, linha=0, i, j, k, contador = 1;

    do {
        printf ("\nDigite o tamanho do Sudoku: 4x4 , 9x9 , 16x16: ");
        scanf("%d", &TAM);

        if (TAM == 4 || TAM == 9 || TAM == 16){
            printf ("\nTamanho de matriz aceito.\n");
        }else {
            printf("\nEste tamanho n�o e v�lido.\n");
            TAM = 0;
        }

    } while (TAM == 0);
        system("cls");
    do {
        printf ("\nDigite em qual posi��o voce deseja inicar. Exemplo linha 3 x coluna 2: ");
        scanf("%d%d", &linha, &coluna);

        if (coluna >= 0 && coluna < TAM && linha >= 0 && linha < TAM){
            printf ("\nLinha e Coluna de tamanhos aceitos.\n");
            coluna = coluna;
            linha = linha;
        } else {
            printf("\nLinha ou coluna nao existente.\n");
            coluna = -1;
            linha = -1;
        }

    } while (coluna == -1);

    system("cls");

    int mat [TAM][TAM];

    for (i = 0; i < TAM ; i++){
        for (j = 0; j < TAM; j++){
                mat[i][j] = 0;
            }
        }

    mat[linha][coluna] = 1;

//-------------------------PRENCHIMENTO DA LINHA------------------------------//

    for ( i = coluna; i < TAM; i ++){
        mat[linha][i] = contador;
        contador++;
    }

    for ( i = 0; i < coluna; i ++){
        mat[linha][i] = contador;
        contador++;
    }

//--------------------------PRENCHIMENTO DAS COLUNA BASES------------------------------//

    contador =1 ;
    int auxmais, auxmenos, raix;

    raix = sqrt(TAM); //Calcula a raiz quadrada do tamanho que o usu�rio digitou
    auxmais = linha + raix;
    auxmenos = linha - raix;

    for (k = 1; k <= raix; k++){ //Percorre a primeira linha de cada conjunto, sendo que a distancia entre cada conjunto � a ra�z do tabuleiro
         contador =1 ;

        if (auxmais < TAM){
            for (i = coluna+k; i < TAM; i ++){
                mat[auxmais][i] = contador;
                contador++;
            }

            for ( i = 0; i < coluna+k; i ++){
                    mat[auxmais][i] = contador;
                    contador++;
                }

            auxmais = auxmais + raix;

        } else if (auxmenos >= 0){

            for ( i = coluna+k; i < TAM; i ++){
                mat[auxmenos][i] = contador;
                contador++;
            }

            for ( i = 0; i < coluna+k; i ++){
                mat[auxmenos][i] = contador;
                contador++;
            }
            auxmenos = auxmenos - raix;
        }
    }

//--------------------------PRENCHIMENTO DAS COLUNA RESTANTES------------------------------//

    if (linha == 0){
        for (i = 0; i < TAM-1; i++){
            if (mat [i][0] != 0){//Se a posi��o j� estiver preenchida
                contador = mat[i][raix-1] + 1;//O contador � igual a �ltima posi��o da linha +1
                if (mat[i+1][0] == 0){//Se a posi��o inicial na pr�xima linha for 0
                    for(j = 0; j < TAM; j++){
                        if (contador > TAM){ //Se o contador for maior que o n�mero de linhas/colunas do tabuleiro
                            contador = 1;//contador volta a ser 1
                        }
                        mat[i+1][j] = contador; //A prox�ma linha nas colunas de 0 a tamanho - 1, s�o iguais ao contador
                        contador++; //Aumenta o contador
                    }
                }
            }
        }
    } else if (linha == TAM-1){//Se a linha for a �ltima
        for (i = linha; i > 0; i--){//Verifica da linha at� o in�cio da matriz
            if (mat [i][0] != 0){//Se j� estiver preenchido
                contador = mat[i][raix-1]+1;//Contador � igual ao pr�ximo n�mero ap�s o fim da linha
                if (mat[i-1][0] == 0){//Se a linha anterior n�o tiver preenchida
                    for(j = 0; j < TAM; j++){
                        if (contador > TAM){
                            contador = 1;
                        }
                        mat[i-1][j] = contador;
                        contador++;
                    }
                }
            }
        }
    } else {
        int cou = 1;//Contador de quadrantes
        for (i = 0; i < TAM-1; i++){//Da primeira a �ltima linha
            if (mat [i][0] != 0){//Se a linha estiver preenchida
                contador = mat[i][raix-1]+1;
                if (mat[i+1][0] == 0){
                    for(j = 0; j < TAM; j++){
                        if (contador > TAM){
                            contador = 1;
                        }
                        mat[i+1][j] = contador; //Preenche a pr�xima linha
                        contador++;
                    }
                }
            }
            if ((cou+1) % raix == 0 && cou != 0){ //Se o contador +1 for ra�z exata e diferente de 0
                i = i+1;//Pula linha
                cou++;//Incrementa contador
            }
            cou++;//Sen�o, apenas incrementa
        }

        cou = TAM-1;//Contador a �ltima linha
        for (i = TAM-1; i > 0; i--){//Da �ltima a primeira linha
            if (mat [i][0] != 0){//Se estiver preenchido
                contador = mat[i+raix-2][raix-1]+1; //i+raiz-2 = Pega a �ltima posi��o preenchida
                if (mat[i-1][0]== 0){//Se a linha anterior estiver vazia
                    for(j = 0; j < TAM; j++){
                        if (contador > TAM){
                            contador = 1;
                        }
                        mat[i-1][j] = contador;
                        contador++;
                    }
                }
            }
            if ((cou-1) % raix == 0 && cou != TAM-1){//Se contador menos 1 for ra�z exata e n�o estiver na �ltima linha
                i = i-1; //Decrementa i
                cou--; //Decrementa o contador
            }
            cou--;
       }

   }

//-----------------------COLORA��O DO SUDOKU------------------------------//

    if (TAM == 4){ //Para o tamanho 4x4
        printf("\nSudoku: \n\n");
        for(i = 0; i < TAM; i++){ //Cada n�mero receber� uma cor, uma vez que com as regras do sudoku, as regras de colora��o j� s�o satisfeitas
            for (j = 0; j < TAM; j++){
                if (mat[i][j] == 1){
                    textcolor (BLUE, BLACK);
                } else if (mat[i][j] == 2){
                    textcolor (GREEN, BLACK);
                } else if (mat[i][j] == 3){
                    textcolor (PURPLE, BLACK);
                } else {
                    textcolor (RED, BLACK);
                }
                if (j % raix == 0){
                    printf("  ");
                }
                if (mat [i][j]< 10){
                    printf(" %d ", mat[i][j]);
                } else {
                    printf("%d ", mat[i][j]);
                }
            }
            if ((i+1) % raix == 0 ) {
                printf("\n\n");
            } else {
                printf ("\n");
            }
        }

    } else if (TAM == 9){ //Para o tamanho 9x9 e 16x16 as cores s�o distribu�das de acordo com a heur�stica de colora��o
        printf("\nSudoku: \n\n");
        for(i = 0; i < TAM; i++){
            for (j = 0; j < TAM; j++){
                if (mat[i][j] == 1){
                    textcolor (BLUE, BLACK);
                } else if (mat[i][j] == 2){
                    textcolor (GREEN, BLACK);
                } else if (mat[i][j]==3){
                    textcolor (PURPLE, BLACK);
                } else if (mat[i][j]==4){
                    textcolor (RED, BLACK);
                }else if(mat[i][j]==5){
                    textcolor (LIGHTBLUE, BLACK);
                }else if(mat[i][j]==6){
                    textcolor (LIGHTGREEN, BLACK);
                }else if(mat[i][j]==7){
                    textcolor (WHITE, BLACK);
                }else if(mat[i][j]==8){
                    textcolor (YELLOW, BLACK);
                }
                else if(mat[i][j]==9){
                    textcolor (LIGHTPURPLE, BLACK);
                }
                if (j % raix == 0){
                    printf("  ");
                }
                if (mat [i][j] < 10){
                    printf(" %d ", mat[i][j]);
                } else {
                    printf("%d ", mat[i][j]);
                }
            }
            if ((i+1) % raix == 0 ) {
                printf("\n\n");
            } else {
                printf ("\n");
            }
        }

    } else {
        printf("\nSudoku: \n\n");
        for(i = 0; i < TAM; i++){
            for (j = 0; j < TAM; j++){
               if (mat[i][j] == 1){
                    textcolor (BLUE, BLACK);
                } else if (mat[i][j] == 2){
                    textcolor (GREEN, BLACK);
                } else if (mat[i][j]==3){
                    textcolor (PURPLE, BLACK);
                } else if (mat[i][j]==4){
                    textcolor (RED, BLACK);
                }else if(mat[i][j]==5){
                    textcolor (LIGHTBLUE, BLACK);
                }else if(mat[i][j]==6){
                    textcolor (LIGHTGREEN, BLACK);
                }else if(mat[i][j]==7){
                    textcolor (WHITE, BLACK);
                }else if(mat[i][j]==8){
                    textcolor (YELLOW, BLACK);
                }
                else if(mat[i][j]==9){
                    textcolor (LIGHTPURPLE, BLACK);
                } else if(mat[i][j]==10){
                    textcolor (GRAY, BLACK);
                }else if(mat[i][j]==11){
                    textcolor (LIGHTRED, BLACK);
                }else if(mat[i][j]==12){
                    textcolor (LIGHTAQUA, BLACK);
                }else if(mat[i][j]==13){
                    textcolor (AQUA, BLACK);
                }else if(mat[i][j]==14){
                    textcolor (BLACK, WHITE);
                }else if(mat[i][j]==15){
                    textcolor (LIGHTYELLOW, BLACK);
                }else if(mat[i][j]==16){
                    textcolor (BRIGHTWHITE, BLACK);
                }
                if (j % raix == 0){
                    printf("  ");
                }
                if (mat [i][j]< 10){
                    printf(" %d ", mat[i][j]);
                } else {
                    printf("%d ", mat[i][j]);
                }
            }
            if ((i+1) % raix == 0 ) {
                printf("\n\n");
            } else {
                printf ("\n");
            }
        }
        textcolor(WHITE, BLACK);
    }
    textcolor(WHITE, BLACK);
    printf ("\n");
    printf ("Deseja jogar novamente?\n");
    printf ("          0 - SIM       \n");
    printf ("          1 - N�O       \n");
    scanf("%d",&sair);

}

    system("PAUSE");
    return 0;
}
