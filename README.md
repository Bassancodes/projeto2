# README

## Descrição:
o projeto possibilita o usuario criar tarefas definir propriedades, resumindo ele faz o usuario ter a liberdade de exercer funcoes listadas a baixo em uma lista de tarefas.

## Funções:

1. **`criar`:**
   Esta função permite ao usuário criar uma nova tarefa inserindo prioridade, categoria e descrição. Ela verifica se a prioridade está dentro do intervalo válido de 1 a 10. As strings de categoria e descrição de entrada são ajustadas para remover caracteres de nova linha no final.

2. **`deletar`:**
   Deleta uma tarefa com base na posição fornecida pelo usuário. Primeiro verifica se existem tarefas para deletar e se a posição especificada é válida. Em seguida, remove quaisquer caracteres de nova linha das strings de categoria e descrição antes de deslocar as tarefas para preencher o espaço deletado.

3. **`listar`:**
   Lista todas as tarefas existentes. Primeiro verifica se há tarefas a serem listadas e depois itera pelas tarefas, imprimindo sua posição, prioridade, categoria e descrição. Os caracteres de nova linha no final das strings de categoria e descrição são removidos antes da impressão.

4. **`salvar`:**
   Salva as tarefas em um arquivo binário chamado "tarefas.bin". Remove quaisquer caracteres de nova linha das strings de categoria e descrição antes de escrever as tarefas no arquivo. Também escreve o número de tarefas (`pos`) no arquivo.

5. **`carregar`:**
   Carrega as tarefas do arquivo binário "tarefas.bin". Primeiro lê as tarefas do arquivo e depois remove quaisquer caracteres de nova linha das strings de categoria e descrição. Também lê o número de tarefas (`pos`) do arquivo.

6. **`clearBuffer`:**
   Esta função limpa o buffer de entrada para evitar que caracteres indesejados afetem a entrada do usuário.

## Uso:
1. Compile o programa usando um compilador C.
2. Execute o arquivo binário compilado.
3. Siga as instruções na tela para criar, deletar, listar, salvar e carregar tarefas.

## Observação:
Certifique-se de que o arquivo de cabeçalho `tarefas.h` esteja presente no mesmo diretório que o arquivo de código-fonte. Este arquivo de cabeçalho provavelmente contém definições usadas por este programa, como estruturas e códigos de erro.
