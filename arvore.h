/*
    * Aluno: Pedro Henrique Oliveira Veloso
    * Matricula: 0002346
*/

#ifndef __ARVORE_BINARIA__
#define __ARVORE_BINARIA__

// Tipos:
typedef struct arvore *Arvore;
typedef struct pilha *Pilha;


// Sub-rotinas da Arvore:
Arvore  abbCriaVazia(void);
Arvore  abbCria(int valor, Arvore pai, Arvore esq, Arvore dir);
Arvore  abbLiberaArvore(Arvore A);
Arvore  abbBusca(Arvore A, int valor);
Arvore  abbInsere(Arvore A, int valor);
Arvore  abbRemove(Arvore A, int valor);
void    abbImprimeArvore(Arvore A);
int     abbVazia(Arvore A);
int     abbPertence(Arvore A, int valor);
int     abbPegaValor(Arvore A);


// Sub-rotinas da Pilha:
Pilha   piCria(void);
Arvore  piDesempilha(Pilha p);
int     piVazia(Pilha p);
void    piEmpilha(Pilha p, Arvore A);
void    piLiberaPilha(Pilha p);


#endif
