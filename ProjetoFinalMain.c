#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>
#define true 1
#define false 0
#define ERRO -1
//#include "ListaLigada.h"
//#include "Cartao.h"
//#include "Conta.h"

typedef int bool;

typedef struct
{
    float numCartao, codSeg, mesVal, anoVal, limite, saldo;
    char categoria;
} CARTAO;
typedef CARTAO *PONTCARTAO;
CARTAO criarCartao(char categ, float nC, float cS, float mV, float aV, float Lim, float Sal)
{
    CARTAO c;
    c.categoria = categ;
    c.anoVal = aV;
    c.codSeg = cS;
    c.limite = Lim;
    c.mesVal = mV;
    c.numCartao = nC;
    c.saldo = Sal;
    return c;
}

bool debitarCartaoDebito(PONTCARTAO cartao, float valor)
{
    if (cartao->saldo >= valor)
    {
        cartao->saldo -= valor;
        return true;
    }
    else
    {
        return false;
    }
}

bool debitarCartaoCredito(PONTCARTAO cartao, float valor)
{
    if (cartao->limite >= valor)
    {
        cartao->limite -= valor;
        return true;
    }
    else
    {
        return false;
    }
}
void exibeDebitarCredito(PONTCARTAO cartao, float valor)
{
    if (debitarCartaoCredito(cartao, valor) == true)
    {
        printf("\nCompra no valor de R$: %.2f realizada com sucesso\n", valor);
    }
    else
    {
        printf("\nLimite insuficiente para compra\n");
    }
}

void exibeDebitarDebito(PONTCARTAO cartao, float valor)
{
    if (debitarCartaoDebito(cartao, valor) == true)
    {
        printf("\nCompra no valor de R$: %.2f realizada com sucesso\n", valor);
    }
    else
    {
        printf("\nSaldo insuficiente para compra\n");
    }
}
bool depositarCartaoDebito(PONTCARTAO cartao, float valor)
{
    cartao->saldo += valor;
}
bool depositarCartaoCredito(PONTCARTAO cartao, float valor)
{
    cartao->limite += valor;
}

bool checarCartao(PONTCARTAO cartao, float numCartao, float mesV, float anoV, float cS, char categ)
{
    if (cartao->anoVal == anoV && cartao->categoria == categ && cartao->codSeg == cS && cartao->mesVal == mesV)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int exibeChecarCartao(PONTCARTAO cartao, float numCartao, float mesV, float anoV, float cS, char categ)
{
    if (checarCartao(cartao, numCartao, mesV, anoV, cS, categ) == true)
    {
        printf("\nDados inseridos corretamente, prossiga\n");
        return 1;
    }
    else
    {
        printf("\nDados incompativeis, tente novamente\n");
        return 0;
    }
}
void exibeCartao(PONTCARTAO cartao)

{
    char categoria, um = '1';

    if (cartao->categoria == um)
        categoria = '1';
    else
        categoria = '2';
    printf("\nDados do cartao:\nNumero: %.0f\nTipo: %c\nMes de vencimento: %.0f\nAno de vencimento: %.0f\nSaldo: R$%.2f\nLimite disponivel: %.2f\n\n", cartao->numCartao, (char)categoria, cartao->mesVal, cartao->anoVal, cartao->saldo, cartao->limite);
}
bool transacaoCartao(PONTCARTAO origem, PONTCARTAO destino, float valor)
{
    bool teste;
    if (origem->categoria == '1')
    {
        teste = debitarCartaoDebito(origem, valor);
    }
    else
    {
        teste = debitarCartaoCredito(origem, valor);
    }
    if (teste == false)
    {
        return false;
    }
    if (destino->categoria == '1')
    {
        depositarCartaoDebito(destino, valor);
    }
    else
    {
        depositarCartaoCredito(destino, valor);
    }
    return true;
}

typedef char *String;
typedef struct
{
    String login;
    String senha;
    char categoria; //1= consumidor, 2 = vendedor, 3 = gerente
    String nome;
} CONTA;

typedef CONTA *PONTCONTA;

CONTA criarConta(String login, String senha, String nome, char categoria)
{ //inserir a categoria entre aspas simples na main
    CONTA conta;
    conta.login = login;
    conta.senha = senha;
    conta.nome = nome;
    conta.categoria = categoria;
    return conta;
}

void exibirConta(PONTCONTA c)
{
    int i;
    printf("\nDados da conta\n");
    printf("\nNOME:\t");
    for (i = 0; i < strlen(c->nome); i++)
    {
        printf("%c", c->nome[i]);
    }
    printf("\n");
    printf("LOGIN:\t");
    for (i = 0; i < strlen(c->login); i++)
    {
        printf("%c", c->login[i]);
    }
    printf("\nSENHA:\t");
    for (i = 0; i < strlen(c->senha); i++)
    {
        printf("%c", c->senha[i]);
    }
    printf("\nTIPO DE CONTA:\t");
    if (c->categoria == '1')
    {
        printf("Cliente\n");
    }
    else if (c->categoria == '2')
    {
        printf("Vendedor\n");
    }
    else if (c->categoria == '3')
    {
        printf("Gerente\n");
    }
}

bool checarConta(PONTCONTA conta, String login, String senha)
{
    if (strcmp(conta->login, login) == 0 && strcmp(conta->senha, senha) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int exibirChecarConta(PONTCONTA conta, String login, String senha)
{
    if (checarConta(conta, login, senha) == true)
    {
        printf("\nLogin realizado com sucesso\n");
        return 1;
    }
    else
    {
        printf("\nLogin ou senha incorretos, tente novamente\n");
        return 0;
    }
}

typedef char *TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave; //Codigo de barras.
    TIPOCHAVE nome;  //Nome do produto
    TIPOCHAVE tipo;  //"Categoria" do produto( 1= vendido por peso, 2 = vendido por unidades)
    char categoria;
    float estoque, precoQuilo, precoUnidade, precoAtacado;
} REGISTRO;

typedef struct aux
{
    REGISTRO reg;
    struct aux *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct
{
    PONT inicio;
} LISTA;

void inicializarLista(LISTA *l)
{
    l->inicio = NULL;
}

void exibirLista(LISTA *l)
{
    char quilo = "1";
    PONT end = l->inicio;
    printf("\n");
    int i;
    printf("\nExibicao dos produtos no seguinte formato:\nNome\nTipo\nCodigo de barras\nPreco quilo/Unidade e Atacado\n\n");
    while (end != NULL)
    {

        for (i = 0; i < strlen(end->reg.nome); i++)
        {
            printf("%c", end->reg.nome[i]);
        }
        printf("\n");
        for (i = 0; i < strlen(end->reg.tipo); i++)
        {
            printf("%c", end->reg.tipo[i]);
        }
        printf("\n");

        for (i = 0; i < strlen(end->reg.chave); i++)
        {
            printf("%c", end->reg.chave[i]);
        }
        printf("\n");
        if (end->reg.categoria == quilo)
        {
            printf("R$ %.2f", end->reg.precoQuilo);
        }
        else
        {
            printf("R$ %.2f\n", end->reg.precoUnidade);
            printf("R$ %.2f", end->reg.precoAtacado);
        }
        printf("\n\n");
        end = end->prox;
    }
    printf("\n");
}

int tamanho(LISTA *l)
{
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL)
    {
        tam++;
        end = end->prox;
    }
    return tam;
}

PONT buscaAux(LISTA *l, TIPOCHAVE ch, PONT *ant)
{
    *ant = NULL;
    PONT atual = l->inicio;
    while (atual != NULL && atual->reg.chave < ch)
    {
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (atual->reg.chave == ch))
        return atual;
    return NULL;
}

void buscaAuxiliar(LISTA *l, PONT *aux)
{
    *aux = NULL;
    int t = tamanho(l);
    int i = 0;
    PONT atual = l->inicio;
    while (i < t)
    {
        *aux = atual;
        atual = atual->prox;
        i++;
    }
}
PONT buscarElemento(TIPOCHAVE ch, LISTA *l, PONT *aux)
{
    PONT end = l->inicio;
    while (end != NULL)
    {
        if (strcmp(end->reg.chave, ch) == 0)
        {
            return end;
        }
        else
        {
            *aux = end;
            end = end->prox;
        }
    }
    return end;
}
bool inserirElemNaoOrd(LISTA *l, TIPOCHAVE ch, TIPOCHAVE nom, TIPOCHAVE tip, char categ, float precoQ, float precoUn, float precoAta, float estoq)
{
    PONT ant, i, j;
    buscaAuxiliar(l, &ant);
    PONT t = buscarElemento(ch, l, &j);
    if (t != NULL)
    {
        return false;
    }
    i = (PONT)malloc(sizeof(ELEMENTO));
    i->reg.chave = ch;
    i->reg.categoria = categ;
    i->reg.nome = nom;
    i->reg.estoque = estoq;
    i->reg.precoAtacado = precoAta;
    i->reg.precoQuilo = precoQ;
    i->reg.precoUnidade = precoUn;
    i->reg.tipo = tip;
    if (ant == NULL)
    {
        i->prox = l->inicio;
        l->inicio = i;
    }
    else
    {
        i->prox = ant->prox;
        ant->prox = i;
    }
    return true;
}
bool inserirProduto(LISTA *l, PONT produto)
{
    PONT ant, i, j;
    buscaAuxiliar(l, &ant);
    printf("5");
    PONT t = buscarElemento(produto->reg.chave, l, &j);
    if (t != NULL)
    {
        return false;
    }
    printf("6");
    i = (PONT)malloc(sizeof(ELEMENTO));
    i->reg.chave = produto->reg.chave;
    i->reg.categoria = produto->reg.categoria;
    i->reg.nome = produto->reg.nome;
    i->reg.estoque = produto->reg.estoque;
    i->reg.precoAtacado = produto->reg.precoAtacado;
    i->reg.precoQuilo = produto->reg.precoQuilo;
    i->reg.precoUnidade = produto->reg.precoUnidade;
    i->reg.tipo = produto->reg.tipo;
    printf("7");
    if (ant == NULL)
    {
        i->prox = l->inicio;
        l->inicio = i;
        printf("8");
    }

    else
    {
        i->prox = ant->prox;
        ant->prox = i;
    }
}
bool inserirProdutoCarrinho(LISTA *l, PONT produto, float qtd)
{
    PONT ant, i, j;
    buscaAuxiliar(l, &ant);
    PONT t = buscarElemento(produto->reg.chave, l, &j);
    if (t != NULL)
    {
        return false;
    }
    i = (PONT)malloc(sizeof(ELEMENTO));
    i->reg.chave = produto->reg.chave;
    i->reg.categoria = produto->reg.categoria;
    i->reg.nome = produto->reg.nome;
    i->reg.estoque = qtd;
    i->reg.precoAtacado = produto->reg.precoAtacado;
    i->reg.precoQuilo = produto->reg.precoQuilo;
    i->reg.precoUnidade = produto->reg.precoUnidade;
    i->reg.tipo = produto->reg.tipo;
    if (ant == NULL)
    {
        i->prox = l->inicio;
        l->inicio = i;
    }
    else
    {
        i->prox = ant->prox;
        ant->prox = i;
    }
}
void reinicializarLista(LISTA *l)
{
    PONT end = l->inicio;
    while (end != NULL)
    {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->inicio = NULL;
}

bool excluirElemento(TIPOCHAVE ch, LISTA *l)
{

    PONT aux, i;
    i = buscarElemento(ch, l, &aux);
    if (i == NULL)
    {
        return false;
    }
    if (aux == NULL)
    {
        l->inicio = i->prox;
    }
    else
    {
        aux->prox = i->prox;
    }
    free(i);
    return true;
}

PONT buscarElementoNome(TIPOCHAVE nome, LISTA *l)
{
    PONT end = l->inicio;
    while (end != NULL)
    {
        if (strcmp(end->reg.nome, nome) == 0)
        {
            break;
        }
        else
        {
            end = end->prox;
        }
    }
    return end;
}

void exibirBuscaNome(LISTA *l, TIPOCHAVE nome)
{
    PONT end = buscarElementoNome(nome, l);
    char quilo = "1";
    int i;
    if (end == NULL)
    {
        printf("\nProduto nao encontrado\n");
    }
    else
    {
        printf("\nProduto buscado:\n");
        for (i = 0; i < strlen(end->reg.nome); i++)
        {
            printf("%c", end->reg.nome[i]);
        }
        printf("\n");
        for (i = 0; i < strlen(end->reg.tipo); i++)
        {
            printf("%c", end->reg.tipo[i]);
        }
        printf("\n");

        for (i = 0; i < strlen(end->reg.chave); i++)
        {
            printf("%c", end->reg.chave[i]);
        }
        printf("\n");
        if (end->reg.categoria == quilo)
        {
            printf("R$ %.2f", end->reg.precoQuilo);
        }
        else
        {
            printf("R$ %.2f\n", end->reg.precoUnidade);
            printf("R$ %.2f", end->reg.precoAtacado);
        }
        printf("\n\n");
    }
}

void buscarElementoTipo(LISTA *lista, TIPOCHAVE tipo)
{
    PONT end = lista->inicio;
    char quilo = "1";
    int i;
    printf("\nProdutos do tipo referido:\n");
    while (end != NULL)
    {
        if (strcmp(end->reg.tipo, tipo) == 0)
        {
            for (i = 0; i < strlen(end->reg.nome); i++)
            {
                printf("%c", end->reg.nome[i]);
            }
            printf("\n");
            for (i = 0; i < strlen(end->reg.tipo); i++)
            {
                printf("%c", end->reg.tipo[i]);
            }
            printf("\n");

            for (i = 0; i < strlen(end->reg.chave); i++)
            {
                printf("%c", end->reg.chave[i]);
            }
            printf("\n");
            if (end->reg.categoria == quilo)
            {
                printf("R$ %.2f", end->reg.precoQuilo);
            }
            else
            {
                printf("R$ %.2f\n", end->reg.precoUnidade);
                printf("R$ %.2f", end->reg.precoAtacado);
            }
            printf("\n\n");
        }
        end = end->prox;
    }
}

float comprarProduto(PONT produto, float qtd, LISTA *lista1, LISTA *carrinho)
{
    char um = "1";
    char dois = "2";
    //if (qtd > produto->reg.estoque)
    //{
    //printf("\nA quantidade desejada não está disponìvel, em breve iremos repor nosso estoque\n");
    //  return 0;
    // }
    //inserirProdutoCarrinho(carrinho, produto, qtd);
    produto->reg.estoque -= qtd;
    if (produto->reg.categoria == um)
    {
        return produto->reg.precoQuilo * qtd;
    }
    else if (produto->reg.categoria == dois && qtd >= 50)
    {
        return produto->reg.precoAtacado * qtd;
    }
    else
    {

        return produto->reg.precoUnidade * qtd;
    }
}

void exibirProduto(TIPOCHAVE codigoBarras, LISTA *lista)
{
    char quilo = "1";
    int i;
    PONT aux, end;
    end = buscarElemento(codigoBarras, lista, &aux);
    for (i = 0; i < strlen(end->reg.nome); i++)
    {
        printf("%c", end->reg.nome[i]);
    }
    printf("\n");
    for (i = 0; i < strlen(end->reg.tipo); i++)
    {
        printf("%c", end->reg.tipo[i]);
    }
    printf("\n");

    for (i = 0; i < strlen(end->reg.chave); i++)
    {
        printf("%c", end->reg.chave[i]);
    }
    printf("\n");
    if (end->reg.categoria == quilo)
    {
        printf("R$ %.2f", end->reg.precoQuilo);
    }
    else
    {
        printf("R$ %.2f\n", end->reg.precoUnidade);
        printf("R$ %.2f", end->reg.precoAtacado);
    }
    printf("\nEstoque disponivel:\n");
    if (end->reg.categoria == quilo)
    {
        printf("%.2f Kg\n", end->reg.estoque);
    }
    else
    {
        printf("%.0f Unidades\n", end->reg.estoque);
    }
}

float reabastecerEstoque(PONT produto, float qtd, LISTA *lista1)
{
    char um = "1";
    char dois = "2";
    produto->reg.estoque += qtd;
    if (produto->reg.categoria == um)
    {
        return produto->reg.precoQuilo * qtd;
    }
    else if (produto->reg.categoria == dois && qtd >= 50)
    {
        return produto->reg.precoAtacado * qtd;
    }
    else
    {
        return produto->reg.precoUnidade * qtd;
    }
}

int main()
{

    LISTA catalogo, carrinho;
    float val, nCartao, mesV, anoV, cSeg, quantidade;
    int i, j, k, conta;
    char categ;
    char lixo;
    PONT aux, produto, iterator;
    CARTAO cartaoMercado, cartaoCredito, cartaoDebito;
    CONTA cliente, gerente, vendedor, contaAtual;
    String input1, input2, input3;
    TIPOCHAVE codBarras, nome, tipo;
    bool teste;
    tipo = (char *)malloc(1024 * sizeof(char));
    codBarras = (char *)malloc(1024 * sizeof(char));
    nome = (char *)malloc(1024 * sizeof(char));
    input1 = (char *)malloc(1024 * sizeof(char));
    input2 = (char *)malloc(1024 * sizeof(char));
    input3 = (char *)malloc(1024 * sizeof(char));
    cartaoMercado = criarCartao('1', 123456, 456, 12, 2025, 0, 100000);
    cartaoCredito = criarCartao('2', 135790, 246, 11, 2025, 500, 0);
    cartaoDebito = criarCartao('1', 246824, 135, 10, 2025, 0, 100);
    cliente = criarConta("cliente1", "senhacliente", "Jose da Silva", '1');
    vendedor = criarConta("vendedor1", "senhavendedor", "Cleide dos Santos", '2');
    gerente = criarConta("gerente1", "senhagerente", "Amadeu Cruz", '3');

    inicializarLista(&catalogo);
    inicializarLista(&carrinho);
    //18 produtos por peso
    inserirElemNaoOrd(&catalogo, "123456", "batata", "FLV", "1", 4, 0, 0, 100);
    inserirElemNaoOrd(&catalogo, "123457", "cenoura", "FLV", "1", 6, 0, 0, 100);
    inserirElemNaoOrd(&catalogo, "123458", "cebola", "FLV", "1", 3.5, 0, 0, 100);
    inserirElemNaoOrd(&catalogo, "123459", "banana nanica", "FLV", "1", 1.90, 0, 0, 100);
    inserirElemNaoOrd(&catalogo, "123460", "tomate", "FLV", "1", 35.1, 0, 0, 100);
    inserirElemNaoOrd(&catalogo, "123461", "limao", "FLV", "1", 1.5, 0, 0, 100);
    inserirElemNaoOrd(&catalogo, "123462", "laranja", "FLV", "1", 1.75, 0, 0, 100);
    inserirElemNaoOrd(&catalogo, "123463", "melao", "FLV", "1", 3, 0, 0, 100);
    inserirElemNaoOrd(&catalogo, "123464", "beterraba", "FLV", "1", 6, 0, 0, 100);
    inserirElemNaoOrd(&catalogo, "123465", "melancia", "FLV", "1", 1.4, 0, 0, 100);
    inserirElemNaoOrd(&catalogo, "133456", "coxao duro", "Carne", "1", 30.99, 0, 0, 50);
    inserirElemNaoOrd(&catalogo, "133457", "linguica toscana", "Carne", "1", 16.9, 0, 0, 80);
    inserirElemNaoOrd(&catalogo, "133458", "coxao mole", "Carne", "1", 40.30, 0, 0, 50);
    inserirElemNaoOrd(&catalogo, "133459", "coxa de frango", "Carne", "1", 7.98, 0, 0, 85);
    inserirElemNaoOrd(&catalogo, "133461", "peito de frango", "Carne", "1", 16.98, 0, 0, 85);
    inserirElemNaoOrd(&catalogo, "133460", "lombo de porco", "Carne", "1", 20.99, 0, 0, 80);
    inserirElemNaoOrd(&catalogo, "143456", "mussarela", "Frio", "1", 32.9, 0, 0, 80);
    inserirElemNaoOrd(&catalogo, "143457", "presunto", "Frio", "1", 31.9, 0, 0, 80);
    //8 produtos limpeza
    inserirElemNaoOrd(&catalogo, "153456", "detergente ype 500ml", "Limpeza", "2", 0, 3.7, 3, 100);
    inserirElemNaoOrd(&catalogo, "153457", "detergente limpol 500ml", "Limpeza", "2", 0, 3.5, 2.8, 100);
    inserirElemNaoOrd(&catalogo, "153458", "tira manchas em po Vanish 450g", "Limpeza", "2", 0, 23.9, 22.9, 80);
    inserirElemNaoOrd(&catalogo, "153459", "tira manchas em po Vanish refil 400g", "Limpeza", "2", 0, 13.7, 12.7, 100);
    inserirElemNaoOrd(&catalogo, "153460", "agua sanitaria ype 5l", "Limpeza", "2", 0, 17.6, 17, 100);
    inserirElemNaoOrd(&catalogo, "153461", "limpador multiuso veja 500ml", "Limpeza", "2", 0, 2.8, 2.6, 100);
    inserirElemNaoOrd(&catalogo, "153462", "desengordurante veja 500ml", "Limpeza", "2", 0, 8.9, 8.5, 80);
    inserirElemNaoOrd(&catalogo, "153463", "amaciante concentrado Comfort 1l", "Limpeza", "2", 0, 14.2, 14.08, 100);
    //10 produtos higiene
    inserirElemNaoOrd(&catalogo, "163456", "escova de dente Oral-B", "Higiene", "2", 0, 9, 8.5, 100);
    inserirElemNaoOrd(&catalogo, "163457", "escova de dente eletrica Oral-B", "Higiene", "2", 0, 50, 48, 100);
    inserirElemNaoOrd(&catalogo, "163458", "escova de dente Colgate", "Higiene", "2", 0, 10, 9.5, 100);
    inserirElemNaoOrd(&catalogo, "163459", "fio dental comum Colgate", "Higiene", "2", 0, 7.15, 7, 100);
    inserirElemNaoOrd(&catalogo, "163460", "fio dental extrafino Colgate", "Higiene", "2", 0, 8.15, 8, 100);
    inserirElemNaoOrd(&catalogo, "163461", "sabotene neutro Dove 90g", "Higiene", "2", 0, 2.9, 2.8, 100);
    inserirElemNaoOrd(&catalogo, "163462", "sabotene em barra Granado 90g", "Higiene", "2", 0, 3.1, 3, 100);
    inserirElemNaoOrd(&catalogo, "163463", "desodorante antitranspirante spray Old Spice 150ml", "Higiene", "2", 0, 14, 13.9, 100);
    inserirElemNaoOrd(&catalogo, "163464", "desodorante antitranspirante roll on Rexona 50ml", "Higiene", "2", 0, 9.5, 8.9, 100);
    inserirElemNaoOrd(&catalogo, "163465", "desodorante antitranspirante roll on Natura 70ml", "Higiene", "2", 0, 18.9, 18.5, 100);
    //8 oleos vegetais
    inserirElemNaoOrd(&catalogo, "173456", "oleo de soja Liza 900ml", "Oleo vegetal", "2", 0, 7.6, 7.5, 100);
    inserirElemNaoOrd(&catalogo, "173457", "oleo de girassol Liza 900ml", "Oleo vegetal", "2", 0, 10, 9.8, 100);
    inserirElemNaoOrd(&catalogo, "173458", "oleo de milho Liza 900ml", "Oleo vegetal", "2", 0, 13.9, 13.7, 100);
    inserirElemNaoOrd(&catalogo, "173459", "oleo de canola Liza 900ml", "Oleo vegetal", "2", 0, 12.9, 11.9, 100);
    inserirElemNaoOrd(&catalogo, "173460", "azeite de oliva extra virgem Gallo 500ml", "Oleo vegetal", "2", 0, 15, 14.2, 100);
    inserirElemNaoOrd(&catalogo, "173461", "azeite de oliva extra virgem Andorinha 500ml", "Oleo vegetal", "2", 0, 13.2, 12.2, 100);
    inserirElemNaoOrd(&catalogo, "173462", "azeite de oliva extra virgem reserva Gallo 500ml", "Oleo vegetal", "2", 0, 28.9, 28.5, 100);
    inserirElemNaoOrd(&catalogo, "173463", "azeite de oliva extra virgem premium Gallo 500ml", "Oleo vegetal", "2", 0, 54, 52, 100);
    //6 não-pereciveis comuns
    inserirElemNaoOrd(&catalogo, "183456", "arroz Tio Joao 5kg", "Arroz", "2", 0, 30, 28, 50);
    inserirElemNaoOrd(&catalogo, "183457", "arroz Tio Joao 1kg", "Arroz", "2", 0, 8, 7.5, 50);
    inserirElemNaoOrd(&catalogo, "183458", "feijao preto Tio Joao 1kg", "Feijao", "2", 0, 7, 6.5, 50);
    inserirElemNaoOrd(&catalogo, "183459", "feijao carioca Camil 1kg", "Feijao", "2", 0, 8, 7.5, 50);
    inserirElemNaoOrd(&catalogo, "183460", "feijao preto Broto Legal 1kg", "Feijao", "2", 0, 8.5, 8, 50);
    inserirElemNaoOrd(&catalogo, "183461", "acucar cristal 2kg", "Acucar", "2", 0, 7, 6.5, 50);

    //exibirLista(&catalogo);
    //printf("quantidade de intens: %d", tamanho(&catalogo));

    i = 5;
    while (i != 0)
    {

        printf("\nEscolha a acao desejada\n1-Login\n2-Encerrar programa\n");
        scanf("%d", &j);
        if (j == 1)
        {
            i = 0;
            printf("\nDeseja logar como:\n1-Consumidor\n2-Vendedor\n3-Gerente\n");
            scanf("%d", &j);
            printf("\nDigite seu login e senha\n");
            if (j == 1)
            {
                scanf("%s", input1);
                scanf("%s", input2);
                teste = checarConta(&cliente, input1, input2);
                if (teste != true)
                {
                    i = 5;
                    printf("\nDados incorretos, tente novamente\n");
                }
                else
                {
                    contaAtual = cliente;
                    conta = 1;
                }
            }
            else if (j == 2)
            {
                scanf("%s", input1);
                scanf("%s", input2);
                teste = checarConta(&vendedor, input1, input2);
                if (teste != true)
                {
                    i = 5;
                    printf("\nDados incorretos, tente novamente\n");
                }
                else
                {
                    contaAtual = vendedor;
                    conta = 2;
                }
            }
            else if (j == 3)
            {
                scanf("%s", input1);
                scanf("%s", input2);
                teste = checarConta(&gerente, input1, input2);
                if (teste != true)
                {
                    i = 5;
                    printf("\nDados incorretos, tente novamente\n");
                }
                else
                {
                    contaAtual = gerente;
                    conta = 3;
                }
            }
            else
            {
                i = 5;
                printf("\nAcao nao-valida, tente novamente\n");
            }
        }
        else if (j == 2)
        {
            printf("\nObrigado pela preferencia\n");
            return 0;
        }
    }
    j = 0;
    if (conta == 1)
    {
        printf("\nSeja bem vindo\n");
        while (j != 3)
        {
            printf("\nDeseja:\n1-Checar informacoes da conta\n2-Buscar um produto\n3-Encerrar programa\n4-Finalizar compra\n");
            scanf("%d", &j);

            if (j == 3)
            {
                return 0;
            }
            else if (j == 1)
            {
                exibirConta(&contaAtual);
            }
            else if (j == 2)
            {
                printf("\nDeseja buscar o produto pelo:\n1-Codigo de barras\n2-Nome do produto\n3-Produtos de determinado tipo (ex:arroz)\n");
                scanf("%d%*c", &k);
                if (k == 1)
                {
                    printf("\nDigite o código de barras referente ao produto desejado\n");
                    scanf("%s", codBarras);
                    produto = buscarElemento(codBarras, &catalogo, &aux);
                    if (produto == NULL)
                    {
                        printf("\nProduto não encontrado, tente novamente\n");
                    }
                    else
                    {
                        exibirBuscaNome(&catalogo, produto->reg.nome);
                        printf("\nDeseja adicionar o produto ao carrinho?\n1-SIM\n2-NAO\n");
                        scanf("%d", &k);
                        if (k == 1)
                        {
                            printf("\nDigite a quantidade a ser comprada\n");
                            scanf("%f", &quantidade);
                            if (quantidade <= produto->reg.estoque)
                            {
                                inserirProdutoCarrinho(&carrinho, produto, quantidade);
                            }
                            else
                            {
                                printf("\nInfelizmente nao possuimos a quantidade desejada em estoque, tente novamente\n");
                            }
                        }
                    }
                }
                else if (k == 2)
                {
                    printf("\nDigite o nome do produto desejado\n");

                    scanf("%1023[^\n]", nome);
                    produto = buscarElementoNome(nome, &catalogo);
                    if (produto == NULL)
                    {
                        printf("\nProduto nao encontrado, tente novamente\n");
                    }
                    else
                    {
                        exibirBuscaNome(&catalogo, nome);
                        printf("\nDeseja adicionar o produto ao carrinho?\n1-SIM\n2-NAO\n");
                        scanf("%d", &k);
                        if (k == 1)
                        {
                            printf("\nDigite a quantidade a ser comprada\n");
                            scanf("%f", &quantidade);
                            if (quantidade <= produto->reg.estoque)
                            {
                                inserirProdutoCarrinho(&carrinho, produto, quantidade);
                            }
                            else
                            {
                                printf("\nInfelizmente nao possuimos a quantidade desejada em estoque, tente novamente\n");
                            }
                        }
                    }
                }
                else if (k == 3)
                {
                    printf("\nDigite o tipo de produto que deseja buscar\n");
                    scanf("%1023[^\n]", tipo);
                    buscarElementoTipo(&catalogo, tipo);
                    printf("\nPara efetuar a compra, busque pelo produto especifico de desejo pelo codigo de barras ou nome\n");
                }
            }
            else if (j == 4)
            {
                iterator = carrinho.inicio;
                if (iterator == NULL)
                {
                    printf("\nNao foram inseridos produtos no carrinho, por favor, busque pelos produtos desejados e os insira\n");
                }
                else
                {
                    exibirLista(&carrinho);
                    while (iterator != NULL)
                    {
                        val += comprarProduto(iterator, iterator->reg.estoque, &catalogo, &carrinho);
                        iterator = iterator->prox;
                    }
                    printf("\nValor total da compra:\nR$%.2f\n", val);
                    printf("\nForma de pagamento sera cartao de:\n1-Debito\n2-Credito\n");
                    scanf("%d", &k);
                    printf("\nInsira os dados do seu cartao na sequencia:\nNumero\nCodigo de seguranca\nMes de validade\nAno de validade\n");
                    scanf("%f", &nCartao);
                    scanf("%f", &cSeg);
                    scanf("%f", &mesV);
                    scanf("%f", &anoV);
                    if (k == 1)
                    {
                        if (checarCartao(&cartaoDebito, nCartao, mesV, anoV, cSeg, '1') == true)
                        {
                            exibeDebitarDebito(&cartaoDebito, val);
                            depositarCartaoDebito(&cartaoMercado, val);
                            reinicializarLista(&carrinho);
                            val = 0;
                        }
                        else
                        {
                            printf("\nDados invalidos, tente novamente\n");
                        }
                    }
                    else if (k == 2)
                    {
                        if (checarCartao(&cartaoCredito, nCartao, mesV, anoV, cSeg, '2') == true)
                        {
                            exibeDebitarCredito(&cartaoCredito, val);
                            depositarCartaoDebito(&cartaoMercado, val);
                            reinicializarLista(&carrinho);
                            val = 0;
                        }
                        else
                        {
                            printf("\nDados invalidos, tente novamente\n");
                        }
                    }
                    else
                    {
                        printf("\nEntrada invalida, tente novamente\n");
                    }
                }
            }
        }
    }
    /*


PARTE DO VENDEDOR

    */
    else if (conta == 2)
    {
        while (j != 3)
        {
            printf("\nDeseja:\n1-Checar informacoes da conta\n2-Buscar um produto\n3-Encerrar programa\n4-Efetuar venda\n5-Finalizar venda\n");

            scanf("%d%*c", &j);
            if (j == 1)
            {
                exibirConta(&contaAtual);
            }
            else if (j == 3)
            {
                return 0;
            }
            else if (j == 2)
            {
                printf("\nDeseja buscar o produto pelo:\n1-Codigo de barras\n2-Nome do produto\n3-Produtos de determinado tipo (ex:arroz)\n");
                scanf("%d%*c", &k);
                if (k == 1)
                {
                    printf("\nDigite o código de barras referente ao produto desejado\n");
                    scanf("%s", codBarras);
                    produto = buscarElemento(codBarras, &catalogo, &aux);
                    if (produto == NULL)
                    {
                        printf("\nProduto não encontrado, tente novamente\n");
                    }
                    else
                    {
                        exibirBuscaNome(&catalogo, produto->reg.nome);
                        printf("\nDeseja adicionar o produto ao carrinho?\n1-SIM\n2-NAO\n");
                        scanf("%d", &k);
                        if (k == 1)
                        {
                            printf("\nDigite a quantidade a ser comprada\n");
                            scanf("%f", &quantidade);
                            if (quantidade <= produto->reg.estoque)
                            {
                                inserirProdutoCarrinho(&carrinho, produto, quantidade);
                            }
                            else
                            {
                                printf("\nInfelizmente nao possuimos a quantidade desejada em estoque, tente novamente\n");
                            }
                        }
                    }
                }
                else if (k == 2)
                {
                    printf("\nDigite o nome do produto desejado\n");

                    scanf("%1023[^\n]", nome);
                    produto = buscarElementoNome(nome, &catalogo);
                    if (produto == NULL)
                    {
                        printf("\nProduto nao encontrado, tente novamente\n");
                    }
                    else
                    {
                        exibirBuscaNome(&catalogo, nome);
                        printf("\nDeseja adicionar o produto ao carrinho?\n1-SIM\n2-NAO\n");
                        scanf("%d", &k);
                        if (k == 1)
                        {
                            printf("\nDigite a quantidade a ser comprada\n");
                            scanf("%f", &quantidade);
                            if (quantidade <= produto->reg.estoque)
                            {
                                inserirProdutoCarrinho(&carrinho, produto, quantidade);
                            }
                            else
                            {
                                printf("\nInfelizmente nao possuimos a quantidade desejada em estoque, tente novamente\n");
                            }
                        }
                    }
                }
                else if (k == 3)
                {
                    printf("\nDigite o tipo de produto que deseja buscar\n");
                    scanf("%1023[^\n]", tipo);
                    buscarElementoTipo(&catalogo, tipo);
                    printf("\nPara efetuar a compra, busque pelo produto especifico de desejo pelo codigo de barras ou nome\n");
                }
            }
            else if (j == 4)
            {
                int u;
                TIPOCHAVE nulo;
                k = 1;
                while (k != 2)
                {
                    printf("\nInsira o codigo de barras do produto\n");
                    scanf("%s", codBarras);

                    produto = buscarElemento(codBarras, &catalogo, &aux);

                    printf("\nDigite a quantidade a ser comprada\n");
                    scanf("%f", &quantidade);
                    inserirProdutoCarrinho(&carrinho, produto, quantidade);
                    printf("\nDeseja continuar?\n1-sim\n2-nao\n");
                    scanf("%d", &k);
                }
                iterator = carrinho.inicio;
                if (iterator == NULL)
                {
                    return 0;
                }
                exibirLista(&carrinho);
                while (iterator != NULL)
                {
                    val += comprarProduto(iterator, iterator->reg.estoque, &catalogo, &carrinho);
                    iterator = iterator->prox;
                }
                printf("\nValor total da compra:\nR$%.2f\n", val);
                printf("\nDefina o metodo de pagamento:\n1-Cartao\n2-Dinheiro\n");
                scanf("%d", &u);
                if (u == 2)
                {
                    float dinheiro;
                    printf("\nDigite quantia recebida\n");
                    scanf("%f", &dinheiro);
                    printf("\nTroco: R$%.2f", dinheiro - val);
                    depositarCartaoDebito(&cartaoMercado, val);
                    printf("\nCompra realizada com sucesso\n");
                    reinicializarLista(&carrinho);
                    val = 0;
                }
                else if (u == 1)
                {
                    printf("\nDefina o tipo do cartao:\n1-Debito\n2-Credito\n");
                    scanf("%d", &k);
                    printf("\nInsira os dados do cartao na sequencia:\nNumero\nCodigo de seguranca\nMes de validade\nAno de validade\n");
                    scanf("%f", &nCartao);
                    scanf("%f", &cSeg);
                    scanf("%f", &mesV);
                    scanf("%f", &anoV);
                    if (k == 1)
                    {
                        if (checarCartao(&cartaoDebito, nCartao, mesV, anoV, cSeg, '1') == true)
                        {
                            exibeDebitarDebito(&cartaoDebito, val);
                            depositarCartaoDebito(&cartaoMercado, val);
                            reinicializarLista(&carrinho);
                            val = 0;
                        }
                        else
                        {
                            printf("\nDados invalidos, tente novamente\n");
                        }
                    }
                    else if (k == 2)
                    {
                        if (checarCartao(&cartaoCredito, nCartao, mesV, anoV, cSeg, '2') == true)
                        {
                            exibeDebitarCredito(&cartaoCredito, val);
                            depositarCartaoDebito(&cartaoMercado, val);
                            reinicializarLista(&carrinho);
                            val = 0;
                        }
                        else
                        {
                            printf("\nDados invalidos, tente novamente\n");
                        }
                    }
                    else
                    {
                        printf("\nEntrada invalida, tente novamente\n");
                    }
                }
            }
            else if (j == 5)
            {
                int u;
                iterator = carrinho.inicio;
                if (iterator == NULL)
                {
                    printf("\nNao foram inseridos produtos no carrinho, por favor, busque pelos produtos desejados e os insira\n");
                }
                else
                {
                    exibirLista(&carrinho);
                    while (iterator != NULL)
                    {
                        val += comprarProduto(iterator, quantidade, &catalogo, &carrinho);
                        iterator = iterator->prox;
                    }
                    printf("\nValor total da compra:\nR$%.2f\n", val);
                    printf("\nDefina o metodo de pagamento:\n1-Cartao\n2-Dinheiro\n");
                    scanf("%d", &u);
                    if (u == 2)
                    {
                        float dinheiro;
                        printf("\nDigite quantia recebida\n");
                        scanf("%f", &dinheiro);
                        printf("\nTroco: R$%.2f", dinheiro - val);
                        depositarCartaoDebito(&cartaoMercado, val);
                        printf("\nCompra realizada com sucesso\n");
                        reinicializarLista(&carrinho);
                    }
                    else if (u == 1)
                    {
                        printf("\nDefina o tipo do cartao:\n1-Debito\n2-Credito\n");
                        scanf("%d", &k);
                        printf("\nInsira os dados do cartao na sequencia:\nNumero\nCodigo de seguranca\nMes de validade\nAno de validade\n");
                        scanf("%f", &nCartao);
                        scanf("%f", &cSeg);
                        scanf("%f", &mesV);
                        scanf("%f", &anoV);
                        if (k == 1)
                        {
                            if (checarCartao(&cartaoDebito, nCartao, mesV, anoV, cSeg, '1') == true)
                            {
                                exibeDebitarDebito(&cartaoDebito, val);
                                depositarCartaoDebito(&cartaoMercado, val);
                                reinicializarLista(&carrinho);
                            }
                            else
                            {
                                printf("\nDados invalidos, tente novamente\n");
                            }
                        }
                        else if (k == 2)
                        {
                            if (checarCartao(&cartaoCredito, nCartao, mesV, anoV, cSeg, '2') == true)
                            {
                                exibeDebitarCredito(&cartaoCredito, val);
                                depositarCartaoDebito(&cartaoMercado, val);
                                reinicializarLista(&carrinho);
                            }
                            else
                            {
                                printf("\nDados invalidos, tente novamente\n");
                            }
                        }
                        else
                        {
                            printf("\nEntrada invalida, tente novamente\n");
                        }
                    }
                }
            }
        }
    }
    else if (conta == 3)
    {
        while (j != 3)
        {
            printf("\nDeseja:\n1-Checar informacoes da conta\n2-Buscar um produto\n3-Encerrar programa\n4-Efetuar venda\n5-Finalizar venda\n6-Repor estoque\n7-Alterar preco de um produto\n");

            scanf("%d%*c", &j);
            if (j == 1)
            {
                exibirConta(&contaAtual);
            }
            else if (j == 3)
            {
                return 0;
            }
            else if (j == 2)
            {
                printf("\nDeseja buscar o produto pelo:\n1-Codigo de barras\n2-Nome do produto\n3-Produtos de determinado tipo (ex:arroz)\n");
                scanf("%d%*c", &k);
                if (k == 1)
                {
                    printf("\nDigite o código de barras referente ao produto desejado\n");
                    scanf("%s", codBarras);
                    produto = buscarElemento(codBarras, &catalogo, &aux);
                    if (produto == NULL)
                    {
                        printf("\nProduto não encontrado, tente novamente\n");
                    }
                    else
                    {
                        exibirBuscaNome(&catalogo, produto->reg.nome);
                        printf("\nDeseja adicionar o produto ao carrinho?\n1-SIM\n2-NAO\n");
                        scanf("%d", &k);
                        if (k == 1)
                        {
                            printf("\nDigite a quantidade a ser comprada\n");
                            scanf("%f", &quantidade);
                            if (quantidade <= produto->reg.estoque)
                            {
                                inserirProdutoCarrinho(&carrinho, produto, quantidade);
                            }
                            else
                            {
                                printf("\nInfelizmente nao possuimos a quantidade desejada em estoque, tente novamente\n");
                            }
                        }
                    }
                }
                else if (k == 2)
                {
                    printf("\nDigite o nome do produto desejado\n");

                    scanf("%1023[^\n]", nome);
                    produto = buscarElementoNome(nome, &catalogo);
                    if (produto == NULL)
                    {
                        printf("\nProduto nao encontrado, tente novamente\n");
                    }
                    else
                    {
                        exibirBuscaNome(&catalogo, nome);
                        printf("\nDeseja adicionar o produto ao carrinho?\n1-SIM\n2-NAO\n");
                        scanf("%d", &k);
                        if (k == 1)
                        {
                            printf("\nDigite a quantidade a ser comprada\n");
                            scanf("%f", &quantidade);
                            if (quantidade <= produto->reg.estoque)
                            {
                                inserirProdutoCarrinho(&carrinho, produto, quantidade);
                            }
                            else
                            {
                                printf("\nInfelizmente nao possuimos a quantidade desejada em estoque, tente novamente\n");
                            }
                        }
                    }
                }
                else if (k == 3)
                {
                    printf("\nDigite o tipo de produto que deseja buscar\n");
                    scanf("%1023[^\n]", tipo);
                    buscarElementoTipo(&catalogo, tipo);
                    printf("\nPara efetuar a compra, busque pelo produto especifico de desejo pelo codigo de barras ou nome\n");
                }
            }
            else if (j == 4)
            {
                int u;
                TIPOCHAVE nulo;
                k = 1;
                while (k != 2)
                {
                    printf("\nInsira o codigo de barras do produto\n");
                    scanf("%s", codBarras);

                    produto = buscarElemento(codBarras, &catalogo, &aux);

                    printf("\nDigite a quantidade a ser comprada\n");
                    scanf("%f", &quantidade);
                    inserirProdutoCarrinho(&carrinho, produto, quantidade);
                    printf("\nDeseja continuar?\n1-sim\n2-nao\n");
                    scanf("%d", &k);
                }
                iterator = carrinho.inicio;
                if (iterator == NULL)
                {
                    return 0;
                }
                exibirLista(&carrinho);
                while (iterator != NULL)
                {
                    val += comprarProduto(iterator, iterator->reg.estoque, &catalogo, &carrinho);
                    iterator = iterator->prox;
                }
                printf("\nValor total da compra:\nR$%.2f\n", val);
                printf("\nDefina o metodo de pagamento:\n1-Cartao\n2-Dinheiro\n");
                scanf("%d", &u);
                if (u == 2)
                {
                    float dinheiro;
                    printf("\nDigite quantia recebida\n");
                    scanf("%f", &dinheiro);
                    printf("\nTroco: R$%.2f", dinheiro - val);
                    depositarCartaoDebito(&cartaoMercado, val);
                    printf("\nCompra realizada com sucesso\n");
                    reinicializarLista(&carrinho);
                    val = 0;
                }
                else if (u == 1)
                {
                    printf("\nDefina o tipo do cartao:\n1-Debito\n2-Credito\n");
                    scanf("%d", &k);
                    printf("\nInsira os dados do cartao na sequencia:\nNumero\nCodigo de seguranca\nMes de validade\nAno de validade\n");
                    scanf("%f", &nCartao);
                    scanf("%f", &cSeg);
                    scanf("%f", &mesV);
                    scanf("%f", &anoV);
                    if (k == 1)
                    {
                        if (checarCartao(&cartaoDebito, nCartao, mesV, anoV, cSeg, '1') == true)
                        {
                            exibeDebitarDebito(&cartaoDebito, val);
                            depositarCartaoDebito(&cartaoMercado, val);
                            reinicializarLista(&carrinho);
                            val = 0;
                        }
                        else
                        {
                            printf("\nDados invalidos, tente novamente\n");
                        }
                    }
                    else if (k == 2)
                    {
                        if (checarCartao(&cartaoCredito, nCartao, mesV, anoV, cSeg, '2') == true)
                        {
                            exibeDebitarCredito(&cartaoCredito, val);
                            depositarCartaoDebito(&cartaoMercado, val);
                            reinicializarLista(&carrinho);
                            val = 0;
                        }
                        else
                        {
                            printf("\nDados invalidos, tente novamente\n");
                        }
                    }
                    else
                    {
                        printf("\nEntrada invalida, tente novamente\n");
                    }
                }
            }
            else if (j == 5)
            {
                int u;
                iterator = carrinho.inicio;
                if (iterator == NULL)
                {
                    printf("\nNao foram inseridos produtos no carrinho, por favor, busque pelos produtos desejados e os insira\n");
                }
                else
                {
                    exibirLista(&carrinho);
                    while (iterator != NULL)
                    {
                        val += comprarProduto(iterator, quantidade, &catalogo, &carrinho);
                        iterator = iterator->prox;
                    }
                    printf("\nValor total da compra:\nR$%.2f\n", val);
                    printf("\nDefina o metodo de pagamento:\n1-Cartao\n2-Dinheiro\n");
                    scanf("%d", &u);
                    if (u == 2)
                    {
                        float dinheiro;
                        printf("\nDigite quantia recebida\n");
                        scanf("%f", &dinheiro);
                        printf("\nTroco: R$%.2f", dinheiro - val);
                        depositarCartaoDebito(&cartaoMercado, val);
                        printf("\nCompra realizada com sucesso\n");
                        reinicializarLista(&carrinho);
                    }
                    else if (u == 1)
                    {
                        printf("\nDefina o tipo do cartao:\n1-Debito\n2-Credito\n");
                        scanf("%d", &k);
                        printf("\nInsira os dados do cartao na sequencia:\nNumero\nCodigo de seguranca\nMes de validade\nAno de validade\n");
                        scanf("%f", &nCartao);
                        scanf("%f", &cSeg);
                        scanf("%f", &mesV);
                        scanf("%f", &anoV);
                        if (k == 1)
                        {
                            if (checarCartao(&cartaoDebito, nCartao, mesV, anoV, cSeg, '1') == true)
                            {
                                exibeDebitarDebito(&cartaoDebito, val);
                                depositarCartaoDebito(&cartaoMercado, val);
                                reinicializarLista(&carrinho);
                            }
                            else
                            {
                                printf("\nDados invalidos, tente novamente\n");
                            }
                        }
                        else if (k == 2)
                        {
                            if (checarCartao(&cartaoCredito, nCartao, mesV, anoV, cSeg, '2') == true)
                            {
                                exibeDebitarCredito(&cartaoCredito, val);
                                depositarCartaoDebito(&cartaoMercado, val);
                                reinicializarLista(&carrinho);
                            }
                            else
                            {
                                printf("\nDados invalidos, tente novamente\n");
                            }
                        }
                        else
                        {
                            printf("\nEntrada invalida, tente novamente\n");
                        }
                    }
                }
            }
            else if (j == 6)
            {
                char um = "1";
                char dois = "2";
                printf("\nDigite o codigo de barras do produto que deseja repor o estoque\n");
                scanf("%s", codBarras);
                produto = buscarElemento(codBarras, &catalogo, &aux);
                printf("\nProduto especificado:\n");
                exibirProduto(codBarras, &catalogo);
                printf("\nDigite a quantidade que será reposta\n");
                scanf("%f", &quantidade);
                if (produto->reg.categoria == um)
                {
                    val = produto->reg.precoQuilo * quantidade;
                }
                else if (produto->reg.categoria == dois && quantidade >= 50)
                {
                    val = produto->reg.precoAtacado * quantidade;
                }
                else
                {
                    val = produto->reg.precoUnidade * quantidade;
                }
                if (val > cartaoMercado.saldo)
                {
                    printf("\nNao ha saldo suficiente para tal reabastecimento\n");
                }
                else
                {
                    produto->reg.estoque += quantidade;
                    cartaoMercado.saldo -= val;
                    printf("\nReposicao feita com sucesso\n");
                    exibirProduto(codBarras, &catalogo);
                }

                val = 0;
            }
            else if (j == 7)
            {
                char um = "1";
                char dois = "2";
                float precoNovo;
                printf("\nDigite o codigo de barras do produto cujo preco sera alterado\n");
                scanf("%s", codBarras);
                produto = buscarElemento(codBarras, &catalogo, &aux);
                printf("\nProduto especificado:\n");
                exibirProduto(codBarras, &catalogo);
                if (produto->reg.categoria == um)
                {
                    printf("\nDigite o novo preco por quilo do produto\n");
                    scanf("%f", &precoNovo);
                    produto->reg.precoQuilo = precoNovo;
                }
                else
                {
                    printf("\nDigite o novo preco por unidade avulsa do produto\n");
                    scanf("%f", &precoNovo);
                    produto->reg.precoUnidade = precoNovo;
                    printf("\nDigite o novo preco por unidade em atacado do produto\n");
                    scanf("%f", &precoNovo);
                    produto->reg.precoAtacado = precoNovo;
                }
                printf("\nProduto apos alteracao de preco\n");
                exibirProduto(codBarras, &catalogo);
            }
        }
    }
}