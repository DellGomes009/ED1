typedef struct {
    int vetor[1000]; // Como estava o vetor nesta etapa
    int pivo_idx;    // Quem era o pivô (para pintar de amarelo)
    int troca_i;     // Elemento 1 a ser trocado (para pintar de vermelho)
    int troca_j;     // Elemento 2 a ser trocado (para pintar de vermelho)
} PassoAnimacao;