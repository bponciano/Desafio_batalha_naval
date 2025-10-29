#include <stdio.h>

int main() {
    // -------------------------------
    // CONFIGURAÇÕES INICIAIS
    // -------------------------------
    const int TAM = 10;      // Tamanho fixo do tabuleiro (10x10)
    const int TAM_NAVIO = 3; // Tamanho fixo dos navios (3 posições)
    int tabuleiro[TAM][TAM]; // Matriz que representa o tabuleiro
    int i, j;

    // -------------------------------
    // INICIALIZAR TABULEIRO
    // -------------------------------
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }

    // -------------------------------
    // DEFINIR POSIÇÕES DOS NAVIOS
    // -------------------------------
    // Navio 1 → Horizontal
    int linhaH = 2;
    int colunaH = 3;

    // Navio 2 → Vertical
    int linhaV = 5;
    int colunaV = 1;

    // Navio 3 → Diagonal principal (↘)
    int linhaD1 = 0;
    int colunaD1 = 0;

    // Navio 4 → Diagonal secundária (↙)
    int linhaD2 = 2;
    int colunaD2 = 9;

    int sobreposicao = 0; // Flag para detectar colisões

    // -------------------------------
    // FUNÇÃO AUXILIAR PARA TESTAR SOBREPOSIÇÃO
    // -------------------------------
    // (Feita inline para simplificar o desafio)
    #define CHECAR_SOBREPOSICAO(l, c) (tabuleiro[(l)][(c)] == 3)

    // -------------------------------
    // POSICIONAR NAVIO HORIZONTAL
    // -------------------------------
    if (colunaH + TAM_NAVIO <= TAM) {
        for (i = 0; i < TAM_NAVIO; i++) {
            if (CHECAR_SOBREPOSICAO(linhaH, colunaH + i)) sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (i = 0; i < TAM_NAVIO; i++)
                tabuleiro[linhaH][colunaH + i] = 3;
        }
    }

    // -------------------------------
    // POSICIONAR NAVIO VERTICAL
    // -------------------------------
    sobreposicao = 0;
    if (linhaV + TAM_NAVIO <= TAM) {
        for (i = 0; i < TAM_NAVIO; i++) {
            if (CHECAR_SOBREPOSICAO(linhaV + i, colunaV)) sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (i = 0; i < TAM_NAVIO; i++)
                tabuleiro[linhaV + i][colunaV] = 3;
        }
    }

    // -------------------------------
    // POSICIONAR NAVIO DIAGONAL PRINCIPAL (↘)
    // -------------------------------
    sobreposicao = 0;
    if (linhaD1 + TAM_NAVIO <= TAM && colunaD1 + TAM_NAVIO <= TAM) {
        for (i = 0; i < TAM_NAVIO; i++) {
            if (CHECAR_SOBREPOSICAO(linhaD1 + i, colunaD1 + i)) sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (i = 0; i < TAM_NAVIO; i++)
                tabuleiro[linhaD1 + i][colunaD1 + i] = 3;
        }
    }

    // -------------------------------
    // POSICIONAR NAVIO DIAGONAL SECUNDÁRIA (↙)
    // -------------------------------
    sobreposicao = 0;
    if (linhaD2 + TAM_NAVIO <= TAM && colunaD2 - TAM_NAVIO + 1 >= 0) {
        for (i = 0; i < TAM_NAVIO; i++) {
            if (CHECAR_SOBREPOSICAO(linhaD2 + i, colunaD2 - i)) sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (i = 0; i < TAM_NAVIO; i++)
                tabuleiro[linhaD2 + i][colunaD2 - i] = 3;
        }
    }

    // -------------------------------
    // EXIBIR TABULEIRO
    // -------------------------------
    printf("\n===== TABULEIRO BATALHA NAVAL =====\n\n");

    // Cabeçalho das colunas
    printf("    ");
    for (j = 0; j < TAM; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Linha separadora
    printf("   --------------------\n");

    // Imprimir tabuleiro
    for (i = 0; i < TAM; i++) {
        printf("%2d | ", i);
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Água | 3 = Navio\n");

    return 0;
}
