#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int codigo;
    char titulo[50];
    char autor[50];
    float preco;
    int ativo; // 1 = ativo, 0 = excluído
} Livro;

void incluirLivro(Livro livros[], int *n) {
    printf("Código: ");
    scanf("%d", &livros[*n].codigo);
    printf("Título: ");
    scanf(" %[^\n]", livros[*n].titulo);
    printf("Autor: ");
    scanf(" %[^\n]", livros[*n].autor);
    printf("Preço: ");
    scanf("%f", &livros[*n].preco);
    livros[*n].ativo = 1;
    (*n)++;
    printf("Livro incluído com sucesso!\n");
}

void alterarLivro(Livro livros[], int n) {
    int codigo, i;
    printf("Digite o código do livro a alterar: ");
    scanf("%d", &codigo);
    for (i = 0; i < n; i++) {
        if (livros[i].ativo && livros[i].codigo == codigo) {
            printf("Novo título: ");
            scanf(" %[^\n]", livros[i].titulo);
            printf("Novo autor: ");
            scanf(" %[^\n]", livros[i].autor);
            printf("Novo preço: ");
            scanf("%f", &livros[i].preco);
            printf("Livro alterado com sucesso!\n");
            return;
        }
    }
    printf("Livro não encontrado.\n");
}

void excluirLivro(Livro livros[], int n) {
    int codigo, i;
    printf("Digite o código do livro a excluir: ");
    scanf("%d", &codigo);
    for (i = 0; i < n; i++) {
        if (livros[i].ativo && livros[i].codigo == codigo) {
            livros[i].ativo = 0;
            printf("Livro excluído com sucesso!\n");
            return;
        }
    }
    printf("Livro não encontrado.\n");
}

void classificarLivros(Livro livros[], int n) {
    Livro temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (livros[i].ativo && livros[j].ativo && livros[i].codigo > livros[j].codigo) {
                temp = livros[i];
                livros[i] = livros[j];
                livros[j] = temp;
            }
        }
    }
    printf("Livros ordenados por código!\n");
}

int buscaBinaria(Livro livros[], int n, int codigo) {
    int inicio = 0, fim = n - 1, meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (!livros[meio].ativo) {
            meio++; // pula inativo
            continue;
        }
        if (livros[meio].codigo == codigo)
            return meio;
        else if (livros[meio].codigo < codigo)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

void consultarLivro(Livro livros[], int n) {
    int codigo, pos;
    printf("Digite o código do livro para busca binária: ");
    scanf("%d", &codigo);
    pos = buscaBinaria(livros, n, codigo);
    if (pos != -1 && livros[pos].ativo) {
        printf("Livro encontrado:\n");
        printf("Código: %d\nTítulo: %s\nAutor: %s\nPreço: %.2f\n", 
               livros[pos].codigo, livros[pos].titulo, livros[pos].autor, livros[pos].preco);
    } else {
        printf("Livro não encontrado.\n");
    }
}

void listarLivros(Livro livros[], int n) {
    printf("Lista de livros cadastrados:\n");
    for (int i = 0; i < n; i++) {
        if (livros[i].ativo) {
            printf("Código: %d | Título: %s | Autor: %s | Preço: %.2f\n",
                   livros[i].codigo, livros[i].titulo, livros[i].autor, livros[i].preco);
        }
    }
}

int main() {
    Livro livros[MAX];
    int n = 0, op;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Incluir Livro\n");
        printf("2 - Alterar Livro\n");
        printf("3 - Excluir Livro\n");
        printf("4 - Classificar Livros\n");
        printf("5 - Consultar livros\n");
        printf("6 - Listar Todos\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch(op) {
            case 1: incluirLivro(livros, &n); break;
            case 2: alterarLivro(livros, n); break;
            case 3: excluirLivro(livros, n); break;
            case 4: classificarLivros(livros, n); break;
            case 5: consultarLivro(livros, n); break;
            case 6: listarLivros(livros, n); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (op != 0);

    return 0;
}
