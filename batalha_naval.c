#include <stdio.h>

#define TAM 10         // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3    // Tamanho fixo dos navios
#define SK_C 7         // Tamanho das matrizes de habilidade (usar 7x7)
                     // (escolhi 7 para dar área razoável; pode ser alterado)
                     
int main() {
    int tab[TAM][TAM];
    int i, j, k;

    // ---------------------------
    // 1) Inicializar tabuleiro
    // ---------------------------
    // 0 = água
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tab[i][j] = 0;
        }
    }

    // ---------------------------
    // 2) Posicionar 4 navios (val = 3)
    //    - Navio horizontal
    //    - Navio vertical
    //    - Navio diagonal principal (↘)
    //    - Navio diagonal secundária (↙)
    // Coordenadas definidas diretamente aqui (simplificação do desafio)
    // ---------------------------

    // Navio 1 - Horizontal (linha, coluna_inicial)
    int h1_l = 1, h1_c = 1; // Exemplo: começa em (1,1), ocupa (1,1),(1,2),(1,3)

    // Navio 2 - Vertical (linha_inicial, coluna)
    int v1_l = 4, v1_c = 6; // Exemplo: ocupa (4,6),(5,6),(6,6)

    // Navio 3 - Diagonal principal (↘) (linha_inicial, coluna_inicial)
    int d1_l = 2, d1_c = 7; // Exemplo: (2,7),(3,8),(4,9)

    // Navio 4 - Diagonal secundária (↙) (linha_inicial, coluna_inicial)
    int d2_l = 6, d2_c = 2; // Exemplo: (6,2),(7,1),(8,0)

    // Função inline: verificar limites (retorna 1 se dentro dos limites)
    #define DENTRO_TAB(l,c) (((l) >= 0 && (l) < TAM) && ((c) >= 0 && (c) < TAM))

    // Colocar navio horizontal - validar limites e sobreposição
    for (i = 0; i < TAM_NAVIO; i++) {
        int rl = h1_l;
        int rc = h1_c + i;
        if (!DENTRO_TAB(rl, rc)) {
            printf("Erro: navio horizontal 1 fora dos limites (%d,%d)\n", rl, rc);
            return 1;
        }
        if (tab[rl][rc] == 3) {
            printf("Erro: sobreposição detectada ao posicionar navio horizontal.\n");
            return 1;
        }
        tab[rl][rc] = 3;
    }

    // Colocar navio vertical
    for (i = 0; i < TAM_NAVIO; i++) {
        int rl = v1_l + i;
        int rc = v1_c;
        if (!DENTRO_TAB(rl, rc)) {
            printf("Erro: navio vertical 1 fora dos limites (%d,%d)\n", rl, rc);
            return 1;
        }
        if (tab[rl][rc] == 3) {
            printf("Erro: sobreposição detectada ao posicionar navio vertical.\n");
            return 1;
        }
        tab[rl][rc] = 3;
    }

    // Colocar navio diagonal principal (↘)
    for (i = 0; i < TAM_NAVIO; i++) {
        int rl = d1_l + i;
        int rc = d1_c + i;
        if (!DENTRO_TAB(rl, rc)) {
            printf("Erro: navio diagonal principal fora dos limites (%d,%d)\n", rl, rc);
            return 1;
        }
        if (tab[rl][rc] == 3) {
            printf("Erro: sobreposição detectada ao posicionar navio diagonal principal.\n");
            return 1;
        }
        tab[rl][rc] = 3;
    }

    // Colocar navio diagonal secundária (↙)
    for (i = 0; i < TAM_NAVIO; i++) {
        int rl = d2_l + i;
        int rc = d2_c - i;
        if (!DENTRO_TAB(rl, rc)) {
            printf("Erro: navio diagonal secundária fora dos limites (%d,%d)\n", rl, rc);
            return 1;
        }
        if (tab[rl][rc] == 3) {
            printf("Erro: sobreposição detectada ao posicionar navio diagonal secundária.\n");
            return 1;
        }
        tab[rl][rc] = 3;
    }

    // ---------------------------
    // 3) Definir matrizes de habilidade dinamicamente (usando condicionais)
    //    Cada matriz é SK_C x SK_C (7x7)
    //    - Cone (aponta para baixo): top-centered expandindo para baixo
    //    - Cruz (cross): linha central e coluna central = área
    //    - Octaedro (vista frontal -> losango/diamond)
    // ---------------------------
    int cone[SK_C][SK_C];
    int cruz[SK_C][SK_C];
    int octa[SK_C][SK_C];

    // Centro das matrizes
    int center = SK_C / 2; // para SK_C = 7, center = 3

    // Construir CONE (ponta no topo, expandindo para baixo)
    // Regra: em cada linha r (0..SK_C-1), a largura ativa é r (0-based), centralizada.
    // Assim a "ponta" será linha 0: 1 célula (col center), linha 1: 3 células (center-1..center+1), etc.
    for (i = 0; i < SK_C; i++) {
        for (j = 0; j < SK_C; j++) {
            // calcular deslocamento da coluna central
            int row = i;
            int dist_col = j - center;
            // largura desejada = row*2 + 1 (mas limitada a SK_C)
            // se |dist_col| <= row então pertence ao cone
            if ( (row <= center) && ( (dist_col <= row) && (dist_col >= -row) ) ) {
                cone[i][j] = 1;
            } else {
                // Para linhas abaixo do center (opcional): cap the cone at center
                // Mantemos 0 além da metade para um cone "triangular"
                cone[i][j] = 0;
            }
        }
    }

    // Construir CRUZ: linha center e coluna center ativadas (mais uma "largura" = 1)
    for (i = 0; i < SK_C; i++) {
        for (j = 0; j < SK_C; j++) {
            if (i == center || j == center) cruz[i][j] = 1;
            else cruz[i][j] = 0;
        }
    }

    // Construir OCTAEDRO (vista frontal = losango / diamond)
    // Condição de diamond: |i - center| + |j - center| <= radius
    // Escolher radius = center (para preencher até borda do SK_C central)
    int radius = center; // por exemplo 3 para SK_C=7
    for (i = 0; i < SK_C; i++) {
        for (j = 0; j < SK_C; j++) {
            int manhattan = (i > center ? i - center : center - i) + (j > center ? j - center : center - j);
            if (manhattan <= radius) octa[i][j] = 1;
            else octa[i][j] = 0;
        }
    }

    // ---------------------------
    // 4) Integrar (sobrepor) habilidades ao tabuleiro
    //    - Definir pontos de origem no tabuleiro (centro da sobreposição)
    //    - Ao aplicar: se célula da habilidade == 1 então marcar o tabuleiro:
    //         se tab == 3 (navio) -> marcar com 8 (indica navio + área)
    //         se tab == 0 -> marcar com 5 (apenas área)
    //    - Certificar-se de não acessar índices fora dos limites
    // ---------------------------

    // Pontos de origem (lin, col) para cada habilidade (definidos diretamente)
    int origem_cone_l = 0, origem_cone_c = 3;  // cone com ponta na linha 0 (para "descer")
    int origem_cruz_l = 5, origem_cruz_c = 4;  // cruz centralizada em (5,4)
    int origem_octa_l = 7, origem_octa_c = 7;  // octaedro centrado em (7,7)

    // Função auxiliar para aplicar uma matriz de habilidade ao tabuleiro
    // top-left do bloco = (orig_l - center, orig_c - center)
    int start_r, start_c;
    // Aplicar CONE
    start_r = origem_cone_l - center;
    start_c = origem_cone_c - center;
    for (i = 0; i < SK_C; i++) {
        for (j = 0; j < SK_C; j++) {
            if (cone[i][j] == 1) {
                int tr = start_r + i;
                int tc = start_c + j;
                if (DENTRO_TAB(tr, tc)) {
                    if (tab[tr][tc] == 3) tab[tr][tc] = 8; // navio + efeito
                    else tab[tr][tc] = 5; // efeito somente
                }
            }
        }
    }

    // Aplicar CRUZ
    start_r = origem_cruz_l - center;
    start_c = origem_cruz_c - center;
    for (i = 0; i < SK_C; i++) {
        for (j = 0; j < SK_C; j++) {
            if (cruz[i][j] == 1) {
                int tr = start_r + i;
                int tc = start_c + j;
                if (DENTRO_TAB(tr, tc)) {
                    if (tab[tr][tc] == 3) tab[tr][tc] = 8;
                    else tab[tr][tc] = 5;
                }
            }
        }
    }

    // Aplicar OCTAEDRO (diamond)
    start_r = origem_octa_l - center;
    start_c = origem_octa_c - center;
    for (i = 0; i < SK_C; i++) {
        for (j = 0; j < SK_C; j++) {
            if (octa[i][j] == 1) {
                int tr = start_r + i;
                int tc = start_c + j;
                if (DENTRO_TAB(tr, tc)) {
                    if (tab[tr][tc] == 3) tab[tr][tc] = 8;
                    else tab[tr][tc] = 5;
                }
            }
        }
    }

    // ---------------------------
    // 5) Exibir tabuleiro com legenda clara
    //    Mapear números para símbolos:
    //     0 -> '0' (água)
    //     3 -> '3' (navio)
    //     5 -> '5' (área de habilidade)
    //     8 -> 'X' (navio + área)
    // ---------------------------

    printf("\n===== TABULEIRO FINAL (Navios + Áreas de Habilidade) =====\n\n");

    // Cabeçalho de colunas
    printf("   ");
    for (j = 0; j < TAM; j++) printf("%2d", j);
    printf("\n");

    printf("   ");
    for (j = 0; j < TAM; j++) printf("--");
    printf("\n");

    for (i = 0; i < TAM; i++) {
        printf("%2d|", i);
        for (j = 0; j < TAM; j++) {
            char c;
            if (tab[i][j] == 0) c = '0';
            else if (tab[i][j] == 3) c = '3';
            else if (tab[i][j] == 5) c = '5';
            else if (tab[i][j] == 8) c = 'X';
            else c = '?'; // caso inesperado
            printf(" %c", c);
        }
        printf("\n");
    }

    printf("\nLegenda:\n");
    printf(" . => Água (0)\n");
    printf(" N => Navio (3)\n");
    printf(" * => Área de habilidade (5)\n");
    printf(" X => Navio dentro da área de habilidade (8)\n");

    // ---------------------------
    // (Opcional) — imprimir as matrizes de habilidade (para debug/visualização)
    // ---------------------------
    printf("\nMatriz CONE (1 = afetado, 0 = não):\n");
    for (i = 0; i < SK_C; i++) {
        for (j = 0; j < SK_C; j++) printf("%d ", cone[i][j]);
        printf("\n");
    }

    printf("\nMatriz CRUZ (1 = afetado, 0 = não):\n");
    for (i = 0; i < SK_C; i++) {
        for (j = 0; j < SK_C; j++) printf("%d ", cruz[i][j]);
        printf("\n");
    }

    printf("\nMatriz OCTAEDRO (1 = afetado, 0 = não):\n");
    for (i = 0; i < SK_C; i++) {
        for (j = 0; j < SK_C; j++) printf("%d ", octa[i][j]);
        printf("\n");
    }

    return 0;
}
