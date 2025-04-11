/**
 * Sistema de Gerenciamento de Livros - Aplicativo CRUD em C
 * 
 * Este programa implementa um sistema de gerenciamento de livros baseado em console com operações CRUD.
 * Funcionalidades incluem:
 * - Adicionar novos livros
 * - Listar todos os livros
 * - Pesquisar livros
 * - Atualizar informações de livros
 * - Excluir livros
 * - Ordenar livros por diferentes critérios
 * - Busca binária para pesquisas eficientes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LIVROS 100
#define MAX_TITULO 50
#define MAX_AUTOR 50
#define MAX_EDITORA 30
#define MAX_ENTRADA 100

// Estrutura para representar um livro
typedef struct {
    int id;                       // Identificador único para o livro
    char titulo[MAX_TITULO];      // Título do livro
    char autor[MAX_AUTOR];        // Autor do livro
    char editora[MAX_EDITORA];    // Editora do livro
    int ano;                      // Ano de publicação
    float preco;                  // Preço do livro
    int disponivel;               // Indica se o livro está disponível (1) ou não (0)
} Livro;

// Variáveis globais
Livro biblioteca[MAX_LIVROS];  // Vetor para armazenar livros
int qtdLivros = 0;             // Quantidade atual de livros na biblioteca
int proximoId = 1;             // ID a ser atribuído ao próximo livro

// Declarações de funções
void limparBuffer();
void esperarEnter();
void exibirMenu();
void adicionarLivro();
void listarLivros();
void buscarLivroPorId();
void buscarLivroPorTitulo();
void atualizarLivro();
void excluirLivro();
void ordenarLivros();
int buscaBinariaPorId(int id, int inicio, int fim);
int buscaBinariaPorTitulo(const char* titulo, int inicio, int fim);
void trocarLivros(int i, int j);
void ordenarPorId();
void ordenarPorTitulo();
void ordenarPorAutor();
void ordenarPorAno();
int obterInteiro(const char* mensagem);
float obterDecimal(const char* mensagem);
void obterTexto(const char* mensagem, char* buffer, int tamanhoMax);
int buscarIndiceLivroPorId(int id);
int buscarIndiceLivroPorTitulo(const char* titulo);
void exibirLivro(const Livro* livro);

int main() {
    int opcao;
    
    printf("╔═════════════════════════════════════╗\n");
    printf("║  SISTEMA DE GERENCIAMENTO DE LIVROS ║\n");
    printf("╚═════════════════════════════════════╝\n");
    printf("Bem-vindo ao Sistema de Gerenciamento de Livros!\n\n");
    
    do {
        exibirMenu();
        printf("Digite sua opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Por favor, digite um número.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();
        
        switch (opcao) {
            case 1:
                adicionarLivro();
                break;
            case 2:
                listarLivros();
                break;
            case 3:
                buscarLivroPorId();
                break;
            case 4:
                buscarLivroPorTitulo();
                break;
            case 5:
                atualizarLivro();
                break;
            case 6:
                excluirLivro();
                break;
            case 7:
                ordenarLivros();
                break;
            case 0:
                printf("Obrigado por usar o Sistema de Gerenciamento de Livros. Até logo!\n");
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
        }
        
        if (opcao != 0) {
            esperarEnter();
        }
        
    } while (opcao != 0);
    
    return 0;
}

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para esperar o usuário pressionar Enter
void esperarEnter() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

// Função para exibir o menu principal
void exibirMenu() {
    printf("\n╔═══════════════ MENU ═══════════════╗\n");
    printf("║  1. Adicionar um novo livro        ║\n");
    printf("║  2. Listar todos os livros         ║\n");
    printf("║  3. Buscar livro por ID            ║\n");
    printf("║  4. Buscar livro por título        ║\n");
    printf("║  5. Atualizar um livro             ║\n");
    printf("║  6. Excluir um livro               ║\n");
    printf("║  7. Ordenar livros                 ║\n");
    printf("║  0. Sair                           ║\n");
    printf("╚═══════════════════════════════════╝\n");
}

// Função para adicionar um novo livro
void adicionarLivro() {
    if (qtdLivros >= MAX_LIVROS) {
        printf("Erro: Biblioteca cheia. Não é possível adicionar mais livros.\n");
        return;
    }
    
    printf("\n╔═══════ ADICIONAR NOVO LIVRO ════════╗\n");
    
    Livro novoLivro;
    novoLivro.id = proximoId++;
    
    obterTexto("Digite o título", novoLivro.titulo, MAX_TITULO);
    obterTexto("Digite o autor", novoLivro.autor, MAX_AUTOR);
    obterTexto("Digite a editora", novoLivro.editora, MAX_EDITORA);
    
    novoLivro.ano = obterInteiro("Digite o ano de publicação");
    novoLivro.preco = obterDecimal("Digite o preço");
    novoLivro.disponivel = 1;  // Novo livro está disponível por padrão
    
    biblioteca[qtdLivros++] = novoLivro;
    
    printf("\nLivro adicionado com sucesso! ID: %d\n", novoLivro.id);
}

// Função para listar todos os livros
void listarLivros() {
    printf("\n╔═══════ TODOS OS LIVROS ════════╗\n");
    
    if (qtdLivros == 0) {
        printf("Não há livros na biblioteca.\n");
        return;
    }
    
    printf("Total de livros: %d\n\n", qtdLivros);
    printf("%-5s %-25s %-20s %-15s %-6s %-10s %-10s\n", 
           "ID", "Título", "Autor", "Editora", "Ano", "Preço", "Disponível");
    printf("--------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < qtdLivros; i++) {
        Livro livro = biblioteca[i];
        printf("%-5d %-25s %-20s %-15s %-6d R$%-8.2f %s\n", 
               livro.id, livro.titulo, livro.autor, livro.editora, livro.ano, livro.preco, 
               (livro.disponivel ? "Sim" : "Não"));
    }
}

// Função para buscar um livro por ID (usando busca binária)
void buscarLivroPorId() {
    printf("\n╔═══════ BUSCAR LIVRO POR ID ════════╗\n");
    
    if (qtdLivros == 0) {
        printf("Não há livros na biblioteca.\n");
        return;
    }
    
    int id = obterInteiro("Digite o ID do livro para buscar");
    
    // Ordena livros por ID antes da busca binária
    ordenarPorId();
    
    int indice = buscaBinariaPorId(id, 0, qtdLivros - 1);
    
    if (indice != -1) {
        printf("\nLivro encontrado:\n");
        exibirLivro(&biblioteca[indice]);
    } else {
        printf("\nLivro com ID %d não encontrado.\n", id);
    }
}

// Função para buscar um livro por título
void buscarLivroPorTitulo() {
    printf("\n╔═══════ BUSCAR LIVRO POR TÍTULO ════════╗\n");
    
    if (qtdLivros == 0) {
        printf("Não há livros na biblioteca.\n");
        return;
    }
    
    char titulo[MAX_TITULO];
    obterTexto("Digite o título do livro para buscar", titulo, MAX_TITULO);
    
    // Ordena livros por título antes da busca binária
    ordenarPorTitulo();
    
    int indice = buscaBinariaPorTitulo(titulo, 0, qtdLivros - 1);
    
    if (indice != -1) {
        printf("\nLivro encontrado:\n");
        exibirLivro(&biblioteca[indice]);
    } else {
        printf("\nLivro com título '%s' não encontrado.\n", titulo);
    }
}

// Função para atualizar um livro
void atualizarLivro() {
    printf("\n╔═══════ ATUALIZAR LIVRO ════════╗\n");
    
    if (qtdLivros == 0) {
        printf("Não há livros na biblioteca.\n");
        return;
    }
    
    int id = obterInteiro("Digite o ID do livro para atualizar");
    
    int indice = buscarIndiceLivroPorId(id);
    
    if (indice == -1) {
        printf("\nLivro com ID %d não encontrado.\n", id);
        return;
    }
    
    printf("\nDetalhes atuais do livro:\n");
    exibirLivro(&biblioteca[indice]);
    
    printf("\nDigite novos detalhes (deixe em branco para manter o valor atual):\n");
    
    char entrada[MAX_ENTRADA];
    
    obterTexto("Digite novo título", entrada, MAX_TITULO);
    if (entrada[0] != '\0') {
        strcpy(biblioteca[indice].titulo, entrada);
    }
    
    obterTexto("Digite novo autor", entrada, MAX_AUTOR);
    if (entrada[0] != '\0') {
        strcpy(biblioteca[indice].autor, entrada);
    }
    
    obterTexto("Digite nova editora", entrada, MAX_EDITORA);
    if (entrada[0] != '\0') {
        strcpy(biblioteca[indice].editora, entrada);
    }
    
    printf("Digite novo ano de publicação (atual: %d, deixe em branco para manter): ", biblioteca[indice].ano);
    fgets(entrada, MAX_ENTRADA, stdin);
    if (entrada[0] != '\n') {
        int ano = atoi(entrada);
        if (ano > 0) {
            biblioteca[indice].ano = ano;
        }
    }
    
    printf("Digite novo preço (atual: %.2f, deixe em branco para manter): ", biblioteca[indice].preco);
    fgets(entrada, MAX_ENTRADA, stdin);
    if (entrada[0] != '\n') {
        float preco = atof(entrada);
        if (preco >= 0) {
            biblioteca[indice].preco = preco;
        }
    }
    
    printf("O livro está disponível? (1 para sim, 0 para não, atual: %d, deixe em branco para manter): ", 
           biblioteca[indice].disponivel);
    fgets(entrada, MAX_ENTRADA, stdin);
    if (entrada[0] != '\n') {
        int disponivel = atoi(entrada);
        if (disponivel == 0 || disponivel == 1) {
            biblioteca[indice].disponivel = disponivel;
        }
    }
    
    printf("\nLivro atualizado com sucesso!\n");
}

// Função para excluir um livro
void excluirLivro() {
    printf("\n╔═══════ EXCLUIR LIVRO ════════╗\n");
    
    if (qtdLivros == 0) {
        printf("Não há livros na biblioteca.\n");
        return;
    }
    
    int id = obterInteiro("Digite o ID do livro para excluir");
    
    int indice = buscarIndiceLivroPorId(id);
    
    if (indice == -1) {
        printf("\nLivro com ID %d não encontrado.\n", id);
        return;
    }
    
    printf("\nLivro a ser excluído:\n");
    exibirLivro(&biblioteca[indice]);
    
    char confirmacao;
    printf("\nTem certeza que deseja excluir este livro? (s/n): ");
    scanf("%c", &confirmacao);
    limparBuffer();
    
    if (tolower(confirmacao) == 's') {
        // Move todos os elementos após o livro excluído uma posição para trás
        for (int i = indice; i < qtdLivros - 1; i++) {
            biblioteca[i] = biblioteca[i + 1];
        }
        qtdLivros--;
        printf("\nLivro excluído com sucesso!\n");
    } else {
        printf("\nExclusão cancelada.\n");
    }
}

// Função para exibir um livro
void exibirLivro(const Livro* livro) {
    printf("ID: %d\n", livro->id);
    printf("Título: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Editora: %s\n", livro->editora);
    printf("Ano de publicação: %d\n", livro->ano);
    printf("Preço: R$%.2f\n", livro->preco);
    printf("Disponível: %s\n", (livro->disponivel ? "Sim" : "Não"));
}

// Função para trocar dois livros no array
void trocarLivros(int i, int j) {
    Livro temp = biblioteca[i];
    biblioteca[i] = biblioteca[j];
    biblioteca[j] = temp;
}

// Função para ordenar livros por ID usando o método bolha
void ordenarPorId() {
    for (int i = 0; i < qtdLivros - 1; i++) {
        for (int j = 0; j < qtdLivros - i - 1; j++) {
            if (biblioteca[j].id > biblioteca[j + 1].id) {
                trocarLivros(j, j + 1);
            }
        }
    }
}

// Função para ordenar livros por título usando o método bolha
void ordenarPorTitulo() {
    for (int i = 0; i < qtdLivros - 1; i++) {
        for (int j = 0; j < qtdLivros - i - 1; j++) {
            if (strcmp(biblioteca[j].titulo, biblioteca[j + 1].titulo) > 0) {
                trocarLivros(j, j + 1);
            }
        }
    }
}

// Função para ordenar livros por autor usando o método bolha
void ordenarPorAutor() {
    for (int i = 0; i < qtdLivros - 1; i++) {
        for (int j = 0; j < qtdLivros - i - 1; j++) {
            if (strcmp(biblioteca[j].autor, biblioteca[j + 1].autor) > 0) {
                trocarLivros(j, j + 1);
            }
        }
    }
}

// Função para ordenar livros por ano usando o método bolha
void ordenarPorAno() {
    for (int i = 0; i < qtdLivros - 1; i++) {
        for (int j = 0; j < qtdLivros - i - 1; j++) {
            if (biblioteca[j].ano > biblioteca[j + 1].ano) {
                trocarLivros(j, j + 1);
            }
        }
    }
}

// Função para menu de ordenação de livros
void ordenarLivros() {
    printf("\n╔═══════ ORDENAR LIVROS ════════╗\n");
    
    if (qtdLivros == 0) {
        printf("Não há livros na biblioteca.\n");
        return;
    }
    
    printf("Ordenar por:\n");
    printf("1. ID\n");
    printf("2. Título\n");
    printf("3. Autor\n");
    printf("4. Ano de publicação\n");
    
    int opcao = obterInteiro("Digite sua opção");
    
    switch (opcao) {
        case 1:
            ordenarPorId();
            printf("\nLivros ordenados por ID.\n");
            break;
        case 2:
            ordenarPorTitulo();
            printf("\nLivros ordenados por título.\n");
            break;
        case 3:
            ordenarPorAutor();
            printf("\nLivros ordenados por autor.\n");
            break;
        case 4:
            ordenarPorAno();
            printf("\nLivros ordenados por ano de publicação.\n");
            break;
        default:
            printf("\nOpção inválida. Livros não ordenados.\n");
            return;
    }
    
    listarLivros();
}

// Função para realizar busca binária por ID
int buscaBinariaPorId(int id, int inicio, int fim) {
    if (inicio > fim) {
        return -1;  // Não encontrado
    }
    
    int meio = inicio + (fim - inicio) / 2;
    
    if (biblioteca[meio].id == id) {
        return meio;  // Encontrado no índice meio
    }
    
    if (biblioteca[meio].id > id) {
        return buscaBinariaPorId(id, inicio, meio - 1);  // Busca na metade esquerda
    } else {
        return buscaBinariaPorId(id, meio + 1, fim);  // Busca na metade direita
    }
}

// Função para realizar busca binária por título
int buscaBinariaPorTitulo(const char* titulo, int inicio, int fim) {
    if (inicio > fim) {
        return -1;  // Não encontrado
    }
    
    int meio = inicio + (fim - inicio) / 2;
    
    int comparacao = strcmp(biblioteca[meio].titulo, titulo);
    
    if (comparacao == 0) {
        return meio;  // Encontrado no índice meio
    }
    
    if (comparacao > 0) {
        return buscaBinariaPorTitulo(titulo, inicio, meio - 1);  // Busca na metade esquerda
    } else {
        return buscaBinariaPorTitulo(titulo, meio + 1, fim);  // Busca na metade direita
    }
}

// Função para buscar um livro por ID usando busca sequencial
int buscarIndiceLivroPorId(int id) {
    for (int i = 0; i < qtdLivros; i++) {
        if (biblioteca[i].id == id) {
            return i;
        }
    }
    return -1;  // Não encontrado
}

// Função para buscar um livro por título usando busca sequencial
int buscarIndiceLivroPorTitulo(const char* titulo) {
    for (int i = 0; i < qtdLivros; i++) {
        if (strcmp(biblioteca[i].titulo, titulo) == 0) {
            return i;
        }
    }
    return -1;  // Não encontrado
}

// Função para obter entrada de número inteiro com validação
int obterInteiro(const char* mensagem) {
    char entrada[MAX_ENTRADA];
    int valor;
    
    while (1) {
        printf("%s: ", mensagem);
        fgets(entrada, MAX_ENTRADA, stdin);
        
        // Remove o caractere de nova linha
        entrada[strcspn(entrada, "\n")] = '\0';
        
        // Verifica se a entrada está vazia
        if (entrada[0] == '\0') {
            printf("Erro: A entrada não pode estar vazia. Por favor, tente novamente.\n");
            continue;
        }
        
        // Verifica se a entrada é um número inteiro válido
        char* fimPtr;
        valor = strtol(entrada, &fimPtr, 10);
        
        if (*fimPtr != '\0') {
            printf("Erro: Entrada inválida. Por favor, digite um número.\n");
            continue;
        }
        
        break;
    }
    
    return valor;
}

// Função para obter entrada de número decimal com validação
float obterDecimal(const char* mensagem) {
    char entrada[MAX_ENTRADA];
    float valor;
    
    while (1) {
        printf("%s: ", mensagem);
        fgets(entrada, MAX_ENTRADA, stdin);
        
        // Remove o caractere de nova linha
        entrada[strcspn(entrada, "\n")] = '\0';
        
        // Verifica se a entrada está vazia
        if (entrada[0] == '\0') {
            printf("Erro: A entrada não pode estar vazia. Por favor, tente novamente.\n");
            continue;
        }
        
        // Verifica se a entrada é um número decimal válido
        char* fimPtr;
        valor = strtof(entrada, &fimPtr);
        
        if (*fimPtr != '\0') {
            printf("Erro: Entrada inválida. Por favor, digite um número.\n");
            continue;
        }
        
        break;
    }
    
    return valor;
}

// Função para obter entrada de texto com validação
void obterTexto(const char* mensagem, char* buffer, int tamanhoMax) {
    while (1) {
        printf("%s: ", mensagem);
        fgets(buffer, tamanhoMax, stdin);
        
        // Remove o caractere de nova linha
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Verifica se a entrada está vazia (permite vazio para operação de atualização)
        if (buffer[0] == '\0' && strcmp(mensagem, "Digite novo título") != 0 && 
            strcmp(mensagem, "Digite novo autor") != 0 && 
            strcmp(mensagem, "Digite nova editora") != 0) {
            printf("Erro: A entrada não pode estar vazia. Por favor, tente novamente.\n");
            continue;
        }
        
        break;
    }
}
