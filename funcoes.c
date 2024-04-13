#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS exportarTarefasTexto(Tarefa tarefas[], int *pos) {
    char nome_arquivo[100];
    printf("Digite o nome do arquivo de texto para exportar as tarefas: ");
    scanf("%99s", nome_arquivo);

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return ABRIR;
    }

    for (int i = 0; i < *pos; i++) {
        fprintf(arquivo, "Prioridade: %d\n", tarefas[i].prioridade);
        fprintf(arquivo, "Categoria: %s\n", tarefas[i].categoria);
        fprintf(arquivo, "Descricao: %s\n", tarefas[i].descricao);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    printf("Tarefas exportadas com sucesso para o arquivo %s.\n", nome_arquivo);

    return OK;
}
ERROS exportarTarefas(Tarefa tarefas[], int *pos) {
    char nome_arquivo[100];
    printf("Digite o nome do arquivo de texto para exportar as tarefas: ");
    scanf("%99s", nome_arquivo);

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return ABRIR;
    }

    for (int i = 0; i < *pos; i++) {
        fprintf(arquivo, "Prioridade: %d\n", tarefas[i].prioridade);
        fprintf(arquivo, "Categoria: %s\n", tarefas[i].categoria);
        fprintf(arquivo, "Descricao: %s\n", tarefas[i].descricao);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    printf("Tarefas exportadas com sucesso para o arquivo %s.\n", nome_arquivo);

    return OK;
}
ERROS criar(Tarefa tarefas[], int *pos) {
    if (*pos >= TOTAL)
        return MAX_TAREFA;

    printf("Entre com a prioridade (de 1 a 10): \n");
    scanf("%d", &tarefas[*pos].prioridade);
    clearBuffer();

    // Verifica se a prioridade está dentro do intervalo permitido
    if (tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10) {
        printf("Prioridade invalida. Deve ser um valor entre 1 e 10.\n");
        return ERRO_PRIORIDADE_INVALIDA;
    }

    printf("Entre com a categoria: \n");
    fgets(tarefas[*pos].categoria, TAMANHO_CATEGORIA, stdin);
    tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0';

    printf("Entre com a descricao: \n");
    fgets(tarefas[*pos].descricao, TAMANHO_DESCRICAO, stdin);
    tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0';

    *pos = *pos + 1;

    return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos){
    // teste se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // verifica se a tarefa escolhida existe
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: \n");
    scanf("%d", &pos_deletar);
    pos_deletar--; // garantir posicao certa no array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;
=
    tarefas[pos_deletar].categoria[strcspn(tarefas[pos_deletar].categoria, "\n")] = '\0';  
    tarefas[pos_deletar].descricao[strcspn(tarefas[pos_deletar].descricao, "\n")] = '\0';

    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos){
    if(*pos == 0)
        return SEM_TAREFAS;

    char categoria_desejada[TAMANHO_CATEGORIA];
    printf("Digite a categoria que deseja listar (deixe vazio para exibir todas as tarefas): ");
    fgets(categoria_desejada, TAMANHO_CATEGORIA, stdin);
    categoria_desejada[strcspn(categoria_desejada, "\n")] = '\0'; // Remove a quebra de linha

    int encontradas = 0; // Variável para contar o número de tarefas encontradas

    for(int i = 0; i < *pos; i++){
        // Remove a quebra de linha das categorias e descrições
        tarefas[i].categoria[strcspn(tarefas[i].categoria, "\n")] = '\0';
        tarefas[i].descricao[strcspn(tarefas[i].descricao, "\n")] = '\0';

        // Verifica se a categoria desejada é igual à categoria da tarefa ou se a categoria está vazia
        if (categoria_desejada[0] == '\0' || strcmp(tarefas[i].categoria, categoria_desejada) == 0) {
            encontradas++;

            printf("Pos: %d\t\n", encontradas);
            printf("Prioridade: %d\t\n", tarefas[i].prioridade);
            printf("Categoria: %s\t\n", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
        }
    }

    if (encontradas == 0) {
        printf("Nenhuma tarefa encontrada para a categoria especificada.\n");
    }

    return OK;
}



ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;
    for(int i = 0; i < *pos; i++) {
        tarefas[i].categoria[strcspn(tarefas[i].categoria, "\n")] = '\0';
        tarefas[i].descricao[strcspn(tarefas[i].descricao, "\n")] = '\0';
    }


    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR;

    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return LER;
    for(int i = 0; i < *pos; i++) {
        tarefas[i].categoria[strcspn(tarefas[i].categoria, "\n")] = '\0';
        tarefas[i].descricao[strcspn(tarefas[i].descricao, "\n")] = '\0';
    }

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER;

    if(fclose(f))
        return FECHAR;

    return OK;

}
