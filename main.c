#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 100
#define TAM_MAX_STRING 50
#define TAM_CEP 9
#define TAM_TELEFONE 15
#define TAM_CELULAR 15

int qContatos = 0;

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

void inserirContato(Contato *agenda);
void buscarPorNome(Contato *agenda);
void buscarPorEstado(Contato *agenda);
void exibirContato(Contato *agenda, int posicao);

void exibirContato(Contato *agenda, int posicao) {
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
    printf("-----------------------------\n\n");
}

void inserirContato(Contato *agenda) {
    if (qContatos < MAX_CONTATOS) {
        Contato novoContato;
        printf("Nome: ");
        scanf(" %[^\n]s", &novoContato.nome);
        printf("Endereco: ");
        scanf(" %[^\n]s", &novoContato.endereco);
        printf("Bairro: ");
        scanf(" %[^\n]s", &novoContato.bairro);
        printf("Cidade: ");
        scanf(" %[^\n]s", &novoContato.cidade);
        printf("Estado: ");
        scanf(" %[^\n]s", &novoContato.estado);
        printf("CEP: ");
        scanf(" %[^\n]s", &novoContato.cep);
        printf("Telefone: ");
        scanf(" %[^\n]s", &novoContato.telefone);
        printf("Celular: ");
        scanf(" %[^\n]s", &novoContato.celular);

        escreverNoArquivo(novoContato);
        agenda[qContatos] = novoContato;
        qContatos++;

        printf("Contato inserido com sucesso!\n");
    } else {
        printf("A agenda está cheia.\n");
    }
}

void buscarPorNome(Contato *agenda) {
    char nomeBusca[TAM_MAX_STRING];
    printf("Digite o nome para buscar: ");
    scanf(" %[^\n]s", nomeBusca);
    printf("\n\n");

    int encontrado = 0;
    for (int i = 0; i < qContatos; i++) {
        if (strcmp(agenda[i].nome, nomeBusca) == 0) {
            exibirContato(agenda, i);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Contato não encontrado.\n");
    }
}

void buscarPorCidade(Contato *agenda) {
    char cidadeBusca[TAM_MAX_STRING];
    printf("Digite a cidade para buscar: ");
    scanf(" %[^\n]s", cidadeBusca);
    printf("\n\n");

    int encontrado = 0;
    for (int i = 0; i < qContatos; i++) {
        if (strcmp(agenda[i].cidade, cidadeBusca) == 0) {
            exibirContato(agenda, i);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Contato não encontrado.\n");
    }
}

void buscarPorEstado(Contato *agenda) {
    char estadoBusca[TAM_MAX_STRING];
    printf("Digite o estado para buscar: ");
    scanf(" %[^\n]s", estadoBusca);
    printf("\n\n");

    int encontrado = 0;
    for (int i = 0; i < qContatos; i++) {
        if (strcmp(agenda[i].estado, estadoBusca) == 0) {
            exibirContato(agenda, i);
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
        fprintf(arquivo, "%d %s %s %s %s %s %s %s %s\n",
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
    int numeroContatos = 0;
    char contatoLido[250];
    while ((fgets(contatoLido, 250, arquivo)) != NULL) {
        qContatos++;
    }

    qContatos = numeroContatos;
}


void lerArquivo(FILE *arquivo, Contato contato[]) {
    
    lerQuantContatosNoArquivo(arquivo);

    for (int i = 0; i < qContatos; i++) {
        fscanf(arquivo, "%d %s %s %s %s %s %s %s %s\n",
            &contato[i].id,
            &contato->nome,
            &contato->endereco,
            &contato->bairro,
            &contato->cidade,
            &contato->estado,
            &contato->cep,
            &contato->telefone,
            &contato->celular
        );
    }
}

void alterarContato(Contato *agenda) {

}

void excluirContato(Contato *agenda) {
    
}


int main() {
    Contato agenda[MAX_CONTATOS];
    int opcao;

    FILE *arquivoAgenda = fopen("agenda.txt", "r+");

    if (arquivoAgenda == NULL) {
        printf("Não foi possível abrir arquivo de agenda.\n");
    } else {
        lerArquivo(arquivoAgenda, agenda);
        fclose(arquivoAgenda);
    }

    do {
        printf("\n==== Menu ====\n");
        printf("1. Inserir Contato\n");
        printf("2. Buscar por Nome\n");
        printf("3. Buscar por Cidade\n");
        printf("4. Buscar por Estado\n");
        printf("5. Alterar cadastro\n");
        printf("6. Excluir cadastro\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirContato(agenda);
                break;
            case 2:
                buscarPorNome(agenda);
                break;
            case 3:
                buscarPorCidade(agenda);
                break;
            case 4:
                buscarPorEstado(agenda);
                break;
            case 5:
                alterarContato(agenda);
                break;
            case 6:
                exluirContato(agenda);
                break;
            case 7:
                printf("Saindo.\n");
                exit(0);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (1);

    return 0;
}