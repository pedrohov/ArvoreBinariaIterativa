/*
    * Aluno: Pedro Henrique Oliveira Veloso
    * Matricula: 0002346
*/

#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"


// Estruturas:
// Arvore de busca binaria:
struct arvore {
    int valor;
    struct arvore *pai;
    struct arvore *esquerda;
    struct arvore *direita;
};

// Pilha:
struct nodo {
    struct arvore *info;
    struct nodo *proximo;
};

struct pilha {
    struct nodo *topo;
    int tamanho;
};


// Sub-rotinas da Arvore:
Arvore abbCriaVazia(void)
{
    return NULL;
}

Arvore abbCria(int valor, Arvore pai, Arvore esq, Arvore dir)
{
    Arvore nova = (Arvore)malloc(sizeof(struct arvore));
    nova -> valor = valor;
    nova -> pai = pai;
    nova -> esquerda = esq;
    nova -> direita = dir;
    return nova;
}

Arvore abbLiberaArvore(Arvore A)
{
    if(abbVazia(A))
        return NULL;

    while(A != NULL)
    {
        Arvore aux = A;

        // Caso reste apenas a raiz:
        if((A -> esquerda == NULL) && (A -> direita == NULL))
        {
            free(A);
            return NULL;
        }

        // Procure por uma folha sem filhos:
        while((aux -> esquerda != NULL) || (aux -> direita != NULL))
        {
            // Caminha para a esquerda ate o fim:
            while(aux -> esquerda != NULL)
                aux = aux -> esquerda;

            // Caminha para a direita ate o fim:
            while(aux -> direita != NULL)
                aux = aux -> direita;
        }

        // Altera os valores de 'esquerda' e 'direita' de pai:
        if(aux -> pai -> esquerda == aux)
            aux -> pai -> esquerda = NULL;
        if(aux -> pai -> direita == aux)
            aux -> pai -> direita = NULL;

        // Libera a folha, nao possui filhos:
        free(aux);
    }

    return A;
}

Arvore abbBusca(Arvore A, int valor)
{
    if(abbVazia(A))
        return NULL;

    // Percorre a arvore ate encontrar o valor,
    // Ou ate chegar a uma folha sem filhos:
    Arvore aux = A;
    while(aux -> valor != valor)
    {
        // Compara valores:
        if(aux -> valor < valor)
            aux = aux -> direita;
        else if(aux -> valor > valor)
            aux = aux -> esquerda;

        // Nao encontrou o valor:
        if(aux == NULL)
            return NULL;
    }

    return aux;
}

Arvore abbInsere(Arvore A, int valor)
{
    // Se A for uma arvore vazia:
    if(abbVazia(A))
        A = abbCria(valor, abbCriaVazia(), abbCriaVazia(), abbCriaVazia());
    else
    {
        Arvore aux = A;
        while(aux != NULL)
        {
            if(valor < aux -> valor)
            {
                // Vai para esquerda:
                if(aux -> esquerda != NULL)
                    aux = aux -> esquerda;
                else {
                    aux -> esquerda = abbCria(valor, aux, abbCriaVazia(), abbCriaVazia());
                    return aux -> esquerda;
                }
            }
            else if(valor > aux -> valor)
            {
                // Vai para direita:
                if(aux -> direita != NULL)
                    aux = aux -> direita;
                else {
                    aux -> direita = abbCria(valor, aux, abbCriaVazia(), abbCriaVazia());
                    return aux -> direita;
                }
            }
        }
    }
    return A;
}

Arvore abbRemove(Arvore A, int valor)
{
    if(abbVazia(A))
        return NULL;

    // Procurar pelo nodo a ser retirado:
    Arvore aux = A;
    while(aux -> valor != valor)
    {
        // Retirar da esquerda:
        if(A -> valor > valor)
            aux = aux -> esquerda;
        // Retirar da direita:
        else if(A -> valor < valor)
            aux = aux -> direita;
    }

    // Remover nodo:
    // Caso o nodo nao possua folhas:
    if((aux -> esquerda == NULL) && (aux -> direita == NULL))
    {
        // Atualiza ponteiros de "pai", se o nodo possuir um pai:
        if(aux -> pai != NULL)
        {
            if(aux -> pai -> esquerda == aux)
                aux -> pai -> esquerda = NULL;
            if(aux -> pai -> direita == aux)
                aux -> pai -> direita = NULL;
        }

        free(aux);
    }
    // Caso o nodo possua um unico filho
    // Na esquerda:
    else if(aux -> direita == NULL)
    {
        // Atualiza o pai do ramo:
        aux -> esquerda -> pai = aux -> pai;

        // Atualiza os ponteiros de "pai" do nodo a ser removido:
        if(aux -> pai != NULL)
        {
            if(aux -> pai -> esquerda == aux)
                aux -> pai -> esquerda = aux -> esquerda;
            if(aux -> pai -> direita == aux)
                aux -> pai -> direita = aux -> esquerda;
        }
        free(aux);
    }
    // Na direita:
    else if(aux -> esquerda == NULL)
    {
        aux -> direita -> pai = aux -> pai;
        if(aux -> pai != NULL)
        {
            if(aux -> pai -> esquerda == aux)
                aux -> pai -> esquerda = aux -> direita;
            if(aux -> pai -> direita == aux)
                aux -> pai -> direita = aux -> direita;
        }
        free(aux);
    }
    // Nodo possui dois filhos:
    else
    {
        // Encontrar o no que precede a raiz na ordenacao:
        Arvore precede = aux -> esquerda;
        while(precede -> direita != NULL)
            precede = precede -> direita;

        // Trocar os valores:
        // O valor de aux eh perdido porque sera removido:
        aux -> valor = precede -> valor;

        // Remove o nodo 'precede':
        // Atualiza o pai do ramo:
        precede -> esquerda -> pai = precede -> pai;

        // Atualiza os ponteiros de "pai" do nodo a ser removido:
        if(precede -> pai != NULL)
        {
            if(precede -> pai -> esquerda == precede)
                precede -> pai -> esquerda = precede -> esquerda;
            if(precede -> pai -> direita == precede)
                precede -> pai -> direita = precede -> esquerda;
        }
        free(precede);
    }

    return A;
}

void abbImprimeArvore(Arvore A)
{
    if(abbVazia(A))
        return;

    // Cria a pilha:
    Pilha p = piCria();

    // Empilha a raiz:
    piEmpilha(p, A);
    Arvore aux = A -> esquerda;

    // Enquanto a pilha nao estiver vazia:
    while(!piVazia(p))
    {
        // Percorra ate o final pela esquerda:
        while(aux != NULL)
        {
            // Empilha todos os nos no processo:
            piEmpilha(p, aux);
            aux = aux -> esquerda;
        }

        // Desempilha e imprime o no:
        Arvore saida = piDesempilha(p);
        printf("%d\t", saida -> valor);

        // Avanca um para a direita:
        aux = saida -> direita;
        if(aux != NULL)
        {
            piEmpilha(p, aux);
            // Como o nodo atual ja foi empilhado,
            // Prossiga para o proximo.
            // (Evita duplicar)
            aux = aux -> esquerda;
        }
    }

    // Libera memoria usada pela pilha:
    piLiberaPilha(p);
    return;
}

int abbVazia(Arvore A)
{
    if(A == NULL)
        return 1;
    return 0;
}

int abbPertence(Arvore A, int valor)
{
    if(abbVazia(A))
        return 0;

    // Percorre a arvore:
    Arvore aux = A;
    while(aux != NULL)
    {
        // Valor encontrado:
        if(aux -> valor == valor)
            return 1;
        // Continua a busca:
        else if(aux -> valor < valor)
            aux = aux -> direita;
        else
            aux = aux -> esquerda;
    }

    return 0;
}

int abbPegaValor(Arvore A)
{
    if(abbVazia(A))
        return 0;
    return A -> valor;
}


// Sub-rotinas da Pilha:
Pilha piCria(void)
{
    Pilha nova = (Pilha)malloc(sizeof(struct pilha));
    nova -> topo = NULL;
    nova -> tamanho = 0;
    return nova;
}

Arvore piDesempilha(Pilha p)
{
    if(piVazia(p))
        return NULL;

    // Armazena o endereco da arvore no topo:
    Arvore topo = p -> topo -> info;

    // Ponteiro para o local a ser desempilhado:
    struct nodo *aux = p -> topo;

    // Informa o novo topo:
    p -> topo = p -> topo -> proximo;
    p -> tamanho--;

    // Libera o topo antigo:
    free(aux);

    // Retorna a arvore que estava no topo:
    return topo;

}

int piVazia(Pilha p)
{
    if(p -> topo == NULL)
        return 1;
    return 0;
}

void piEmpilha(Pilha p, Arvore A)
{
    // Aloca memoria para um novo nodo:
    struct nodo *novo = (struct nodo*)malloc(sizeof(struct nodo));

    // Atualiza as informacoes do novo topo:
    novo -> proximo = p -> topo;    // O topo atual sera o proximo.
    novo -> info = A;

    // O novo nodo sera o novo topo:
    p -> topo = novo;
    p -> tamanho++;
    return;
}

void piLiberaPilha(Pilha p)
{
    while(!piVazia(p))
        piDesempilha(p);

    free(p);
    return;
}
