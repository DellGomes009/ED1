//Tipo de expotado
typedef struct ponto Ponto;

//funções exportadas
Ponto* pto_criar(float x, float y);
void pto_liberar(Ponto* p);
void pto_acessar(Ponto* p, float* x, float* y);
void pto_atribuir(Ponto* p, float x, float y);
float pto_distancia(Ponto* p1, Ponto* p2);
    