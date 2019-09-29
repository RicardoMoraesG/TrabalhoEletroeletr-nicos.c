#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define CADPRODUTO "produtos.dat"
#define CADCLIENTE "clientes.dat"
#define CADVENDA "vendas.dat"
/* GRUPO
Jonathan Elias
Lucas Eduardo
Ricardo de Moraes Gon�alves
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

};
int codigoProduto() {
    //Automatiza a atribui��o de c�digos para o cadastro de produtos
    FILE *fpprodutos;
    struct Produto produto;
    int codigo;
    int resposta;
    int incrementaCodigo=0;

    fpprodutos = fopen(CADPRODUTO, "rb");
    if (fpprodutos == NULL) {

        printf("� o primeiro cadastro?! \n");
        printf("1 - Sim!\n");
        printf("0 - N�o!\n");
        scanf("%i", &resposta);
        if(resposta) {
            codigo = 1;
            incrementaCodigo = 1;
        } else {
            printf("Erro na abertura ou arquivo ainda n�o existe!\n");
            system("pause");
        }
    } else {
        while (fread(&produto,sizeof(produto),1,fpprodutos) == 1) {
            incrementaCodigo++;//conta quantos cadastros de produto existem.
        }//Fim while.
        fclose(fpprodutos);

        codigo = incrementaCodigo+1; //acrescenta o novo na contagem.
    }
    return codigo;
}
int codigoCliente() {
    //Automatiza a atribui��o de c�digos para o cadastro de produtos
    FILE *fpcliente;
    struct Cliente cliente;
    int codigo;
    int resposta;
    int incrementaCodigo=0;

    fpcliente = fopen(CADCLIENTE, "rb");
    if (fpcliente == NULL) {

        printf("� o primeiro cadastro?! \n");
        printf("1 - Sim!\n");
        printf("0 - N�o!\n");
        scanf("%i", &resposta);
        if(resposta) {
            codigo = 1;
            incrementaCodigo = 1;
        } else {
            printf("Erro na abertura ou arquivo ainda n�o existe!!\n");
            system("pause");
        }
    } else {
        while (fread(&cliente,sizeof(cliente),1,fpcliente) == 1) {
            incrementaCodigo++;//conta quantos clientes cadastrados existem.
        }//Fim while.
        fclose(fpcliente);

        codigo = incrementaCodigo+1; //acrescenta o novo na contagem.
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
    printf("\nDescri��o do Produto: ");
    fflush(stdin);
    gets(produto.descricao);

    printf("\nQuantidade em Estoque: ");
    fflush(stdin);
    scanf("%i", &produto.estoque);

    printf("\nQuantidade M�nima para o estoque: ");
    fflush(stdin);
    scanf("%i", &produto.estoqueMinimo);

    printf("\nPre�o: ");
    fflush(stdin);
    scanf("%f", &produto.preco);

    //receber o c�digo via teclado:
    /*
    printf("\nC�digo Produto: ");
    fflush(stdin);
    scanf("%i", &produto.codigo);
    */

    //Automatiza a atribui��o de c�digo:
    produto.codigo = codigoProduto();

    printf("\nConfirma Cadastro?");
    printf("\n0 - N�O");
    printf("\n1 - SIM\n");
    scanf("%i", &opcao);
    switch (opcao) {
    case 1 : { //Gravar produto
        fpprodutos = fopen(CADPRODUTO, "ab");
        if (fpprodutos == NULL) {
            printf("Erro na abertura ou arquivo ainda n�o existe!\n");
            system("pause");
            return;
        }
        fwrite(&produto,sizeof(produto),1,fpprodutos);

        printf("\n");
        printf("\nC�digo: %7i ", produto.codigo);
        printf("\n%s ", produto.descricao);
        printf("\nQuantidade em Estoque: %7i ", produto.estoque);
        printf("\nEstoque M�nimo: %7i ", produto.estoqueMinimo);
        printf("\nPre�o R$ %.2f ", produto.preco);
        printf("\n\n");
        fclose(fpprodutos);
        break;
    }//Fim case 1

    case 0 :
        printf("Cadastro Cancelado! ");
        //retornar para o main.
        break;
    default:
        printf("\nOp��o inv�lida! ");
    }
    system("pause");
}
//FimCadastrarProdutos

//(2)1.1-CONSULTAR PRODUTO POR PALAVRA CHAVE NA DESCRI��O DO PRODUTO
void ConsultarProdutoDescricao() {
    setlocale(LC_ALL,"Portuguese");

    FILE *fpprodutos;
    struct Produto produto;
    char pesquisaProduto[20];
    int achou=0;

    system("cls");
    printf("\nPesquisar produto por descri��o: \t");
    fflush(stdin);
    gets(pesquisaProduto);

    fpprodutos = fopen(CADPRODUTO, "rb");
    if (fpprodutos == NULL) {
        printf("Erro na abertura ou arquivo ainda n�o existe!!\n");
        system("pause");
            return;
    }
    while (fread(&produto,sizeof(produto),1,fpprodutos) == 1) {
            //Se a palavra pesquisada faz parte da descri��o do produto
        if(strstr(produto.descricao, pesquisaProduto) != NULL){
            achou = 1;
            printf("\n%s, %i, Estoque %i, Estoque m�nimo %i, R$ %.2f", produto.descricao, produto.codigo, produto.estoque, produto.estoqueMinimo, produto.preco);
        }//FimIf.

    }//FimWhile
    fclose(fpprodutos);

    if(!achou) {
        printf("\nProduto N�O encontrado! \n");
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
        printf("Erro na abertura ou arquivo ainda n�o existe!!\n");
        system("pause");
            return;
    }
    system("cls");
    printf("CADASTRO DE PRODUTOS\n");
    printf("\nC�digo - Descri��o - Est. - E.Min. - Pre�o\n");
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
//(3)1.2-RELATAR PRODUTOS COM ESTOQUE M�NIMO
void estoqueMinimo() {
    FILE *fpprodutos;
    struct Produto produto;
    fpprodutos = fopen(CADPRODUTO, "rb");
    if (fpprodutos == NULL) {
        printf("Erro na abertura ou arquivo ainda n�o existe!!\n");
        system("pause");
            return;
    }
    system("cls");
    printf("\t\tPRODUTOS COM ESTOQUE M�NIMO\n\n");
    printf("C�digo \t\t Descri��o \tEstoque m�nimo  Estoque Atual");
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
//RECEBE DADOS DO CLIENTE (TECLADO)
    system("cls");
    printf("\nCADASTRO DE CLIENTES\n");
    printf("\nNome: ");
    fflush(stdin);
    gets(cliente.nome);

    printf("\nEndere�o: ");
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
     //Automatiza a atribui��o de c�digo:
    cliente.codigo = codigoCliente();
    printf("\nConfirma Cadastro?");
    printf("\n0 - N�O");
    printf("\n1 - SIM\n");
    scanf("%i", &opcao);
    switch (opcao) {
    case 1:{ //ABRE O ARQUIVO clientes.dat E ESCREVE OS DADOS
        fpclientes = fopen(CADCLIENTE, "ab");
            if (fpclientes == NULL) {
            printf("Erro na abertura ou arquivo ainda n�o existe!!\n");
            system("pause");
            return;
            }
        fwrite(&cliente,sizeof(cliente),1,fpclientes);
        //MOSTRA O RESULTADO
        printf("\n");
        printf("\nC�digo: %i ", cliente.codigo);
        printf("\nNome: %s ", cliente.nome);
        printf("\nEndere�o: %s ", cliente.endereco);
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
        printf("\nOp��o inv�lida! ");
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
        printf("Erro na abertura ou arquivo ainda n�o existe!!\n");
        system("pause");
            return;
    }
    system("cls");
    printf("\n\tCADASTRO DE CLIENTES\n");
    while (fread(&cliente,sizeof(cliente),1,fpclientes) == 1) {

        printf("\nC�digo: %i", cliente.codigo);
        printf(" - Cliente: %s", cliente.nome);
        printf("\nTelefone: %s - ", cliente.telefone);
        printf("Endere�o: %s ", cliente.endereco);
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
            printf("Erro na abertura ou arquivo ainda n�o existe!!\n");
            system("pause");
            return;
        }//verifica��o
    while(fread(&cliente,sizeof(cliente),1,fpclientes) == 1) {
        if(strncmp(comparaNome,cliente.nome,strlen(comparaNome)) == 0){
            encontrado++;
            printf("\nNome: %s", cliente.nome);
            printf("\tC�digo: %i", cliente.codigo);
            printf("\nTelefone: %s - ", cliente.telefone);
            printf("Endere�o: %s ", cliente.endereco);
            printf("E-mail: %s \n", cliente.email);
        }
    }//fim while
    if (!encontrado){
        printf("\t****");
        printf("\n\tNome N�O cadastrado!\n");
        printf("\t****");
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
    int opc;
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
        printf("\n cliente nao localizado!");
        return;
    }
    fclose(fpclientes);
    //se achou:
    printf("\n Confirma Cliente? \n\t 1 - SIM \n\t 0 - N�O\n\t");
    fflush(stdin); scanf("%i",&opc);
    if (opc == 0){
        printf("\nOperancao Cancelada");
        return;
    }
    //se confirmar cliente:
    printf("\nDigite o codigo da venda");
    fflush(stdin); scanf("%i",&codvendas);
    //DIGITAR PRODUTOS
    do {
        printf("\nDigite o c�digo do produto: ");
        fflush(stdin); scanf("%i",&codprod);
        //abre o arquivo de produtos
        fpprodutos = fopen(CADPRODUTO,"rb");
            if (fpprodutos == NULL){printf("Erro na abertura ou arquivo ainda n�o existe!!\n");}
        achou = 0;
        while ((!achou)&&(fread(&produto,sizeof(produto),1,fpprodutos) == 1)){
            if (produto.codigo == codprod){
                printf("\nDescricao: %s",produto.descricao);
                    strcpy(venda.descricao_prod, produto.descricao);
                printf("\n Preco : %.2f",produto.preco);
                    venda.preco_prod = produto.preco;
                achou = 1;
            }//fim if
        }//fim while
        fclose(fpprodutos);//fecha arquivo de produtos
        if (!achou){
            printf("\nProduto nao localizado");
        }
        else{
            printf("\tquantidade : ");
            fflush(stdin); scanf("%i",&venda.qtde);
            printf("\nDigite o desconto : ");
            fflush(stdin); scanf("%f",&venda.desc);
            venda.cod_venda = codvendas;
            venda.cod_cliente = codcli;
            venda.cod_prod = codprod;
            //gravar a venda
            printf("\n Confirmar a venda do produto (S/N)?");
            fflush(stdin); scanf("%c",&opc);
            if((opc=='s')||(opc=='S')){
                fpvendas = fopen(CADVENDA,"ab");
                fwrite(&venda,sizeof(venda),1,fpvendas);
                fclose(fpvendas);
                printf("\nItem vendido com sucesso");
            }
            else{
                printf("\nItem nao confirmado");
            }
        }
        //Mais vendas

        printf("\nDeseja incluir mais vendas? \n\t 1 - SIM \n\t 0 - N�O\n\t");
        fflush(stdin); scanf("%i",&continuar);
        /*//if ((opc=='s')||(opc=='S')){//**TESTEANDO SE O ERRO EST� AQUI**
            continuar = 1;
        }
        else{
            continuar = 0;
        }*/
    }while (continuar);

//Finalizar vendas
printf("\n venda ");
printf("\n Pedido numero : %i",codvendas);
printf("\n cliente %i - %s",cliente.codigo,cliente.nome);
printf("\nCodigo Descri��o                  Preco  Qtde  Desconto Total");
fpvendas = fopen(CADVENDA,"rb");
total = 0;
while (fread(&venda,sizeof(venda),1,fpvendas)==1){
    if (venda.cod_venda == codvendas){
        fpprodutos = fopen(CADPRODUTO,"rb");
        achou = 0;
        while ((!achou)&&(fread(&produto,sizeof(produto),1,fpprodutos)==1)){
            if (produto.codigo == venda.cod_prod){
                achou = 1;
            }
        }
        fclose(fpprodutos);
        subtotal = (produto.preco * venda.qtde) - venda.desc;
        total = total + subtotal;
        printf("\n%6i %-25s %5.2f %4i %8.2f %.2f",venda.cod_prod,produto.descricao,produto.preco,venda.qtde,venda.desc,subtotal);
    }
}
printf("\n\n TOTAL = %.2f\n",total);
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
    printf("\nC�digo do cliente: ");
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
            printf("Venda Produto\t\t\t\t  C�d\tPre�o R$\tDesconto\tUn.\n");//titulo da listagem do cliente
            while ( (fread(&vendas, sizeof(vendas), 1, fpvenda) == 1) ) {
                if (vendas.cod_cliente == pesquisa_cliente) {//l� cada registro de cliente
                    printf("%4i   %-30s \t %4i\tR$ %5.2f\tR$ %5.2f\t%3i \n", vendas.cod_venda, vendas.descricao_prod, vendas.cod_prod, vendas.preco_prod,vendas.desc,vendas.qtde);
                }
            }
        }
        else
            printf("\n\tN�o foram registradas vendas para este cliente\n");
        fclose(fpvenda);//fecha o arquivo de vendas
    //fecha os arquivos de venda, cliente e produto
    printf("\n");
    system("pause");
}
//FimRelatarTodosOsProdutosCompradosPorUmCliente

//(8)3.2-RELATAR TODOS OS CLIENTES QUE COMPRARAM UM PRODUTO
//FimClientesQueCompraramUmProduto

//(9)3.3-RELATAR PRODUTOS VENDIDOS EM UM DETERMINADO MES

//FimRelatarProdutosVendidosPorUmMes

//(10)3.4-RELATAR PRODUTO CAMPE�O DE VENDAS EM UM ANO
//FimRelatarProdutoCampeaoDeVendasEmUmAno

void main() {
    setlocale(LC_ALL,"Portuguese");

    int opcao;

    do {
        system("cls");
        printf("\n\tLOJA DE ELETROELETRONICOS 'GOBEU' \n");
        printf("\n 0 - Sair. ");
        printf("\n 1 - Cadastrar Produtos.");
        printf("\n      11 - Consultar Produtos por DESCRI��O.");
        printf("\n      12 - Relat�rio de Produtos com o Estoque M�nimo.");
        printf("\n      13 - Listar Cadastro.");
        printf("\n 2 - Cadastrar Clientes.");
        printf("\n      21 - Consultar cliente pelo PRIMEIRO NOME.");
        printf("\n      22 - Listar Clientes.");
        printf("\n 4 -  Realizar venda ");
        printf("\n      41 - Relat�rio de vendas por cliente.");
        printf("\n");
        scanf("%i",&opcao);
        switch (opcao) {
        case 0:
            printf("\n\nSa�da do programa com sucesso!\n\n");
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
        case 4 :
            rvendas();
            break;
        case 41:
            vendasPorCliente();
            break;


        default :
            printf("Op��o Inv�lida!\n");
            system("pause");
        }//FimSwitch
    } while (opcao != 0);
    system("pause");
}
