#include <stdio.h>

int main() {
    // -------------------------------
    // CONFIGURAÇÕES INICIAIS
    // -------------------------------
    const int TAM = 10;      // Tamanho do tabuleiro (10x10)
    const int TAM_NAVIO = 3; // Tamanho fixo dos navios (3 posições)

    int tabuleiro[TAM][TAM]; // Matriz que representa o tabuleiro
    int i, j;                // Variáveis de controle para loops

    // -------------------------------
    // INICIALIZAR TABULEIRO
    // -------------------------------
    // 0 = água
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // -------------------------------
    // DEFINIR POSIÇÕES DOS NAVIOS
    // -------------------------------
    // Cada navio será representado pelo valor 3 no tabuleiro.
    // As coordenadas iniciais são definidas diretamente no código.

    // Navio 1 → Horizontal (linha, coluna inicial)
    int linhaH = 2;
    int colunaH = 4;

    // Navio 2 → Vertical (linha inicial, coluna)
    int linhaV = 5;
    int colunaV = 7;

    // -------------------------------
    // VALIDAR E POSICIONAR NAVIO HORIZONTAL
    // -------------------------------
    if (colunaH + TAM_NAVIO <= TAM) { // Garante que o navio cabe no tabuleiro
        for (i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaH][colunaH + i] = 3;
        }
    } else {
        printf("ERRO: Navio horizontal fora dos limites do tabuleiro.\n");
        return 1;
    }

    // -------------------------------
    // VALIDAR E POSICIONAR NAVIO VERTICAL
    // -------------------------------
    if (linhaV + TAM_NAVIO <= TAM) { // Garante que o navio cabe no tabuleiro
        int sobreposicao = 0;
        for (i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaV + i][colunaV] == 3) {
                sobreposicao = 1;
                break;
            }
        }

        if (sobreposicao == 0) {
            for (i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = 3;
            }
        } else {
            printf("ERRO: Navios se sobrepõem!\n");
            return 1;
        }

    } else {
        printf("ERRO: Navio vertical fora dos limites do tabuleiro.\n");
        return 1;
    }

    // -------------------------------
    // EXIBIR TABULEIRO
    // -------------------------------
    printf("\n===== TABULEIRO BATALHA NAVAL =====\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Água | 3 = Navio\n");

    return 0;
}
