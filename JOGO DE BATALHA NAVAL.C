#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 10

/* Habilidade:
   Usamos matriz 5x5 para as três habilidades (tamanho fixo para este exercício).
   - Cone: ponto de origem é o topo central da matriz (mat_origin_row = 0, mat_origin_col = center)
   - Cruz: origem é o centro da matriz (center, center)
   - Octaedro (vist frontal => losango/diamante): origem é o centro da matriz
*/

void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("\nTabuleiro (0=água, 3=navio, 5=área afetada):\n");
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

/* Constroi matriz do cone (5x5) dinamicamente usando condicionais.
   A ideia: na matriz 5x5, o topo é row 0; para cada row r, largura = 1 + 2*r
   (limitada pelo tamanho). Centro de coluna é center. */
void buildCone(int mat[5][5]) {
    int size = 5;
    int center = size / 2; // 2
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            // condição para estar dentro do "cone" com origem no topo
            if ( (c >= center - r) && (c <= center + r) ) {
                mat[r][c] = 1;
            } else {
                mat[r][c] = 0;
            }
        }
    }
}

/* Constroi matriz da cruz (5x5): linha do meio inteira e coluna do meio inteira */
void buildCross(int mat[5][5]) {
    int size = 5;
    int center = size / 2;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (r == center || c == center) mat[r][c] = 1;
            else mat[r][c] = 0;
        }
    }
}

/* Constroi matriz "octaedro" vista frontal = losango/diamante (5x5).
   Condição: abs(r-center) + abs(c-center) <= center  => posição dentro do diamante */
int abs_int(int x) { return x < 0 ? -x : x; }

void buildOcta(int mat[5][5]) {
    int size = 5;
    int center = size / 2;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (abs_int(r - center) + abs_int(c - center) <= center) mat[r][c] = 1;
            else mat[r][c] = 0;
        }
    }
}

/* Sobrepõe a matriz de habilidade ao tabuleiro.
   - board: tabuleiro 10x10
   - mat: matriz da habilidade (5x5)
   - matOriginRow, matOriginCol: coordenada dentro da matriz que representa
     o ponto de origem (a posição da habilidade). Ex.: cone tem origem (0,center),
     cruz e octaedro têm origem (center,center).
   - boardOriginRow, boardOriginCol: coordenadas no tabuleiro onde queremos posicionar a origem.
*/
void overlaySkill(int board[BOARD_SIZE][BOARD_SIZE], int mat[5][5],
                  int matOriginRow, int matOriginCol,
                  int boardOriginRow, int boardOriginCol) {

    int matSize = 5;
    for (int mi = 0; mi < matSize; ++mi) {
        for (int mj = 0; mj < matSize; ++mj) {
            if (mat[mi][mj] == 1) {
                int bi = boardOriginRow - matOriginRow + mi;
                int bj = boardOriginCol - matOriginCol + mj;
                // verificar limites do tabuleiro (condicional exigida)
                if (bi >= 0 && bi < BOARD_SIZE && bj >= 0 && bj < BOARD_SIZE) {
                    // Marca área afetada com valor 5 (diferente de 0 e 3).
                    // Observação: isto sobrescreve valores existentes (por exemplo navio=3).
                    // Se preferir NÃO sobrescrever navios, substitua a linha abaixo por:
                    // if (board[bi][bj] != 3) board[bi][bj] = 5;
                    board[bi][bj] = 5;
                }
            }
        }
    }
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    memset(board, 0, sizeof(board)); // inicializa tudo com 0 (água)

    // -- Colocando alguns navios de exemplo (valor 3) em posições fixas --
    // (Simplificação: posições definidas diretamente no código)
    board[2][2] = 3;
    board[2][3] = 3;
    board[2][4] = 3;
    board[5][7] = 3;
    board[6][7] = 3;

    // --- Criação das matrizes de habilidade (5x5) ---
    int cone[5][5];
    int cross[5][5];
    int octa[5][5];

    buildCone(cone);
    buildCross(cross);
    buildOcta(octa);

    // --- Definindo pontos de origem no tabuleiro para cada habilidade ---
    // As coordenadas são (linha, coluna). Definidas diretamente no código (requisito).
    // Ex.: cone origin será posicionado com seu topo central em (1,4)
    int cone_board_row = 1, cone_board_col = 4;
    int cross_board_row = 4, cross_board_col = 2;
    int octa_board_row = 7, octa_board_col = 7;

    // --- Definindo as coordenadas da origem dentro de cada matriz ---
    int matCenter = 5 / 2;
    int cone_mat_origin_row = 0;        // topo do cone
    int cone_mat_origin_col = matCenter;// coluna central
    int cross_mat_origin_row = matCenter;
    int cross_mat_origin_col = matCenter;
    int octa_mat_origin_row = matCenter;
    int octa_mat_origin_col = matCenter;

    // --- Sobrepondo habilidades no tabuleiro ---
    overlaySkill(board, cone, cone_mat_origin_row, cone_mat_origin_col, cone_board_row, cone_board_col);
    overlaySkill(board, cross, cross_mat_origin_row, cross_mat_origin_col, cross_board_row, cross_board_col);
    overlaySkill(board, octa, octa_mat_origin_row, octa_mat_origin_col, octa_board_row, octa_board_col);

    // --- Exibir o tabuleiro final ---
    printBoard(board);

    // --- (Opcional) imprimir as matrizes das habilidades individualmente para checagem ---
    printf("\nMatriz Cone (1=afetado):\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) printf("%d ", cone[i][j]);
        printf("\n");
    }

    printf("\nMatriz Cruz (1=afetado):\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) printf("%d ", cross[i][j]);
        printf("\n");
    }

    printf("\nMatriz Octaedro/Losango (1=afetado):\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) printf("%d ", octa[i][j]);
        printf("\n");
    }

    return 0;
}
