/*
Turma Análise e Desenvolvimento de Sistemas 0117
Alunos:
-> Edivan Dyeimes Figueira de Souza


*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MIN 0
#define MAX 1000000000
#define QTDE 50000

//Estrutura da Lista dupla e da ArvoreBB
typedef struct TipoCelula
{

    int Item;
    TipoCelula *Esq, *Dir;
};

//Estrutura da Lista Simples
typedef struct _TipoCelula
{

    int num;
    _TipoCelula *prox;
};


TipoCelula *Raiz, *Frente, *Traz;
_TipoCelula *ListaF, *ListaT;




//contador de inserção
int Quantos = 0, Quantos_ls=0, Quantos_ld=0, nordem=0;

//vetor de 50 mil numeros para serem inseridos e pesquisados
int op[QTDE];

//Busca lista dupla
bool Lista_Procura(int elemento)
{


    TipoCelula *Temp = Frente;

    while(Temp != Traz && Temp->Item != elemento)
    {

        Temp = Temp->Dir;
    }

    if(Temp != Traz)
        return true;
    else
        return false;


}

//Busca lista simples
bool Lista_Psim(int elemento)
{


    _TipoCelula *Temp = ListaF;

    while(Temp != NULL  && Temp->num != elemento)
    {

        Temp = Temp->prox;
    }

    if(Temp != NULL)
        return true;
    else
        return false;


}
//Busca ArvoreBB
bool ArvoreBinariaBusca_Pesquisar(int Elemento, TipoCelula *Raiz)
{

    if(Raiz == NULL)return false;
    else
    {
        if(Elemento < Raiz->Item)
            return ArvoreBinariaBusca_Pesquisar(Elemento, Raiz->Esq);
        else
        {
            if(Elemento > Raiz->Item)
                return ArvoreBinariaBusca_Pesquisar(Elemento, Raiz->Dir);
            else return true;
        }
    }
}

//Insere na Lista Dupla
void Lista_Dupla(int Elemento)
{

    TipoCelula *Novo;

    if((Novo = (TipoCelula *) malloc(sizeof(TipoCelula)))==NULL)
    {


        printf("Error");
        system("pause");
    }
    else
    {
        Traz->Item = Elemento;


        Traz->Dir = Novo;

        Novo->Esq = Traz;


        Novo->Dir = NULL;

        Traz = Novo;

        Quantos_ld++;


    }
}

//Insere na lista simples
void Lista_Simples(int elemento, _TipoCelula *&Lista)
{
    _TipoCelula *novo;

    if((novo=(_TipoCelula *) malloc(sizeof(_TipoCelula))) != NULL)
    {



        ListaT->num = elemento;

        novo->prox = NULL;

        ListaT->prox = novo;

        ListaT = novo;

        Quantos_ls++;

    }
}

//Ordena numeros usando a ArvoreBB
int numeros_odernados(TipoCelula *Raiz)
{

    if(Raiz!=NULL)
    {
        numeros_odernados(Raiz->Esq);
        op[nordem] = Raiz->Item;
        nordem++;
        numeros_odernados(Raiz->Dir);
    }
}

//Gera numeros aleatorios entre 0 e 1 bilao
int randomNumber( int a, int maximo)
{


    return (int)((double)(MAX)/RAND_MAX*rand()/(maximo)*a);

}

//Insere na ArvoreBB
int ArvoreBB_const_ins(int Elemento, TipoCelula *&Raiz)
{

    if(Raiz == NULL)
    {
        if((Raiz = new(TipoCelula)) == NULL)
            return 5;
        else
        {
            Raiz->Item = Elemento;
            Raiz->Esq = Raiz->Dir = NULL;
            Quantos++;
            return 1;

        }
    }
    else
    {
        if(Elemento < Raiz->Item)
            ArvoreBB_const_ins(Elemento, Raiz->Esq);
        else
        {
            if(Elemento > Raiz->Item)
                ArvoreBB_const_ins(Elemento, Raiz->Dir);
            else return 0;  //Elemento já existe na Árvore
        }
    }
}


int main()
{
    Raiz = NULL; //inicia arvore

    //Inicia Lista Simples
    ListaT = (_TipoCelula *)malloc(sizeof(_TipoCelula));
    ListaF = ListaT;
    ListaF->prox = NULL;



    int x;
    int i, j;
    extern int op[QTDE];
    float tFim, tIn, total_a=0, total_ld=0, total_ls=0;

    srand(time(NULL));

    printf("EXERCICIO ESTRUTURA DE DADOS (TP08)\n\n");
    printf("Alunos: Edivan Dyeimes Figueira de Souza e Nathan Gomes Ferreira\n");
    printf("Professor: Thiago Bicalho\nTurma: ADS0117\n\n\n");

    //Gera numeros randomicos entre 0 e 1 bilhao
    j=0;
    for(i=0; (j!=QTDE); i++)
    {

        if(rand()%2000 ==0)
        {

            op[j]=i;



            j++;
        }
        if(i==MAX)i=0;

    }

    float ci, cf, cin_ls, cin_ld, cfim_ls, cfim_ld;

    //Insere na arvore e na lista simples os numeros randomicos
    for(i=0; i<QTDE; i++)
    {
        //Usa os numeros aleatorios do vetor op para gerar numeros entre 0 e 1 bilhao.
        op[i]=randomNumber(op[i], op[QTDE-1]);


        //inserir na arvoreBB
        ci=clock();
        x= ArvoreBB_const_ins(op[i], Raiz);
        cf=clock();
        while(x==0)
        {
            //quando um numero é repetido ele usa esse numero como chave para gerar outro numero.
            if(op[i]==0) op[i]++;//se 0 for o numero repetido troca para 1, pois chave 0 gera sempre 0 criando um loop
            op[i]=randomNumber(op[i], op[QTDE-1]);
            ci=clock();
            x= ArvoreBB_const_ins(op[i], Raiz);
            cf=clock();



        }
        total_a=total_a+(cf-ci);


        //insere na Lista Simples
        cin_ls=clock();
        Lista_Simples(op[i], ListaF);
        cfim_ls=clock();
        total_ls=total_ls+(cfim_ls-cin_ls);

    }


    Traz = (TipoCelula *)malloc(sizeof(TipoCelula));
    Frente = Traz;
    Frente->Dir = Frente->Esq = NULL;

    numeros_odernados(Raiz);   //Pega os numeros ordenados pela arvore para ser inseridos na lista

    //insere na lista duplamente encadeada
    for(i=0; i<QTDE; i++)
    {

        cin_ld=clock();
        Lista_Dupla(op[i]);
        cfim_ld=clock();
        total_ld=total_ld + (cfim_ld - cin_ld);


    }



    printf("TEMPO GASTO PARA INSERIR:\n\n");
    printf("Arvore: %.0lf ms \t        Quantidade: %d\nLista Simples: %.0lf ms\tQuantidade: %d\nLista Dupla: %.0lf ms\tQuantidade: %d\n\n\n\n",total_a, Quantos, total_ls, Quantos_ls, total_ld, Quantos_ld );


    //Gera numeros aleatorios para busca
    for(i=0; (j!=QTDE); i++)
    {

        if(rand()%2000 ==0)
        {

            op[j]=i;

            j++;
        }
        if(i==MAX)i=0;

    }
    for(i=0; i<QTDE; i++)
    {

        //Gera numeros aleatorios
        op[i]=randomNumber(op[i], op[QTDE-1]);

        //Busca na ArvoreBB
        ci=clock();
        ArvoreBinariaBusca_Pesquisar(op[i], Raiz);
        cf=clock();
        total_a=total_a+(cf-ci);

        //Busca na Lista Simples
        cin_ls=clock();
        Lista_Psim(op[i]);
        cfim_ls=clock();
        total_ls=total_ls+(cfim_ls-cin_ls);

        //Busca na Lista Dupla
        cin_ld=clock();
        Lista_Procura(op[i]);
        cfim_ld=clock();
        total_ld=total_ld+(cfim_ld-cin_ld);




    }

    printf("TEMPO GASTO PARA BUSCAR:\n\n");
    printf("Arvore: %.0f ms\nLista Simples: %.0f ms\nLista Dupla: %.0f ms\n", total_a, total_ls, total_ld);




    return 0;
}
