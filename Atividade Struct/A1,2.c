#include <stdio.h>
#define MAX 3

typedef struct pessoa{
    char nome [50];
    char cpf[20];
    char rg[20];
    char telefone[20];
    int idade;

} 
pessoa;
void recebe (pessoa*a){

    printf ("Digite seu nome: ");
    scanf(" %[^\n]", a->nome);

    printf ("idade: ");
    scanf ("%d", &a->idade);

    printf ("cpf: ");
    scanf ("%s", a->cpf);

    printf ("rg: ");
    scanf ("%s", a->rg);

    printf ("telefone: ");
    scanf (" %[^\n]", a->telefone);
}
void imprime (pessoa a){

    printf("\n Nome: %s | idade: %d\n | cpf: %s\n | rg: %s\n | telefone: %s \n", a.nome, a.idade, a.cpf, a.rg, a.telefone);
}

//Vetores strucks
int main (void){
    pessoa p[MAX];
    int contador;

    for(contador=0; contador<MAX; contador++){
        printf("\n--- Pessoa %d ---\n", contador + 1);
        recebe(&p[contador]);
    }
printf("\n===== DADOS CADASTRADOS =====\n");

    for (contador = 0; contador < MAX; contador++) {

        imprime(p[contador]);
    }
    
   
    return 0;
}