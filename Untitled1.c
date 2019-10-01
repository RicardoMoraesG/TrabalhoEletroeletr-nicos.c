#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define CADPRODUTOS "produtos.dat"
#define CADCLIENTES "clientes.dat"
#define CADVENDAS "vendas.dat"

 struct reg_produtos{
    int codigo;
    char descricao[255];
    float preco;
    int quantidade;
    int quantidade_minima;
 };

 struct reg_clientes{
    int codigo;
    char nome[50];
    char endereco[255];
    char telefone[17]; // padrão telefone: (XXX) XXXXX-XXXX
    char email[255];
    char data_nascimento[12];
 };

 struct reg_vendas{
    int codigo_venda;
    int codigo_produto;
    int codigo_cliente;
    int quantidade_adquirida;
    char data_venda[12];
    float desconto;
 };

 void pegarDataAtual(char data[11]){
    struct tm *local;
    time_t t;

    t = time(NULL);
    local = localtime(&t);
    sprintf(data, "%d/%d/%d", local->tm_mday, local->tm_mon + 1, local->tm_year+1900);

    }// fim pegarData()

 void cadastrarProduto(){
    FILE *fpprodutos;
    struct reg_produtos produto;
    char opc;

    system("cls");

 /** Pegar os dados do produto **/
    printf("Digite o código do produto: ");
    fflush(stdin); scanf("%d", &produto.codigo);

 if(produto.codigo <= 0){
    printf("\nEste código é inválido!\n");
    system("pause");
    return;
    }

    printf("Digite a descrição: ");
    fflush(stdin); gets(produto.descricao);

    printf("Digite o preço do produto: ");
    fflush(stdin); scanf("%f", &produto.preco);

    printf("Digite a quantidade em estoque do produto: ");
    fflush(stdin); scanf("%d", &produto.quantidade);

    if(produto.quantidade < 0){
    printf("\nA quantidade do produto em estoque não pode ser menor que zero!\n");
    system("pause");
    return;
    }

    printf("Digite o estoque mínimo do produto: ");
    fflush(stdin); scanf("%d", &produto.quantidade_minima);

    if(produto.quantidade_minima < 0){
    printf("\nA quantidade mínima em estoque do produto não pode ser menor que zero!\n");
    system("pause");
    return;
    }

    printf("FINALIZAR (S/N) \n ");
    fflush(stdin); scanf("%c", &opc);

 if((opc == 'S') || (opc == 's')){
    fpprodutos = fopen(CADPRODUTOS, "ab");
    fwrite(&produto, sizeof(produto), 1, fpprodutos);
    fclose(fpprodutos);

    printf("\nProduto cadastrado com sucesso!\n");
    system("pause");
    system("cls");
 }else
    {
        printf("\nOperação cancelada!\n");
        system("pause");
        system("cls");
    }

 } // fim cadastrarProduto()


 void cadastrarCliente(){
    FILE *fpclientes;
    struct reg_clientes cliente;
    char opc;

    system("cls");

 /** Pegar os dados do cliente **/
    printf("Digite o código do cliente: ");
    fflush(stdin);
    scanf("%d", &cliente.codigo);

    if(cliente.codigo <= 0){
    printf("\nEste código é inválido!\n");
    system("pause");
    return;
    }

    printf("Digite o nome do cliente: ");
    fflush(stdin); gets(cliente.nome);

    printf("Digite o endereço do cliente: ");
    fflush(stdin);
    gets(cliente.endereco);

    printf("Digite o telefone do cliente: ");
    fflush(stdin); gets(cliente.telefone);

    printf("Digite a data de nascimento do cliente: ");
    fflush(stdin); gets(cliente.data_nascimento);

    printf("Digite o email do cliente: ");
    fflush(stdin); gets(cliente.email);

    printf("G r a v a r ? ( S / n ) \n-> ");
    fflush(stdin); scanf("%c", &opc);

 if((opc == 'S') || (opc == 's')){
    fpclientes = fopen(CADCLIENTES, "ab");
    fwrite(&cliente, sizeof(cliente), 1, fpclientes);
    fclose(fpclientes);

    printf("\nCliente cadastrado com sucesso!\n");
    system("pause");
    system("cls");
 }
 else{
    printf("\nOperação cancelada!\n");
    system("pause");
    system("cls");
    }

 } // fim cadastrarCliente()

 void consultarPalavraChave(){
    FILE *fpprodutos;
    struct reg_produtos produto;
    char palavra_chave[255];
    int achou = 0;

    system("cls");

    printf("Digite uma palavra-chave para buscar: ");
    fflush(stdin);
    gets(palavra_chave);
    strlwr(palavra_chave);

    fpprodutos = fopen(CADPRODUTOS, "rb");
    while(fread(&produto, sizeof(produto), 1, fpprodutos) == 1){
        char string_temporaria[255];
        strcpy(string_temporaria, produto.descricao);
        strlwr(string_temporaria);
    if(strstr(string_temporaria, palavra_chave) != NULL){
        if(!achou){
            printf("\n\t\tProdutos encontrados: ");
            printf("\n COD | DESCRIÇÃO | PREÇO | ESTOQUE | ESTOQUE MIN |\n");
        }
    if(strlen(produto.descricao) >= 9){
        printf(" %d | %-.12s... | R$%-7.2f | %-2d | %d |\n",produto.codigo, produto.descricao, produto.preco, produto.quantidade,produto.quantidade_minima);
    }
    else{
        printf(" %d | %-9s | R$%-7.2f | %-2d | %d |\n",produto.codigo, produto.descricao, produto.preco, produto.quantidade,produto.quantidade_minima);
    }
    achou++;
    }
 }
 //fechar o arquivo
 fclose(fpprodutos);

    if(!achou){
        printf("\n Não encontramos nada com essa palavra chave. . .\n\n");
 }

    printf("\n");
    system("pause");
    system("cls");

 } // fim consultarPalavraChave()

 void consultarPorInicioDoNome(){
    FILE *fpclientes;
    struct reg_clientes cliente;
    char palavra_inicial[255];
    int achou = 0;

    system("cls");

    printf("Digite o começo do nome do(a) cliente: ");
    fflush(stdin);
    gets(palavra_inicial);
    strlwr(palavra_inicial);

    fpclientes = fopen(CADCLIENTES, "rb");

    while(fread(&cliente, sizeof(cliente), 1, fpclientes) == 1){
        char string_temporaria[255];
        strcpy(string_temporaria, cliente.nome);
        strlwr(string_temporaria);
    if(strncmp(string_temporaria, palavra_inicial, strlen(palavra_inicial)) == 0){
        if(!achou){
            printf("\n\t\t\t\tClientes encontrados: ");
            printf("\n COD | NOME | ENDEREÇO | TELEFONE| EMAIL | DATA DE NASC |\n");
        }

    printf(" %d | %-.9s... | %-.11s... | %-.13s... | %-.18s... | %s |\n",cliente.codigo, cliente.nome, cliente.endereco, cliente.telefone, cliente.email,cliente.data_nascimento);
        achou++;
    }
 }

    if(!achou){
        printf("\n Não encontramos nada com essa(s) palavra(s) chave(s).\n\n");
    }

    fclose(fpclientes);

    printf("\n");
    system("pause");
    system("cls");
} // fim consultarPorInicioDoNome()

 void realizarVenda(){
    FILE *fpvendas;
    FILE *fpprodutos;
    FILE *fpprodutosnew;
    FILE *fpclientes;
    struct reg_vendas venda;
    struct reg_produtos produto;
    struct reg_clientes cliente;
    int estoque, achou;
    char opc, continuar;
    float preco_produto, total;

    system("cls");
    printf("Digite o código da venda: ");
    fflush(stdin); scanf("%d", &venda.codigo_venda);
    printf("Digite o código do cliente: ");
    fflush(stdin); scanf("%d", &venda.codigo_cliente);
    achou = 0;

    fpclientes = fopen(CADCLIENTES, "rb");
    while(fread(&cliente, sizeof(cliente), 1, fpclientes) == 1){
        if(venda.codigo_cliente == cliente.codigo)
    {
    printf("\n COD | NOME | ENDEREÇO | TELEFONE | EMAIL | DATA DE NASC |\n");
    printf(" %d | %-.9s... | %-.11s... | %-.13s... | %-.18s... | %s |\n",cliente.codigo, cliente.nome, cliente.endereco, cliente.telefone, cliente.email,
cliente.data_nascimento);
    achou++;
    }
 }
    fclose(fpclientes);

    if(!achou) {
        printf("\nEste cliente não está cadastrado em nossa loja =(\n");
        system("pause");
    return;
    }
    else{
        printf("\nConfirma cliente? (S/n) -> ");
    fflush(stdin); scanf("%c", &opc);
    if(opc != 'S' && opc != 's')
    {
    printf("\nOperação cancelada!\n");
    system("pause");
    return;
    }
 }
    do{
        printf("\nDigite o código do produto: ");
        fflush(stdin); scanf("%d", &venda.codigo_produto);

        achou = 0;
        fpprodutos = fopen(CADPRODUTOS, "rb");
    while(fread(&produto, sizeof(produto), 1, fpprodutos) == 1){
        if(venda.codigo_produto == produto.codigo){
        printf("\n COD | DESCRIÇÃO | PREÇO | ESTOQUE | ESTOQUE MIN |\n");
    if(strlen(produto.descricao) >= 9){
        printf(" %d | %-.12s... | R$%-7.2f | %-2d | %d |\n",produto.codigo, produto.descricao, produto.preco, produto.quantidade,produto.quantidade_minima);
 }
    else {
        printf(" %d | %-9s | R$%-7.2f | %-2d | %d |\n",produto.codigo, produto.descricao, produto.preco, produto.quantidade,produto.quantidade_minima);
    }
    preco_produto = produto.preco;
    achou++;
    }
 }
 fclose(fpprodutos);

    if(!achou){
        printf("\nEsse produto não existe na nossa loja! =(\n");
        system("pause");
    return;
    }
    else{
        printf("\nConfirma produto? (S/n) -> ");
        fflush(stdin); scanf("%c", &opc);

    if(opc != 'S' && opc != 's'){
        printf("\nOperação cancelada!\n");
        system("pause");
    return;
    }
 }

    printf("\nDigite a quantidade adquirida: ");
    fflush(stdin); scanf("%d", &venda.quantidade_adquirida);

    fpprodutos = fopen(CADPRODUTOS, "rb");
    while(fread(&produto, sizeof(produto), 1, fpprodutos) == 1){
        if(venda.codigo_produto == produto.codigo){
            estoque = produto.quantidade;
        if(venda.quantidade_adquirida > estoque){
            printf("\nQuantidade indisponível!\n");
            system("pause");
        return;
        }
    }
 }
 fclose(fpprodutos);

    printf("\nDigite a porcentagem de desconto a ser aplicada no produto: ");
    fflush(stdin); scanf("%f", &venda.desconto);

    pegarDataAtual(venda.data_venda);
    total = (preco_produto * venda.quantidade_adquirida) - ((preco_produto *venda.quantidade_adquirida) * venda.desconto / 100);

    printf("\nValor total da compra: RS%.2f\n", total);
    printf("G r a v a r ? ( S / n ) \n -> ");
    fflush(stdin); scanf("%c", &opc);

    if((opc == 'S') || (opc == 's')){
        fpvendas = fopen(CADVENDAS, "ab");
        fwrite(&venda, sizeof(venda), 1, fpvendas);
        fclose(fpvendas);
        printf("\nVenda realizada com sucesso!\n");
    }
    else{
        printf("\nOperação cancelada!\n");
        system("pause");
    return;
 }

 /** Alterando estoque **/
    fpprodutos = fopen(CADPRODUTOS, "rb");
    fpprodutosnew = fopen("produtos.new", "wb");

    estoque -= venda.quantidade_adquirida;
    while(fread(&produto, sizeof(produto), 1, fpprodutos) == 1){
        if(venda.codigo_produto == produto.codigo){
            produto.quantidade = estoque;
        }

    fwrite(&produto, sizeof(produto), 1, fpprodutosnew);
 }

    printf("Estoque alterado com sucesso.\n");
    fclose(fpprodutos);
    fclose(fpprodutosnew);

    system("del produtos.dat");

    system("ren produtos.new produtos.dat");

    printf("\nDeseja realizar outra compra? ( S / n ) -> ");
    fflush(stdin); scanf("%c", &continuar);

    if(continuar == 's' || continuar == 'S'){
        system("cls");
    }
 }
    while(continuar == 's' || continuar == 'S');

        printf("\nOperação finzalizada!\n");
        system("pause");

 } // fim realizarVenda()

void rel_EstMin(){
    FILE *fpprodutos;
    struct reg_produtos produto;
    int cont = 0;

    system("cls");

    fpprodutos = fopen(CADPRODUTOS, "rb");

    printf("\n\n");
    printf(" COD -- DESCRIÇÃO ------ PREÇO -------- ESTOQUE ------- ESTOQUE MIN  \n\n");
    while(fread(&produto, sizeof(produto), 1, fpprodutos) == 1){
        if(produto.quantidade <= produto.quantidade_minima){
            printf(" %d   %9s         R$%-7.2f           %-2d   %15d \n\n", produto.codigo, produto.descricao,produto.preco, produto.quantidade, produto.quantidade_minima);
            cont++;
        }
    }

    if(!cont){
        printf("\n\tNenhum produto está abaixo do estoque mínimo...\n\n");
    }
    fclose(fpprodutos);

    system("pause");

 } // fim RELATORIO DE ESTOQUE MINIMO

void rel_ProdporCLie(){
    FILE *fpvendas;
    FILE *fpprodutos;
    struct reg_vendas venda;
    struct reg_produtos produto;
    int codigo_cliente, achou =0, cod_produto_anterior = 0;
    float subtotal, total = 0;

    system("cls");

    printf("Digite o código do cliente que deseja buscar: ");
    fflush(stdin); scanf("%d", &codigo_cliente);

    fpprodutos = fopen(CADPRODUTOS, "rb");

    while(fread(&produto, sizeof(produto), 1, fpprodutos) == 1){
        fpvendas = fopen(CADVENDAS, "rb");
    while(fread(&venda, sizeof(venda), 1, fpvendas) == 1){
        if(codigo_cliente == venda.codigo_cliente){
            if(produto.codigo == venda.codigo_produto){
    if(!achou){
        printf("\n\tProdutos comprados pelo(a) cliente: \n");
        printf(" COD | DESCRIÇÃO | PREÇO | ESTOQUE | ESTOQUE MIN | QTDE |\n");
    }

    if(produto.codigo != cod_produto_anterior){
        if(strlen(produto.descricao) >= 9){
            printf(" %d | %-.6s... | R$%-7.2f | %-2d | %d | %-4d |\n", produto.codigo, produto.descricao, produto.preco, produto.quantidade, produto.quantidade_minima, venda.quantidade_adquirida);
    }
    else {
        printf(" %d | %-9s | R$%-7.2f | %-2d | %d | %-4d |\n", produto.codigo, produto.descricao, produto.preco, produto.quantidade, produto.quantidade_minima, venda.quantidade_adquirida);
    }
 }

        cod_produto_anterior = produto.codigo;
        achou++;
        }
    }
 }
    subtotal = (produto.preco * venda.quantidade_adquirida) - ((produto.preco * venda.quantidade_adquirida) * venda.desconto / 100);
    total += subtotal;
    fclose(fpvendas);
 }
    fclose(fpprodutos);

    if(achou){
        printf("\nEste(a) cliente gastou R$%.2f em produtos da nossa loja. . .\n", total);
    }
    else {
        printf("\nNão encontramos nenhum cliente com esse código em nossa loja. . .\n");
    }
    system("pause");
 } // fim gerarPorProdutoPorCliente()

void rel_CliporProd(){
    FILE *fpvendas;
    FILE *fpclientes;
    struct reg_vendas venda;
    struct reg_clientes cliente;
    int codigo_produto, achou = 0, cod_cliente_anterior = 0;


    system("cls");

    printf("Digite o código do produto que deseja buscar: ");
    fflush(stdin); scanf("%d", &codigo_produto);

    fpclientes = fopen(CADCLIENTES, "rb");

    while(fread(&cliente, sizeof(cliente), 1, fpclientes) == 1){
        fpvendas = fopen(CADVENDAS, "rb");
    while(fread(&venda, sizeof(venda), 1, fpvendas) == 1){
        if(codigo_produto == venda.codigo_produto){
            if(venda.codigo_cliente == cliente.codigo){
    if(!achou){
        printf("\n\t\t\tClientes que compraram este produto: \n");
        printf(" COD | NOME | ENDEREÇO | TELEFONE | EMAIL | DATA DE NASC |\n");
    }

    if(cliente.codigo != cod_cliente_anterior){
        printf(" %d | %-.9s... | %-.11s... | %-.13s... | %-.18s... | %s |\n", cliente.codigo, cliente.nome, cliente.endereco, cliente.telefone,
        cliente.email, cliente.data_nascimento);
    }
        cod_cliente_anterior = cliente.codigo;
        achou++;
        }
    }
 }
 fclose(fpvendas);
 }

 fclose(fpclientes);

    if(!achou) {
        printf("\nNão encontramos esse produto em nossa loja. . .\n\n");
    }
    printf("\n");
    system("pause");

 } // fim gerarRelatorioPorClientePorProduto()

void rel_prodMes(){
    FILE *fpvendas;
    FILE *fpprodutos;
    struct reg_vendas venda;
    struct reg_produtos produto;
    char mes_ano[7];
    int achou = 0;
    float subtotal, total = 0;

    system("cls");

 /** Ler o mês e o ano digitado pelo usuário **/
    printf("Digite o mês e o ano que deseja ver as compras: \n(Fomato M/AAAA se M < 10 ou MM/AAAA se M > 10)\n-> ");
    fflush(stdin); gets(mes_ano);

    if(strlen(mes_ano) != 6 || strlen(mes_ano) != 9){
        printf("\nDigite uma data válida. . .\n");
        printf(" ex: 9/2019 ou 10/2019\n\n");
        system("pause");
    return;
    }

    fpvendas = fopen(CADVENDAS, "rb");

    while(fread(&venda, sizeof(venda), 1, fpvendas) == 1){
    int len = strlen(venda.data_venda);
    char *mes_ano_ate_setembro = &venda.data_venda[len-6]; // retorna M/AAAA (o único ou o ultimo digito do mês)
    char *mes_ano_depois_setembro = &venda.data_venda[len-7]; // retorna MM/AAAA ou/M/AAAA
    if((strcmp(mes_ano, mes_ano_ate_setembro) == 0) || (strcmp(mes_ano, mes_ano_depois_setembro) == 0)){
        fpprodutos = fopen(CADPRODUTOS, "rb");
    while(fread(&produto, sizeof(produto), 1, fpprodutos) == 1){
        if(venda.codigo_produto == produto.codigo){
    if(!achou){
        printf("\n\t\t Produtos vendidos em %s\n", mes_ano);
        printf(" COD | DESCRIÇÃO | PREÇO | ESTOQUE | ESTOQUE MIN | VALOR DA COMPRA |\n");
    }

    subtotal = (produto.preco * venda.quantidade_adquirida) - ((produto.preco * venda.quantidade_adquirida) * venda.desconto / 100);
    if(strlen(produto.descricao) >= 9){
        printf(" %d | %-.6s... | R$%-7.2f | %-2d | %d | R$%-6.2f |\n", produto.codigo, produto.descricao, produto.preco, produto.quantidade, produto.quantidade_minima, subtotal);
    }
    else {
        printf(" %d | %-9s | R$%-7.2f | %-2d | %d | R$%-6.2f |\n", produto.codigo, produto.descricao, produto.preco, produto.quantidade,
        produto.quantidade_minima, subtotal);
    }

        achou++;
    }
 }
 fclose(fpprodutos);
 }
 total += subtotal;
 }

    if(!achou){
        printf("\n\t Não achamos nenhuma compra nesse mês . . . =(\n\n");
        system("pause");
    }
    else {
        printf("\t O total vendido no mês %s é de R$%.2f\n\n", mes_ano, total);
    }

    fclose(fpvendas);
    fclose(fpprodutos);
    system("pause");
 } // fim gerarRelatorioPorProdutosPorMes()

 void rel_ProdWin() {
    FILE *fpvendas;
    FILE *fpprodutos;
    struct reg_vendas venda;
    struct reg_produtos produto;
    struct reg_produtos produto_campeao;
    char ano[5];
    int maior_quantidade = 0, achou = 0;
    float total;

    system("cls");
    printf("Digite um ano para listar: ");
    fflush(stdin); gets(ano);

    if(strlen(ano) != 4){ //verifica o ano
        printf("Ano invalido , digite novamente . . .\n");
        system("pause");
    return;
    }

    fpprodutos = fopen(CADPRODUTOS, "rb");

    while(fread(&produto, sizeof(produto), 1, fpprodutos) == 1){
        fpvendas = fopen(CADVENDAS, "rb");
        int qtde = 0;
    while(fread(&venda, sizeof(venda), 1, fpvendas) == 1){
        int len = strlen(venda.data_venda);
        char *ano_venda = &venda.data_venda[len-4];

    if(strcmp(ano, ano_venda) == 0){
        if(produto.codigo == venda.codigo_produto){
            qtde += venda.quantidade_adquirida;
            achou++;
        }
    }
 }
 fclose(fpvendas);

    if(!achou){
        printf("\n\tVENDAS NAO REGISTRADAS. . .\n");
        system("pause");
        fclose(fpprodutos);
    return;
    }
    if(qtde > maior_quantidade){
        maior_quantidade = qtde;
        produto_campeao = produto;
    }
 }

 fclose(fpprodutos);

    total = produto_campeao.preco * maior_quantidade;

    printf("\n\t\t*** PRODUTO CAMPEÃO ***\n");
    printf(" COD -- DESCRIÇÃO ------ PREÇO -------- ESTOQUE ------- ESTOQUE MIN  \n\n");

    if(strlen(produto_campeao.descricao) >= 9){
        printf(" %d | %-.6s... | R$%-7.2f | %-2d | %d |\n", produto_campeao.codigo, produto_campeao.descricao, produto_campeao.preco,
        produto_campeao.quantidade, produto_campeao.quantidade_minima);
    }
    else {
        printf(" %d   %9s         R$%-7.2f           %-2d   %15d \n\n", produto_campeao.codigo, produto_campeao.descricao, produto_campeao.preco,
        produto_campeao.quantidade, produto_campeao.quantidade_minima);
    }

    printf("\nUnidades vendidas %d TOTAL R$%.2f\n\n", maior_quantidade, total);
    printf("\n\n");
    system("pause");

 } // fim buscarProdutoCampeao()



 int main(void)
 {
 int opcao;

 setlocale(LC_ALL, "portuguese");

 do{

    system("cls");
    printf("\n");
    printf(" ***************** Loja de Eletroeletrônicos *****************\n");
    printf("\n\n");
    printf(" >>> 1) Cadastro de produtos \n");
    printf("      11 - Consulta por palavra chave \n");
    printf("      12 - Relatório - Estoque mínimo \n");
    printf("\n");
    printf(" >>> 2) Cadastro de clientes \n");
    printf("      22 - Consulta pelo início do nome \n");
    printf("\n");
    printf(" >>> 3) Gerar venda \n\n");
    printf("-------------------------RELATORIOS---------------------------\n\n");
    printf("  4) Relatório - Produtos por cliente \n");
    printf("  5) Relatório - Clientes por produto \n");
    printf("  6) Relatório - Produtos em um mês \n");
    printf("  7) Produto campeão de vendas no ano \n");
    printf(" --------------------------------------------------------------\n\n");
    printf("  0) Sair \n");
    printf("\n");
    printf(" -------------------------------------------------------------\n");
    printf("\n\n");
    printf(" >>> Opção -> ");
    fflush(stdin); scanf("%d", &opcao);

    switch(opcao){
    case 1:
        cadastrarProduto();
    break;
    case 11:
        consultarPalavraChave();
    break;
    case 12:
        rel_EstMin();
    break;
    case 2:
        cadastrarCliente();
    break;
    case 22:
        consultarPorInicioDoNome();
    break;
    case 3:
        realizarVenda();
    break;
    case 4:
        rel_ProdporCLie();
    break;
    case 5:
        rel_CliporProd();
    break;
    case 6:
        rel_prodMes();
    break;
    case 7:
        rel_ProdWin();
    break;
    case 0:
        printf(" Saindo . . .");
    break;
    default:
        printf("\nDigite uma opção válida . . . \n");
        system("pause");
    break;
    }
 }
    while(opcao != 0);
 }
