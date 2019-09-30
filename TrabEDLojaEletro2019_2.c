#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#define CADPRODUTO "produtos.dat"
#define CADCLIENTE "clientes.dat"
#define CADVENDA "vendas.dat"
/* GRUPO
Jonathan Elias
Lucas Eduardo
Ricardo de Moraes Gonçalves
*/
struct Produto {
    int codigo;
    char descricao[50];
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
struct reg_vendas{
    int cod_venda;
    int cod_cliente;
    int cod_prod;
    int qtde;
    float desc;
    float preco_prod;
    char descricao_prod[50];
    int diaVenda, mesVenda, anoVenda;
};
int gera_codigo(char* arquivo) {
    //atribui um código automático em sequência
    int codigo;
    int sequenciaCodigo = 0;
    FILE* fp = fopen(arquivo, "rb");
    if (fp == NULL) {
        printf("(Arquivo vazio)\n");
        codigo = 0;
        sequenciaCodigo+1;
    }
    if (strncmp(CADPRODUTO, arquivo, strlen(CADPRODUTO)) == 0 ){
        struct Produto estrutura;
        //conta quantos cadastrados existem.
        while (fread(&estrutura,sizeof(estrutura),1,fp) == 1) {
            sequenciaCodigo++;
        }
    }
    if (strncmp( CADCLIENTE, arquivo, strlen(CADCLIENTE)) == 0){
        struct Cliente estrutura;
        while (fread(&estrutura,sizeof(estrutura),1,fp) == 1) {
            sequenciaCodigo++;
        }
    }
    if (strncmp( CADVENDA, arquivo, strlen(CADVENDA)) == 0);{
        struct reg_vendas estrutura;
        while (fread(&estrutura,sizeof(estrutura),1,fp) == 1) {
            sequenciaCodigo++;
        }
    }
    fclose(fp);
    codigo = sequenciaCodigo+1; //acrescenta o novo na contagem.
    return codigo;
    system("pause");
}
//(1)1-CADASTRAR PRODUTOS
void CadastrarProdutos() {
    setlocale(LC_ALL,"Portuguese");

    FILE *fpprodutos;
    struct Produto produto;
    int opcao;
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
    //automatiza a atribuição de código (em sequencia)
    produto.codigo = gera_codigo(CADPRODUTO);
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
            return;
    }
    while (fread(&produto,sizeof(produto),1,fpprodutos) == 1) {
            //Se a palavra pesquisada faz parte da descrição do produto
        if(strstr(produto.descricao, pesquisaProduto) != NULL){
            achou = 1;
            printf("\n%s, %i, Estoque %i, Estoque mínimo %i, R$ %.2f", produto.descricao, produto.codigo, produto.estoque, produto.estoqueMinimo, produto.preco);
        }

    }
    fclose(fpprodutos);

    if(!achou) {
        printf("\nProduto NÃO encontrado! \n");
    }
    printf("\n");
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
               "\n%4i - %-20s - %3i un. \t- %3i un. \t- R$ %3.2f",
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
    printf("\t\tPRODUTOS COM ESTOQUE MÍNIMO\n\n");
    printf("Código \t\t Descrição \tEstoque mínimo  Estoque Atual");
    while (fread(&produto,sizeof(produto),1,fpprodutos) == 1) {
        if(produto.estoque <= produto.estoqueMinimo) {

            printf("\n%4i  \t%20s  \t\t%4i  \t\t%4i",
                   produto.codigo, produto.descricao, produto.estoqueMinimo, produto.estoque );
        }
    }
    printf("\n");
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
    //automatiza a atribuição de código (em sequencia)
    cliente.codigo = gera_codigo(CADCLIENTE);
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
    }
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
            printf("\nNome: %s", cliente.nome);
            printf("\tCódigo: %i", cliente.codigo);
            printf("\nTelefone: %s - ", cliente.telefone);
            printf("Endereço: %s ", cliente.endereco);
            printf("E-mail: %s \n", cliente.email);
        }
    }//fim while
    if (!encontrado){
        printf("\n\n\tNome NÃO cadastrado!\n\n");
    }
    fclose(fpclientes);
    printf("\n");
    system("pause");
}
//FimConsultarClientePorParteInicialDoNome
//(6)3-VENDER
void rvendas(){
    FILE *fpprodutos, *fpclientes, *fpvendas;
    struct Produto produto;
    struct Cliente cliente;
    struct reg_vendas venda;
    int codprod, codcli, codvendas, achou, continuar;
    char opc;
    float total,subtotal;
    //LOCALIZAR CLIENTE
    printf("\nDigite o codigo do Cliente: ");
    fflush(stdin); scanf("%i",&codcli);
    fpclientes = fopen(CADCLIENTE,"rb");
    achou = 0;
    while ((!achou)&&(fread(&cliente,sizeof(cliente),1,fpclientes)==1)){
        if (cliente.codigo == codcli){
            printf("\nNome: %s",cliente.nome);
            achou = 1;
        }
    }
    if(!achou){
        printf("\n cliente não localizado!");
        system("pause");
        return;
    }
    fclose(fpclientes);
    //se achou:
    printf("\n Confirma Cliente? (S/N)");
    fflush(stdin); scanf("%c",&opc);
    if ((opc=='s')||(opc=='S')){
        continuar = 1;
    }
    else{
        continuar = 0;
        printf("\nOperanção Cancelada\n");
        system("pause");
        return;
    }
    //DIGITAR PRODUTOS
    do {
        printf("\nDigite o código do produto: ");
        fflush(stdin); scanf("%i",&codprod);
        //abre o arquivo de produtos
        fpprodutos = fopen(CADPRODUTO,"rb");
            if (fpprodutos == NULL){printf("Erro na abertura ou arquivo ainda não existe!!\n");system("pause");}
            achou = 0;
            //copia os dados do arquivo de produtos
            while ((!achou)&&(fread(&produto,sizeof(produto),1,fpprodutos) == 1)){
                if (produto.codigo == codprod){
                    printf("\nDescricao: %s",produto.descricao);
                        strcpy(venda.descricao_prod, produto.descricao);
                    printf("\n Preco : %.2f",produto.preco);
                        venda.preco_prod = produto.preco;
                    achou = 1;
                }
            }
        fclose(fpprodutos);//fecha arquivo de produtos
        if (!achou){
            printf("\nProduto nao localizado");
        }
        else{
            printf("\tquantidade : ");
            fflush(stdin); scanf("%i",&venda.qtde);
            printf("\nDigite o desconto R$: ");
            fflush(stdin); scanf("%f",&venda.desc);
            //gravar a venda
            continuar = 0;
            printf("\n Confirmar a venda do produto (S/N)?\t");
            fflush(stdin); scanf("%c",&opc);
            if ((opc=='s')||(opc=='S')){
                continuar = 1;
                //abre o arquivo de vendas para gravar
                fpvendas = fopen(CADVENDA,"ab");
                //copia os codigos para o arquivo de vendas
                venda.cod_cliente = codcli;
                venda.cod_prod = codprod;
                venda.cod_venda = gera_codigo(CADVENDA);//automatiza a atribuição de código (em sequência)
                codvendas = venda.cod_venda;
                /*recebe uma data aleatória para testar os arquivos*/
                venda.anoVenda = rand()% 3 + 2017;
                venda.mesVenda = rand()% 12;
                if(venda.mesVenda == 0) {
                    venda.mesVenda++;
                }
                venda.diaVenda = rand()% 31;
                if(venda.diaVenda == 0) {
                    venda.diaVenda++;
                }
                /**/
                //registra e fecha o arquivo de vendas para gravar
                fwrite(&venda,sizeof(venda),1,fpvendas);
                fclose(fpvendas);
                printf("\nItem vendido com sucesso");
            }
            else{
                continuar = 0;
                printf("\nItem nao confirmado");
            }
        }
        //Mais vendas?
        continuar = 0;
        printf("\nDeseja incluir mais vendas? (S/N)?\t");
        fflush(stdin); scanf("%c",&opc);
        if ((opc=='s')||(opc=='S')){
            continuar = 1;
        }
        else{
            continuar = 0;
        }
    }while (continuar);
    //Finalizar vendas
    fpvendas = fopen(CADVENDA,"rb");
    printf("\n \tVENDA ");
    printf("\nPedido número: %i",venda.cod_venda);
    printf("\nCliente %i - %s",cliente.codigo, cliente.nome);

    //mostar os itens vendidos para o cliente
    printf("\nCódigo Descrição                  Preco  Qtde  Desconto Total");
    total = 0;
    while ( fread(&venda,sizeof(venda),1,fpvendas) == 1 ) {                         //le cada registro de venda
        if (venda.cod_venda == codvendas) {                                         //se o codigo do registro é o pesquisado:
            fpprodutos = fopen(CADPRODUTO,"rb");                                    //abre o cadastro de produtos
            achou = 0;                                                              //zera o 'achou'
            while ((!achou)&&(fread(&produto,sizeof(produto),1,fpprodutos) == 1) ){//enquanto (nao 'achou') e (ler um registro de produto)
                if (produto.codigo == venda.cod_prod){//se o (codigo do produto) for o do registro de venda
                    subtotal = (produto.preco * venda.qtde) - venda.desc;           //preco * quantidade - desconto.
                    total = total + subtotal;
                    printf("\n%6i %-25s %5.2f %4i %8.2f %.2f",venda.cod_prod,produto.descricao,produto.preco,venda.qtde,venda.desc,subtotal);achou = 1;
                }
            }
        fclose(fpprodutos);
        }
    }
    printf("\n\n TOTAL = %.2f\n",total);

    fclose(fpvendas);
    printf("\n");
    system("pause");
}
//FimVender

//(7)3.1-RELATAR TODOS OS PRODUTOS COMPRADOS POR UM CLIENTE
void vendasPorCliente(){
    FILE *fpcliente;
    FILE *fpvenda;
    FILE *fpproduto;
    struct Cliente cliente;
    struct reg_vendas vendas;
    struct Produto produto;
    int pesquisa_cliente, achou = 0;

    system("cls");
    printf("\nCONSULTA DE PRODUTOS COMPRADOS POR UM CLIENTE");
    printf("\nCódigo do cliente: ");
    fflush(stdin);
    scanf("%i", &pesquisa_cliente);
    //abre os arquivos de venda
        fpvenda = fopen(CADVENDA, "rb");
        while ((!achou) && (fread(&vendas, sizeof(vendas), 1, fpvenda) == 1) ){
            if (vendas.cod_cliente == pesquisa_cliente){
                achou = 1;
            }
        }
        if (achou){
            printf("Venda Produto\t\t\t\t  Cód\tPreço R$\tDesconto\tUn.\n");//titulo da listagem do cliente
            while ( (fread(&vendas, sizeof(vendas), 1, fpvenda) == 1) ) {
                if (vendas.cod_cliente == pesquisa_cliente) {//lê cada registro de cliente
                    printf("%4i   %-30s \t %4i\tR$ %5.2f\tR$ %5.2f\t%3i \n", vendas.cod_venda, vendas.descricao_prod, vendas.cod_prod, vendas.preco_prod,vendas.desc,vendas.qtde);
                }
            }
        }
        else
            printf("\n\tNão foram registradas vendas para este cliente\n");
        fclose(fpvenda);//fecha o arquivo de vendas
    printf("\n");
    system("pause");
}
//FimRelatarTodosOsProdutosCompradosPorUmCliente

//(8)3.2-RELATAR TODOS OS CLIENTES QUE COMPRARAM UM PRODUTO
void clientesPorProduto(){

    FILE *fpvenda;
    FILE *fpcliente;
    struct reg_vendas vendas;
    struct Cliente cliente;
    int pesquisa_produto, achou = 0;
    char nome_cliente[30];
    int dataVenda;

    system("cls");
    printf("\nCONSULTA DE CLIENTES QUE COMPRARAM UM PRODUTO");
    printf("\nCódigo do produto: ");
    fflush(stdin);
    scanf("%i", &pesquisa_produto);
    //abre os arquivos de venda
        fpvenda = fopen(CADVENDA, "rb");
        while ((!achou) && (fread(&vendas, sizeof(vendas), 1, fpvenda) == 1) ){
            if (vendas.cod_prod == pesquisa_produto){
                achou = 1;
            }
        }
        if (achou){
            printf("Nome\t\t\t  Venda\tPreço R$\tDesconto\tUn.\n");//titulo da listagem do produto
            while ( (fread(&vendas, sizeof(vendas), 1, fpvenda) == 1) ) {
                if (vendas.cod_prod == pesquisa_produto) {//lê cada registro do produto
                    fpcliente = fopen(CADCLIENTE,"rb");
                    //mostrar o nome do cliente
                    while ( (fread(&cliente, sizeof(cliente), 1, fpcliente) == 1) ){
                        if (vendas.cod_cliente == cliente.codigo){
                            strcpy(nome_cliente,cliente.nome);
                        }
                    }//
                printf("%-20s \t %4i\tR$ %5.2f\tR$ %5.2f\t%3i \n", nome_cliente,vendas.cod_venda, vendas.preco_prod,vendas.desc,vendas.qtde);
                fclose(fpcliente);
                }
            }
        }
        else{
            printf("\n\tNão foram registradas vendas para este produto\n");}

        fclose(fpvenda);//fecha o arquivo de vendas
    printf("\n");
    system("pause");
}
//FimClientesQueCompraramUmProduto

//(9)3.3-RELATAR PRODUTOS VENDIDOS EM UM DETERMINADO MES
void vendaMensal(){
    FILE *fpvenda;
    struct reg_vendas vendas;
    int pesquisa_mes, achou = 0;
    system("cls");
    printf("\nRELATÓRIO DE VENDAS MENSAIS");
    printf("\nMês para consulta:\t ");
    fflush(stdin); scanf("%i", &pesquisa_mes);
    //abre os arquivos de venda
        fpvenda = fopen(CADVENDA, "rb");
        while ((!achou) && (fread(&vendas, sizeof(vendas), 1, fpvenda) == 1) ){
            if (vendas.mesVenda == pesquisa_mes){
                achou = 1;
            }
        }
        if (achou){
            printf("Venda Produto\t\t\t\t  Cód\tPreço R$\tDesconto\tUn.\n");//titulo da listagem do cliente
            while ( (fread(&vendas, sizeof(vendas), 1, fpvenda) == 1) ) {
                if (vendas.mesVenda == pesquisa_mes) {//lê cada registro de cliente
                    printf("%4i   %-30s \t %4i\tR$ %5.2f\tR$ %5.2f\t%3i \n", vendas.cod_venda, vendas.descricao_prod, vendas.cod_prod, vendas.preco_prod,vendas.desc,vendas.qtde);
                }
            }
        }
        else
            printf("\n\tNão foram registradas vendas neste mês\n");
        fclose(fpvenda);//fecha o arquivo de vendas
    printf("\n");
    system("pause");
}

//FimRelatarProdutosVendidosPorUmMes

//(10)3.4-RELATAR PRODUTO CAMPEÃO DE VENDAS EM UM ANO

//FimRelatarProdutoCampeaoDeVendasEmUmAno

void main() {
    setlocale(LC_ALL,"Portuguese");

    int opcao;

    do {
        system("cls");
        printf("\n\tLOJA DE ELETROELETRONICOS 'GOBEU' \n");
        printf("\n 0 - Sair. ");
        printf("\n 1 - Cadastrar Produtos.");
        printf("\n      11 - Consultar Produtos por DESCRIÇÃO.");
        printf("\n      12 - Relatório de Produtos com o Estoque Mínimo.");
        printf("\n      13 - Listar Cadastro.");
        printf("\n 2 - Cadastrar Clientes.");
        printf("\n      21 - Consultar cliente pelo PRIMEIRO NOME.");
        printf("\n      22 - Listar Clientes.");
        printf("\n 3 -  Realizar venda ");
        printf("\n      31 - Relatório de vendas por cliente.");
        printf("\n      32 - Relatório de clientes que compraram um produto.");
        printf("\n      33 - Relatório vendas mensal.");
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
        case 3 :
            rvendas();
            break;
        case 31:
            vendasPorCliente();
            break;
        case 32:
            clientesPorProduto();
            break;
        case 33:
            vendaMensal();
            break;
        default :
            printf("Opção Inválida!\n");
            system("pause");
        }
    } while (opcao != 0);
    system("pause");
}
