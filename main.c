#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 100
#define TAM_MAX_STRING 50
#define TAM_CEP 9
#define TAM_TELEFONE 15
#define TAM_CELULAR 15

#define QUANT_CARACTER_LINE 250

typedef struct {
    int id;
    char nome[TAM_MAX_STRING];
    char endereco[TAM_MAX_STRING];
    char bairro[TAM_MAX_STRING];
    char cidade[TAM_MAX_STRING];
    char estado[TAM_MAX_STRING];
    char cep[TAM_CEP];
    char telefone[TAM_TELEFONE];
    char celular[TAM_CELULAR];
} Contato;

Contato agenda[MAX_CONTATOS];
int qContatos = 0;

void inserirContato();
void buscarPorNome();
void buscarPorEstado();
void exibirContato(int posicao);
void escreverNoArquivo(Contato contato);
void excluirContato();

void exibirContato(int posicao) {
    printf("-----------------------------\n");
    printf("Id: %d\n", agenda[posicao].id);
    printf("Nome: %s\n", agenda[posicao].nome);
    printf("Endereco: %s\n", agenda[posicao].endereco);
    printf("Bairro: %s\n", agenda[posicao].bairro);
    printf("Cidade: %s\n", agenda[posicao].cidade);
    printf("Estado: %s\n", agenda[posicao].estado);
    printf("CEP: %s\n", agenda[posicao].cep);
    printf("Telefone: %s\n", agenda[posicao].telefone);
    printf("Celular: %s\n", agenda[posicao].celular);
}

Contato lerContato(int id) {
    Contato contatoLido;

    contatoLido.id = id;

    printf("Nome: ");
    scanf(" %[^\n]s", contatoLido.nome);
    printf("Endereco: ");
    scanf(" %[^\n]s", contatoLido.endereco);
    printf("Bairro: ");
    scanf(" %[^\n]s", contatoLido.bairro);
    printf("Cidade: ");
    scanf(" %[^\n]s", contatoLido.cidade);
    printf("Estado: ");    
    scanf(" %[^\n]s", contatoLido.estado);
    printf("CEP: ");
    scanf(" %[^\n]s", contatoLido.cep);
    printf("Telefone: ");
    scanf(" %[^\n]s", contatoLido.telefone);
    printf("Celular: ");
    scanf(" %[^\n]s", contatoLido.celular);
    return contatoLido;
}

void inserirContato() {
    if (qContatos < MAX_CONTATOS) {
        Contato novoContato;
        novoContato = lerContato(qContatos);
        escreverNoArquivo(novoContato);
        agenda[qContatos] = novoContato;
        qContatos++;
        printf("Contato inserido com sucesso!\n");
    } else {
        printf("A agenda está cheia.\n");
    }
}

void buscarPorNome() {
    char nomeBusca[TAM_MAX_STRING];
    printf("Digite o nome para buscar: ");
    scanf(" %[^\n]s", nomeBusca);
    printf("\n\n");

    int encontrado = 0;
    for (int i = 0; i < qContatos; i++) {
        if (strcmp(agenda[i].nome, nomeBusca) == 0) {
            exibirContato(i);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Contato não encontrado.\n");
    }
}

void buscarPorCidade() {
    char cidadeBusca[TAM_MAX_STRING];
    printf("Digite a cidade para buscar: ");
    scanf(" %[^\n]s", cidadeBusca);
    printf("\n\n");

    int encontrado = 0;
    for (int i = 0; i < qContatos; i++) {
        if (strcmp(agenda[i].cidade, cidadeBusca) == 0) {
            exibirContato(i);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Contato não encontrado.\n");
    }
}

void buscarPorEstado() {
    char estadoBusca[TAM_MAX_STRING];
    printf("Digite o estado para buscar: ");
    scanf(" %[^\n]s", estadoBusca);
    printf("\n\n");

    int encontrado = 0;
    for (int i = 0; i < qContatos; i++) {
        if (strcmp(agenda[i].estado, estadoBusca) == 0) {
            exibirContato(i);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Contato não encontrado.\n");
    }
}


void escreverNoArquivo(Contato contato) {
    FILE *arquivo = fopen("agenda.txt", "r+");

    if (arquivo != NULL) {
        fseek(arquivo, 0, SEEK_END);
        fprintf(arquivo, "%d // %s // %s // %s // %s // %s // %s // %s // %s\n",
                contato.id,
                contato.nome,
                contato.endereco,
                contato.bairro,
                contato.cidade,
                contato.estado,
                contato.cep,
                contato.telefone,
                contato.celular
            );
        fclose(arquivo);
    } else {
        printf("O arquivo não está disponível");
    }
}

void lerQuantContatosNoArquivo(FILE *arquivo) {
    char contatoLido[QUANT_CARACTER_LINE];
    while ((fgets(contatoLido, QUANT_CARACTER_LINE, arquivo)) != NULL) {
        qContatos++;
    }
}


void lerArquivo(FILE *arquivo) {

    lerQuantContatosNoArquivo(arquivo);

    fseek(arquivo, 0, SEEK_SET);

    for (int i = 0; i < qContatos; i++) {
        fscanf(arquivo, "%d // %s // %s // %s // %s // %s // %s // %s // %s\n",
            &agenda[i].id,
            agenda[i].nome,
            agenda[i].endereco,
            agenda[i].bairro,
            agenda[i].cidade,
            agenda[i].estado,
            agenda[i].cep,
            agenda[i].telefone,
            agenda[i].celular
        );
    }
    
}

void listarContatos() {
    for (int i = 0; i < qContatos; i++) {
       exibirContato(i);
    }
}

void escreverContatoPosicao(Contato contato, int posicao) {
    FILE *arquivo = fopen("agenda.txt", "r+");

    if (arquivo == NULL) {
        printf("Arquivo não encontrado.");
    } else {

        char guardarInfoInutil[QUANT_CARACTER_LINE];
        fseek(arquivo, 0, SEEK_SET);

        for (int i = 0; i < posicao; i++) {
            fgets(guardarInfoInutil, QUANT_CARACTER_LINE, arquivo);
        }

        fprintf(arquivo, "%d // %s // %s // %s // %s // %s // %s // %s // %s\n",
                contato.id,
                contato.nome,
                contato.endereco,
                contato.bairro,
                contato.cidade,
                contato.estado,
                contato.cep,
                contato.telefone,
                contato.celular
            );
        fclose(arquivo);
    }
}

void alterarContato() {
    int scan;
    printf("\nDigite o ID do contato a ser alterado:\n");
    printf("Caso queira voltar para pesquisar, digite um id que não exista:\n");
    printf("> ");
    scanf("%d", &scan);
    if (scan < 0 || scan >= qContatos) {
        printf(("O id não existe. Voltando"));
    } else {
        Contato contatoParaAlterar;

        int contatoEncontrado = 0;

        for (int i = 0; i < qContatos; i++) {
            if (agenda[i].id == scan) {
                contatoEncontrado = 1;

                contatoParaAlterar = lerContato(i);
                agenda[i] = contatoParaAlterar;
                escreverContatoPosicao(contatoParaAlterar, i);
                break;
            }
        }
        if (!contatoEncontrado)
            printf("\nOcorreu um erro. Contato não encontrado\n");
    }
    
}

void excluirContato() {
    int cId;
}


int main() {

    int opcao;

    FILE *arquivoAgenda = fopen("agenda.txt", "r+");

    if (arquivoAgenda == NULL) {
        printf("Não foi possível abrir arquivo de agenda.\n");
        exit(0);
    } else {
        lerArquivo(arquivoAgenda);
        fclose(arquivoAgenda);
    }

    do {
        printf("\n==== Menu ====\n");
        printf("1. Inserir Contato\n");
        printf("2. Listar todos os contatos\n");
        printf("3. Buscar por Nome\n");
        printf("4. Buscar por Cidade\n");
        printf("5. Buscar por Estado\n");
        printf("6. Alterar cadastro\n");
        printf("7. Excluir cadastro\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirContato();
                break;
            case 2:
                listarContatos();
                break;
            case 3:
                buscarPorNome();
                break;
            case 4:
                buscarPorCidade();
                break;
            case 5:
                buscarPorEstado();
                break;
            case 6:
                alterarContato();
                break;
            case 7:
                excluirContato();
                break;
            case 8:
                printf("Saindo.\n");
                exit(0);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (1);

    return 0;
}