int main() {
    funcao fs[] = {criar, deletar, listar, salvar, carregar, exportarTarefasTexto};

    Tarefa tarefas[TOTAL];
    int pos = 0;

    ERROS erro = fs[4](tarefas, &pos);
    if (erro != OK)
        pos = 0;

    int opcao;
    do {
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("4 - Exportar tarefas para um arquivo binario\n");
        printf("5 - Carregar tarefas de um arquivo binario\n");
        printf("6 - Exportar tarefas para um arquivo de texto\n"); // Nova opção
        printf("0 - Sair\n");
        printf("Escolha uma opcao: \n");

        scanf("%d", &opcao);

        if (opcao < 0 || opcao > 6) {
            printf("Opcao invalida\n");
        } else if (opcao > 0) {
            fs[opcao - 1](tarefas, &pos);
        } else {
            printf("Sair...\n");
        }

    } while (opcao != 0);

    fs[3](tarefas, &pos);

    return 0;
}
