#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LINHAS 15
#define COLUNAS 20
int main() {
    char mapa[LINHAS][COLUNAS];
    int px = 1, py = 1;    //jogador
    int mx = 10, my = 8;   //Monstro
    int tx = 18, ty = 13;  //Tesouro
    int vida = 5;
    int pontos = 0;
    int x, y;
    char comando;
    srand (time(NULL));
    while (vida > 0) {
        //MONTA O MAPA

        for(y = 0;y < LINHAS; y++) {
            for (x = 0; x < COLUNAS; x++) {
                //bordas
                if (y == 0 || y == LINHAS -1 || x == 0 || x == COLUNAS -1) {
                    mapa[y][x]='#';
                }
                else {
                    mapa[y][x]='.';
                }
            }
        }
        //PAREDES INTERNAS
        for (x = 3; x < 10; x++) {
            mapa[5][x]='#';
        }
        for (y = 7; y < 12; y++) {
            mapa[y][12]='#';
        }
        //OBEJETOS
        mapa[py][px] = 'P';
        mapa[my][mx] = 'M';
        mapa[ty][tx] = '@';
        //LIMPAR TELA
        system("CLS");
        //DESENHAR MAPA
        for (y = 0; y<LINHAS; y++) {
            for (x = 0; x<COLUNAS; x++) {
                printf("%c", mapa[y][x]);
            }
            printf("\n");
        }
        //STATUS
        printf("\nVida: %d", vida);
        printf("\tPontos: %d\n", pontos);
        printf("\nC = cima");
        printf("\nB = baixo");
        printf("\nE = esquerda");
        printf("\nD = direita");
        printf("\n\nComando:");
        scanf("%c", &comando);
        //MOVIMENTO DO JOGADOR
        int novoX = px;
        int novoy = py;
        switch (comando) {
            case 'C':
            case 'c':
                novoy--;
                break;
            case 'B':
            case 'b':
                novoy++;
                break;
            case 'E':
            case 'e':
                novoX--;
                break;
            case 'D':
            case 'd':
                novoX++;
                break;
        }
        //SÓ MOVE SE NÃO FOR PAREDE
        if (mapa[novoy][novoX] !='#') {
            px=novoX;
            py=novoy;
        }
        //MONSTRO PERSEGUE PLAYER
        if (mx < px) {
            if (mapa[my][mx + 1] !='#')
                mx++;
        }
        if (mx > px) {
            if (mapa[my][mx - 1] != '#')
                mx--;
        }
        if (my < py) {
            if (mapa[my + 1][mx] != '#')
                my++;
        }
        else if (my > py) {
            if (mapa[my - 1][mx] != '#')
                my--;
        }
        //COLISÃO COM O MOSNTRO
        if (px == mx && py == my) {
            vida--;

            printf("\nO monstro atacou você!");
            printf("\nVida restante: %d\n", vida);
            system("PAUSE");
            //REPOSICIONAR JOGADOR
            px = 1;
            py = 1;
        }
        //PEGOU TESOURO
        if (px == tx && py == ty){
            pontos +=100;
            printf("\nVoce encontrou o tesouro!");
            printf("\nPontos: %d\n", pontos);
            system("PAUSE");
            //NOVO TESOURO EM POSIÇÃO ALEATORIA
            tx = rand()%(COLUNAS - 2) + 1;
            ty = rand()%(LINHAS - 2) + 1;
            //EVITAR NASCER PAREDE
            while (mapa[ty][tx] == "#") {
                tx = rand()%(COLUNAS - 2) + 1;
                ty = rand()%(LINHAS - 2) + 1;
            }
        }
    }
    //GAME OVER
    system("CLS");
    printf("GAME OVER\n");
    printf("Pontuação Final: %d\n", pontos);
    return 0;
    }