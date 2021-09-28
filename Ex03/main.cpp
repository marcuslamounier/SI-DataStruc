#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iomanip>

#include <iostream>

using namespace std;

typedef struct produto produto;

struct produto {
    char nome[40];
    int codigo;
    double preco;
    int quantidade;
};

void cadastrarNome(char *nome) {
    char n[40];
    cout << "Nome: ";
    scanf("%s", &n);
    strcpy(nome, n);
}

int cadastrarCodigo() {
    srand(time(0));
    int codigo = rand() % 50;
    cout << "Codigo " << codigo << endl;;
    return codigo;
}

void cadastrarPreco(double *preco) {
    double p;
    do {
        cout << "Preco: ";
        cin >> p;
        if (p <= 0) cout << "O preco deve ser positivo." << endl;
    } while (p <= 0);
    *preco = p;
}

void cadastrarQuantidade(produto *listaProdutos) {
    int quantidade;
    cout << "Quantidade: ";
    do {
        cin >> quantidade;
        if (quantidade < 0) cout << "A quantidade nao pode ser negativa." << endl;
    } while (quantidade < 0);
    listaProdutos->quantidade = quantidade;
}

produto *preencherDados(int *quantidade) {

    produto *produtos = (produto*) malloc((*quantidade) * sizeof(produto));

    produto *listaProdutos;
    listaProdutos = produtos;

    for (int i = 1; i <= *quantidade; i++) {

        cout << endl;
        cout << "PRODUTO " << i << endl;

        int codigo = cadastrarCodigo();
        listaProdutos->codigo = codigo;

        char nome[40];
        char *ptrNome;
        ptrNome = nome;
        cadastrarNome(ptrNome);
        strcpy(listaProdutos->nome, nome);

        double preco;
        cadastrarPreco(&preco);
        listaProdutos->preco = preco;

        cadastrarQuantidade(listaProdutos);

        listaProdutos += sizeof(produto);
    }

    return produtos;
}

produto* cadastrarProdutos(int *quantidade) {
    int q;

    do {
        cout << "Digite a quantidade de produtos: ";
        cin >> q;
        if (q <= 0) cout << "A quantidade deve ser positiva." << endl;
    } while (q <= 0);

    *quantidade = q;

    produto *produtos = (produto*) malloc((*quantidade) * sizeof(produto));

    produto *listaProdutos;
    listaProdutos = preencherDados(quantidade);

    return listaProdutos;
}

void imprimirProduto(produto *p, int pos) {
    cout << "PRODUTO " << pos << endl;
    cout << "Codigo: " << p->codigo << endl;
    cout << "Nome: " << p->nome << endl;
    cout << "Preco: " << std::fixed << std::setprecision(2) << p->preco << endl;
    cout << "Quantidade: " << p->quantidade << endl;
    cout << endl;
}

void listarProdutos(produto *ptrProduto, int *quantidade, int pos) {

    imprimirProduto(ptrProduto, pos);

    if (pos < *quantidade) {
        ptrProduto += sizeof(produto);
        pos++;
        listarProdutos(ptrProduto, quantidade, pos);
    }
}

void imprimirMenu() {
    cout << "CADASTRO DE PRODUTOS" << endl;
    cout << "A - Preencher dados" << endl;
    cout << "B - Exibir produtos cadastrados no estoque" << endl;
    cout << "C - Finalizar" << endl;
}

int main () {

    char opcao;

    int quantidade;
    int *ptrQuantidade;
    ptrQuantidade = &quantidade;

    produto *produtos;

    do {
        cout << endl;
        imprimirMenu();
        cout << "Opcao escolhida: ";
        cin >> opcao;
        cout << endl;

        switch (opcao) {
            case 'A':
                produtos = cadastrarProdutos(ptrQuantidade);
                system("cls");
                break;
            case 'B':
                listarProdutos(produtos, ptrQuantidade, 1);
                break;
            case 'C':
                break;

            default:
                cout <<"Digite uma opcao valida!" << endl;
        }
    } while (opcao != 'C');

    system("pause");
    return 0;
}