#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define CADPRODUTO "produtos.dat"
#define CADCLIENTE "clientes.dat"
/*Ricardo de Moraes Gonçalves*/
struct Produto {
    int codigo;
    char descricao[100];
    int estoque;
    int estoqueMinimo;
    float preco;
};
struct Cliente {
    int codigo;
    char nome[50];
    char endereco[50];
    char telefone[50];
    char email[50];
    char dataDeNascimento[11];
};
int codigoProduto() {
    //Automatiza a atribuição de códigos para o cadastro de produtos
    FILE *fpprodutos;
    struct Produto produto;
    int codigo;
    int resposta;
    int incrementaCodigo=0;

    fpprodutos = fopen(CADPRODUTO, "rb");
    if (fpprodutos == NULL) {

        printf("É o primeiro cadastro?! \n");
        printf("1 - Sim!\n");
        printf("0 - Não!\n");
        scanf("%i", &resposta);
        if(resposta) {
            codigo = 1;
            incrementaCodigo++;
        } else {
            printf("Erro na abertura ou arquivo ainda não existe!\n");
            system("pause");
            return;
        }
    } else {
        while (fread(&produto,sizeof(produto),1,fpprodutos) == 1) {
            incrementaCodigo++;//conta quantos cadastros de produto existem.
        }//Fim while.
        fclose(fpprodutos);

        codigo = incrementaCodigo++; //acrescenta o novo na contagem.
    }
    return codigo;
}
int codigoCliente() {
    //Automatiza a atribuição de códigos para o cadastro de produtos
    FILE *fpcliente;
    struct Cliente cliente;
    int codigo;
    int resposta;
    int incrementaCodigo=0;

    fpcliente = fopen(CADCLIENTE, "rb");
    if (fpcliente == NULL) {

        printf("É o primeiro cadastro?! \n");
        printf("1 - Sim!\n");
        printf("0 - Não!\n");
        scanf("%i", &resposta);
        if(resposta) {
            codigo = 1;
        } else {
            printf("Erro na abertura ou arquivo ainda não existe!!\n");
            system("pause");
            return;
        }
    } else {
        while (fread(&cliente,sizeof(cliente),1,fpcliente) == 1) {
            incrementaCodigo++;//conta quantos clientes cadastrados existem.
        }//Fim while.
        fclose(fpcliente);

        codigo = incrementaCodigo++; //acrescenta o novo na contagem.
    }
    return codigo;
}
//(1)1-CADASTRAR PRODUTOS
void CadastrarProdutos() {
    setlocale(LC_ALL,"Portuguese");

    FILE *fpprodutos;
    struct Produto produto;
    int opcao;

//RECEBE DADOS DO TECLADO
    system("cls");
    printf("\nCADASTRO DE PRODUTOS\n");
    printf("\nDescrição do Produto: ");
    fflush(stdin);
    gets(produto.descricao);

    printf("\nQuantidade em Estoque: ");
    fflush(stdin);
    scanf("%i", &produto.estoque);

    printf("\nQuantidade Mínima para o estoque: ");
    fflush(stdin);
    scanf("%i", &produto.estoqueMinimo);

    printf("\nPreço: ");
    fflush(stdin);
    scanf("%f", &produto.preco);

    //receber o código via teclado:
    /*
    printf("\nCódigo Produto: ");
    fflush(stdin);
    scanf("%i", &produto.codigo);
    */

    //Automatiza a atribuição de código:
    produto.codigo = codigoProduto();

    printf("\nConfirma Cadastro?");
    printf("\n0 - NÃO");
    printf("\n1 - SIM\n");
    scanf("%i", &opcao);
    switch (opcao) {
    case 1 : { //Gravar produto
        fpprodutos = fopen(CADPRODUTO, "ab");
        if (fpprodutos == NULL) {
            printf("Erro na abertura ou arquivo ainda não existe!\n");
            system("pause");
            return;
        }
        fwrite(&produto,sizeof(produto),1,fpprodutos);

        printf("\n");
        printf("\nCódigo: %7i ", produto.codigo);
        printf("\n%s ", produto.descricao);
        printf("\nQuantidade em Estoque: %7i ", produto.estoque);
        printf("\nEstoque Mínimo: %7i ", produto.estoqueMinimo);
        printf("\nPreço R$ %.2f ", produto.preco);
        printf("\n\n");
        fclose(fpprodutos);
        break;
    }//Fim case 1

    case 0 :
        printf("Cadastro Cancelado! ");
        //retornar para o main.
        break;
    default:
        printf("\nOpção inválida! ");
    }
    system("pause");
}
//FimCadastrarProdutos

//(2)1.1-CONSULTAR PRODUTO POR PALAVRA CHAVE NA DESCRIÇÃO DO PRODUTO
void ConsultarProdutoDescricao() {
    setlocale(LC_ALL,"Portuguese");

    FILE *fpprodutos;
    struct Produto produto;
    char pesquisaProduto[20];
    int achou=0;

    system("cls");
    printf("\nPesquisar produto por descrição: \t");
    fflush(stdin);
    gets(pesquisaProduto);

    fpprodutos = fopen(CADPRODUTO, "rb");
    if (fpprodutos == NULL) {
        printf("Erro na abertura ou arquivo ainda não existe!!\n");
        system("pause");
            return;;
    }
    while (fread(&produto,sizeof(produto),1,fpprodutos) == 1) {
            //Se a palavra pesquisada faz parte da descrição do produto
        if(strstr(produto.descricao, pesquisaProduto) != NULL){
            achou = 1;
            printf("\n%s, %i, Estoque %i, Estoque mínimo %i, R$ %.2f", produto.descricao, produto.codigo, produto.estoque, produto.estoqueMinimo, produto.preco);
        }//FimIf.

    }//FimWhile
    fclose(fpprodutos);

    if(!achou) {
        printf("\nProduto NÃO encontrado! \n");
    }
    system("pause");
}
//FimConsultarProdutoPorPalavraChave
void listarCadastro() {
    FILE *fpprodutos;
    struct Produto produto;

    fpprodutos = fopen(CADPRODUTO, "rb");
    if (fpprodutos == NULL) {
        printf("Erro na abertura ou arquivo ainda não existe!!\n");
        system("pause");
            return;
    }
    system("cls");
    printf("CADASTRO DE PRODUTOS\n");
    printf("\nCódigo - Descrição - Est. - E.Min. - Preço\n");
    while (fread(&produto,sizeof(produto),1,fpprodutos) == 1) {
        printf(
               "\n%4i - %-10s - %3i un. \t- %3i un. \t- R$ %3.2f",
                produto.codigo,
                produto.descricao,
                produto.estoque,
                produto.estoqueMinimo,
                produto.preco
        );
    }
    printf("\n");
    fclose(fpprodutos);
    system("pause");
}
//(3)1.2-RELATAR PRODUTOS COM ESTOQUE MÍNIMO
void estoqueMinimo() {
    FILE *fpprodutos;
    struct Produto produto;
    fpprodutos = fopen(CADPRODUTO, "rb");
    if (fpprodutos == NULL) {
        printf("Erro na abertura ou arquivo ainda não existe!!\n");
        system("pause");
            return;
    }
    system("cls");
    printf("PRODUTOS COM ESTOQUE MÍNIMO\n");
    while (fread(&produto,sizeof(produto),1,fpprodutos) == 1) {
        if(produto.estoque <= produto.estoqueMinimo) {
            printf("\n %i - %s - Estoque Mínimo %i - Estoque Atual ",
                   produto.codigo, produto.descricao, produto.estoqueMinimo, produto.estoque );
        }
    }
    fclose(fpprodutos);
    system("pause");
}
//FimRelatarProdutosComEstoqueMinimo

//(4)2-CADASTRAR CLIENTES
void CadastrarClientes(){
    setlocale(LC_ALL,"Portuguese");
    FILE *fpclientes;
    struct Cliente cliente;
    int opcao;
//RECEBE DADOS DO CLIENTE (TECLADO)
    system("cls");
    printf("\nCADASTRO DE CLIENTES\n");
    printf("\nNome: ");
    fflush(stdin);
    gets(cliente.nome);

    printf("\nEndereço: ");
    fflush(stdin);
    gets(cliente.endereco);

    printf("\nTelefone: ");
    fflush(stdin);
    gets(cliente.telefone);

    printf("\nE-mail: ");
    fflush(stdin);
    gets(cliente.email);

    printf("\nData de Nascimento: ");
    fflush(stdin);
    gets(cliente.dataDeNascimento);
     //Automatiza a atribuição de código:
    cliente.codigo = codigoCliente();
    printf("\nConfirma Cadastro?");
    printf("\n0 - NÃO");
    printf("\n1 - SIM\n");
    scanf("%i", &opcao);
    switch (opcao) {
    case 1:{ //ABRE O ARQUIVO clientes.dat E ESCREVE OS DADOS
        fpclientes = fopen(CADCLIENTE, "ab");
            if (fpclientes == NULL) {
            printf("Erro na abertura ou arquivo ainda não existe!!\n");
            system("pause");
            return;
            }
        fwrite(&cliente,sizeof(cliente),1,fpclientes);
        //MOSTRA O RESULTADO
        printf("\n");
        printf("\nCódigo: %i ", cliente.codigo);
        printf("\nNome: %s ", cliente.nome);
        printf("\nEndereço: %s ", cliente.endereco);
        printf("\nTelefone: %s ", cliente.telefone);
        printf("\nE-mail: %s ", cliente.email);
        printf("\nData de Nascimento: %s ", cliente.dataDeNascimento);
        printf("\n\n");
        //FECHA O ARQUIVO clientes.dat
        fclose(fpclientes);
        break;
    }//Fim case 1

    case 0 :
        printf("Cadastro Cancelado! ");
        //retornar para o main.
        break;
    default:
        printf("\nOpção inválida! ");
    }//fim switch
    system("pause");
}
//FimCadastrarClientes

//LISTA COMPLETA DE CLIENTES
void listarClientes(){
    setlocale(LC_ALL,"Portuguese");
    FILE *fpclientes;
    struct Cliente cliente;

    fpclientes = fopen(CADCLIENTE, "rb");
    if (fpclientes == NULL) {
        printf("Erro na abertura ou arquivo ainda não existe!!\n");
        system("pause");
            return;
    }
    system("cls");
    printf("\n\tCADASTRO DE CLIENTES\n");
    while (fread(&cliente,sizeof(cliente),1,fpclientes) == 1) {

        printf("\nCódigo: %i", cliente.codigo);
        printf(" - Cliente: %s", cliente.nome);
        printf("\nTelefone: %s - ", cliente.telefone);
        printf("Endereço: %s ", cliente.endereco);
        printf("E-mail: %s \n", cliente.email);
    }
    fclose(fpclientes);
    system("pause");
}
//Fim lista completa de clientes.

//(5)2.1-CONSULTAR CLIENTE POR PARTE INICIAL DO NOME
void consultarCliente(){
    system("cls");
    setlocale(LC_ALL,"Portuguese");
    FILE *fpclientes;
    struct Cliente cliente;
    char comparaNome[20];
    int encontrado=0;

    printf("\nPESQUISA CLIENTE POR NOME:");
    printf("\nDigite o PRIMEIRO nome do cliente:\t");
    fflush(stdin);
    gets(comparaNome);

    fpclientes = fopen(CADCLIENTE, "rb");
        if (fpclientes == NULL) {
            printf("Erro na abertura ou arquivo ainda não existe!!\n");
            system("pause");
            return;
        }//verificação
    while(fread(&cliente,sizeof(cliente),1,fpclientes) == 1) {
        if(strncmp(comparaNome,cliente.nome,strlen(comparaNome)) == 0){
            encontrado++;
            printf("\nCódigo: %i", cliente.codigo);
            printf(" - Cliente: %s", cliente.nome);
            printf("\nTelefone: %s - ", cliente.telefone);
            printf("Endereço: %s ", cliente.endereco);
            printf("E-mail: %s \n", cliente.email);
        }
    }//fim while
    if (!encontrado){
        printf("\t****");
        printf("\n\tNome NÃO cadastrado!\n");
        printf("\t****");
    }
    fclose(fpclientes);
    system("pause");
}
//FimConsultarClientePorParteInicialDoNome

//(6)3-VENDER
//FimVender

//(7)3.1-RELATAR TODOS OS PRODUTOS COMPRADOS POR UM CLIENTE
//FimRelatarTodosOsProdutosCompradosPorUmCliente

//(8)3.2-RELATAR TODOS OS CLIENTES QUE COMPRARAM UM PRODUTO
//FimClientesQueCompraramUmProduto

//(9)3.3-RELATAR PRODUTOS VENDIDOS EM UM DETERMINADO MES
//FimRelatarProdutosVendidosPorUmMes

//(10)3.4-RELATAR PRODUTO CAMPEÃO DE VENDAS EM UM ANO
//FimRelatarProdutoCampeaoDeVendasEmUmAno

void main() {
    setlocale(LC_ALL,"Portuguese");

    int opcao;

    do {
        system("cls");
        printf("\nLOJA DE ELETROELETRONICOS\n");
        printf("\n 0 - Sair. ");
        printf("\n 1 - Cadastrar Produtos.");
        printf("\n      11 - Consultar Produtos por DESCRIÇÃO.");
        printf("\n      12 - Relatório de Produtos com o Estoque Mínimo.");
        printf("\n      13 - Listar Cadastro.");
        printf("\n 2 - Cadastrar Clientes.");
        printf("\n      21 - Consultar cliente pelo PRIMEIRO NOME.");
        printf("\n      22 - Listar Clientes.");
        printf("\n");
        scanf("%i",&opcao);
        switch (opcao) {
        case 0:
            printf("\n\nSaída do programa com sucesso!\n\n");
            break;
        case 1:
            CadastrarProdutos();
            break;
        case 11:
            ConsultarProdutoDescricao();
            break;
        case 12:
            estoqueMinimo();
            break;
        case 13:
            listarCadastro();
            break;
        case 2:
            CadastrarClientes();
            break;
        case 21:
            consultarCliente();
            break;
        case 22:
            listarClientes();
            break;

        default :
            printf("Opção Inválida!");
        }//FimSwitch
    } while (opcao != 0);
    system("pause");
}
