#include <stdio.h>
#include "tarefas.h"

int main() {
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos = 0; // Inicializa pos para evitar comportamento indefinido

    ERROS erro = fs[4](tarefas, &pos);
    if(erro != OK)
        pos = 0;

    int opcao;
    do {
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: \n");

        scanf("%d", &opcao);

        if(opcao < 0 || opcao > 3) { // Corrigido o limite da condição
            printf("Opcao invalida\n");
        } else if(opcao > 0) { // Corrigida a verificação da opcao
            fs[opcao - 1](tarefas, &pos); // Corrigida a indexação do array de funções
        } else {
            printf("Sair...\n");
        }

    } while(opcao != 0); // Corrigida a condição do loop

    fs[3](tarefas, &pos);

    return 0; // Adicionada a declaração de retorno para main
}
