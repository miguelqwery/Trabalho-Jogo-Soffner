#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 15
#define COLUNAS 20

int main() {

    char mapa[LINHAS][COLUNAS];

    int px = 1, py = 1;      // Jogador
    int mx = 10, my = 8;     // Monstro
    int tx = 18, ty = 13;    // Tesouro

    int vida = 5;
    int pontos = 0;

    int x, y;
    char comando;

    srand(time(NULL));

    while (vida > 0) {

        // LIMPA O MAPA
        for (y = 0; y < LINHAS; y++) {
            for (x = 0; x < COLUNAS; x++) {

                // Bordas
                if (y == 0 || y == LINHAS - 1 ||
                    x == 0 || x == COLUNAS - 1) {

                    mapa[y][x] = '#';
                }
                else {
                    mapa[y][x] = '.';
                }
            }
        }

        // PAREDES INTERNAS
        for (x = 3; x < 10; x++) {
            mapa[5][x] = '#';
        }

        for (y = 7; y < 12; y++) {
            mapa[y][12] = '#';
        }

        // OBJETOS
        mapa[py][px] = 'P';
        mapa[my][mx] = 'M';
        mapa[ty][tx] = '@';

        // LIMPA A TELA (melhor para CLion)
        fflush(stdout);
        printf("\033[H\033[J");

        // DESENHA MAPA
        for (y = 0; y < LINHAS; y++) {
            for (x = 0; x < COLUNAS; x++) {
                printf("%c", mapa[y][x]);
            }
            printf("\n");
        }

        // STATUS
        printf("\nVida: %d", vida);
        printf("\tPontos: %d\n", pontos);

        printf("\nC = cima");
        printf("\nB = baixo");
        printf("\nE = esquerda");
        printf("\nD = direita");

        printf("\n\nComando: ");

        scanf(" %c", &comando);

        // MOVIMENTO DO JOGADOR
        int novoX = px;
        int novoY = py;

        switch (comando) {

            case 'C':
            case 'c':
                novoY--;
                break;

            case 'B':
            case 'b':
                novoY++;
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

        // SÓ MOVE SE NÃO FOR PAREDE
        if (mapa[novoY][novoX] != '#') {
            px = novoX;
            py = novoY;
        }

        // MONSTRO PERSEGUE PLAYER

        // Movimento X
        if (mx < px) {

            if (mapa[my][mx + 1] != '#') {
                mx++;
            }

        }
        else if (mx > px) {

            if (mapa[my][mx - 1] != '#') {
                mx--;
            }
        }

        // Movimento Y
        if (my < py) {

            if (mapa[my + 1][mx] != '#') {
                my++;
            }

        }
        else if (my > py) {

            if (mapa[my - 1][mx] != '#') {
                my--;
            }
        }

        // COLISÃO COM MONSTRO
        if (px == mx && py == my) {

            vida--;

            printf("\n\nO monstro atacou voce!");
            printf("\nVida restante: %d\n", vida);

            system("pause");

            // REPOSICIONA PLAYER
            px = 1;
            py = 1;
        }

        // PEGOU TESOURO
        if (px == tx && py == ty) {

            pontos += 100;

            printf("\n\nVoce encontrou o tesouro!");
            printf("\nPontos: %d\n", pontos);

            system("pause");

            // NOVO TESOURO
            do {

                tx = rand() % (COLUNAS - 2) + 1;
                ty = rand() % (LINHAS - 2) + 1;

            } while (
                mapa[ty][tx] == '#' ||
                (tx == px && ty == py) ||
                (tx == mx && ty == my)
            );
        }
    }

    // GAME OVER
    printf("\033[H\033[J");

    printf("GAME OVER\n");
    printf("Pontuacao final: %d\n", pontos);

    return 0;
}