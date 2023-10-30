#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//define a quantidade maxima do array
#define QTD_CLIENTES 65

int numClientes = 0; // Variável para rastrear o número de clientes (defina corretamente)
typedef struct {
    char nome[100];
    char cpf[20];
    char tipooo[2];
    float saldo;
    char senha[50];
    char apagacliente[30];
} Cliente;
//clientes armazenando o valor de QTD_CLIENTES
Cliente clientes[QTD_CLIENTES];
int numClientes = 0;
//funcao para salvar clientes em um arq binario
// aqui abro a void para o novo cliente, basicamente a void printa oque ira ser feito, pede para que a pessoa digite o cpf
//abrindo o arquivo para adicionar os dados digitados,a funcao le o arquivo todo e confere se a opcao selecionada no tipo de conta foi commum ou plus, assim podendo me permitir trabalhar em cima do codigo e aplicar as taxas dadas pelo professor por fim, a funcao printa todos os dados inseridos pelo cliente e informa-o que sua conta foi cadastrada
void novo() {
    printf("Novo cliente");//coloca na tela oque deve ser feito
    char cpf[20];//pede para o cliente informar o cpf
    printf("Seu CPF: ");//coloca na tela oque deve ser feito
    scanf("%s", cpf);//le o cpf
    char filename[20];//formata e armazena
    sprintf(filename, "%s.bin", cpf);//print no arquivo
    FILE *arquivosnomes; //arquivo com as informacoes
    arquivosnomes = fopen(filename, "r");//abre o arquivo para leitura
    if (!arquivosnomes) { //optei por nao usar o = NULL 
        char nome[50], senha[50], tipooo[2];//as informacoes em seus numeros combinados
        float valor;
        printf("Seu nome: ");//coloca na tela oque deve ser feito
        scanf("%s", nome);//le
        printf("Coloque sua senha: ");//coloca na tela oque deve ser feito
        scanf("%s", senha);//le
        printf("escolha um tipo de conta: 1-Comum 2-Plus. ");//coloca na tela oque deve ser feito
        scanf("%s", tipooo);//le
        printf("Valor inicial da conta: ");//coloca na tela oque deve ser feito
        scanf("%f", &valor);//le
        char tipo[6];
        if (strcmp(tipooo, "1") == 0) {
            strcpy(tipo, "comum");//caso a escolha for 1 tipo commum
        }
        else {//caso contrario tipo plus
            strcpy(tipo, "plus");
        }
        arquivosnomes = fopen(filename, "w");//abre o arquivo para escrita
        fprintf(arquivosnomes, "Nome: %s Seu CPF: %s Senha: %s Tipo: %s", nome, cpf, senha, tipo);//coloca os dados
        fprintf(arquivosnomes, "Tarifa:     0.00   Saldo: %8.2f", valor); //coloca valores
        fclose(arquivosnomes);// fecha o arquivo
      printf("Conta cadastrada.\n");//informa
      menu();//abre o menu novamente
    }
}
//a funcao tem como objetivo apagar uma conta ja existente no "arquivonomes", arquivo onde sao inseridas todas as informações digitadas pelo usuário, a funcao printa todas as informações necessárias, pedindo cpf e senha da conta, logo em seguida confere se ambos os dados batem com o arquivo onde as informações estao guardadas, caso as informações nao corresponderem o arquivo informa o erro e te leva ao menu novamente, caso esteje tudo certo, o codigo exclui do arquivo e informa a acao para o cliente.
void apagacliente() {
    char cpf[20];
    printf("Seu CPF: ");//coloca na tela oque deve ser feito
    scanf("%s", cpf);
    char apagacliente[30];
    sprintf(apagacliente, "%s.bin", cpf);
    FILE *arquivonomes;
    arquivonomes = fopen(apagacliente, "r");
    if (arquivonomes == NULL) {
        printf("Erro, tente novamente \n");//informa
        menu();
    }
    else {
        fclose(arquivonomes);
        char senha[20];
        printf("Sua Senha: ");//pede informacao
        scanf("%s", senha);
        FILE *arquivo = fopen(apagacliente, "r");//abre o arquivo para leitura e para conferir
        char choice[2][20];
        int i = 0;
        while (fgets(choice[i], 20, arquivo)) { //confere
            choice[i][strlen(choice[i]) - 1] = '\0';
            i++;
        }
        fclose(arquivo);
        if (strcmp(senha, choice[2]) == 0) { //confere
            remove(apagacliente);
            printf("Conta apagada com sucesso\n");
            menu();
        }
        else {
            printf("Erro, tente novamente\n");
            menu();
        }
    }
}



void debitoapossenha(Cliente *cliente, double valor) {
    // Aplicar taxa apropriada com base no tipo de conta
    if (strcmp(cliente->tipo_conta, "comum") == 0) {
        // Conta "Comum" cobra 5% de taxa
        valor += valor * 0.05;
    } else if (strcmp(cliente->tipo_conta, "plus") == 0) {
        // Conta "Plus" cobra 3% de taxa
        valor += valor * 0.03;
    }

    // Verificar saldo suficiente para a ação desejada
    if (cliente->saldo - valor < -1000.0 && strcmp(cliente->tipo_conta, "comum") == 0) {
        printf("Saldo insuficiente para realizar a ação. :(\n");
    } else if (cliente->saldo - valor < -5000.0 && strcmp(cliente->tipo_conta, "plus") == 0) {
        printf("Saldo insuficiente para realizar a ação. :(\n");
    } else {
        // Realizar a ação (por exemplo, débito)
        cliente->saldo -= valor;

        salvarClientes();
        printf("Ação realizada com sucesso! =)\n");
    }
}

void debitocomsenha() {
    char cpf[10];
    char senha[20];
    double valor;

    // Inputs
    printf("CPF: ");
    scanf("%s", cpf);

    if (!validarCPF(cpf)) {
        printf("CPF inválido. :(\n");
        return;
    }

    int clienteIndex = -1;

    // Encontre o cliente com base no CPF
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            clienteIndex = i;
            break;
        }
    }

    // Verifique se o cliente foi encontrado
    if (clienteIndex == -1) {
        printf("Cliente não encontrado. :(\n");
        return;
    }

    // Inputs
    printf("Senha: ");
    scanf("%s", senha);

    // Verificar a senha
    if (strcmp(clientes[clienteIndex].senha, senha) == 0) {
        // A senha está correta, realizar a ação desejada (por exemplo, um débito)
        printf("Valor a ser debitado: ");
        debito(Cliente *cliente, double valor);
    } else {
        printf("Senha incorreta. :(\n");
    }
}



void extrato() {
    printf("Voce selecionou extrato!\n");
    char cpf[10];
    char senha[20];
    //imputs
    printf("CPF: ");
    scanf("%s", cpf);

    printf("Senha: ");
    scanf("%s", senha);
    //comparando strings e retorna 0 se as duas forem iguais
    int x = -1;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            x = i;
            break;
        }
    }
    //se a condicao do laco for nao for cumprido ele executa a linha de       baixo e nao muda o valor de x
    if (x == -1) {
        printf("Cliente nao encontrado ou senha incorreta.'-'\n");
        return;
    }

    printf("Extrato:\n");
    printf("Saldo atual: R$ %.2f =) \n,", clientes[x].saldo);
}
// a funcao pede e confere o cpf e senha como as outras, a funcao tambem pede o cpf da conta que deseja transferir o vlaor, apos isso funcao informa a tranferencia com o valor o saldo novo e a taifa ja implementada no codigo 
void transferencia() {
    printf("Voce selecionou tranferencia!\n");
    char cpfOrigem[10], senhaOrigem[20], cpfDestino[10];
    float valor;
  //imputs
    printf("CPF (Origem): ");
    scanf("%s", cpfOrigem);

    printf("Senha (Origem): ");
    scanf("%s", senhaOrigem);

    printf("CPF (Destino): ");
    scanf("%s", cpfDestino);
    //comparando strings e retorna 0 se as duas forem iguais
    int i, xOrigem = -1, xDestino = -1;
    for (i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfOrigem) == 0 && strcmp(clientes[i].senha, senhaOrigem) == 0) {
            xOrigem = i;
        } else if (strcmp(clientes[i].cpf, cpfDestino) == 0) {
            xDestino = i;
        }
    }

    if (xOrigem == -1 || xDestino == -1) {
        printf("Cliente(s) nao encontrado(s) ou senha incorreta.'-'\n");
        return;
    }
    //digita o valor e se estiver sem saldo retorna
    printf("Valor: ");
    scanf("%f", &valor);

    if (strcmp(clientes[xOrigem].tipoConta, "comum") == 0) {
        if (valor > clientes[xOrigem].saldo + 1000) {
            printf("Saldo insuficiente. =( \n");
            return;
        }
        //aplicando a taxa de 5% de débito 
        clientes[xOrigem].saldo -= valor * 0.05;  
    } else if (strcmp(clientes[xOrigem].tipoConta, "plus") == 0) {
        if (valor > clientes[xOrigem].saldo + 5000) {
            printf("Saldo insuficiente. =( \n");
            return;
        }
        //aplicando a taxa de 3% de débito
        clientes[xOrigem].saldo -= valor * 0.03;  
    } else {
        printf("Tipo de conta invalido.'-'\n");
        return;
    }

    clientes[xDestino].saldo += valor;

    salvarClientes();

    printf("Transferencia realizada com sucesso.=)\n");
}

// Função para listar todos os clientes cadastrados
void listarClientes() {
    FILE *arquivo;
    char nome[50];

    // Abre o arquivo para leitura
    arquivo = fopen("arquivosnomes", "r");

    printf("Lista de Clientes:\n");

    // Lê e exibe os nomes dos clientes enquanto não atingir o fim do arquivo
    while (fgets(nome, sizeof(nome), arquivo) != NULL) {
        printf("%s", nome);
    }
    fclose(arquivo);
}

void sair() {
    exit(0);
}


