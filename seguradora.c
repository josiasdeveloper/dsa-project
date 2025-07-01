#include "seguradora.h"

// ============= IMPLEMENTAÇÃO DAS FUNÇÕES DE LISTA GENÉRICA =============

Lista* criarLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) {
        return NULL;
    }
    
    lista->head = NULL;
    lista->tail = NULL;
    lista->tamanho = 0;
    
    return lista;
}

void destruirLista(Lista* lista, void (*liberarDados)(void*)) {
    if (lista == NULL) {
        return;
    }
    
    No* atual = lista->head;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        
        if (liberarDados != NULL && atual->dados != NULL) {
            liberarDados(atual->dados);
        }
        
        free(atual);
        atual = proximo;
    }
    
    free(lista);
}

bool inserirNoInicio(Lista* lista, void* dados) {
    if (lista == NULL || dados == NULL) {
        return false;
    }
    
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        return false;
    }
    
    novoNo->dados = dados;
    novoNo->anterior = NULL;
    novoNo->proximo = lista->head;
    
    if (lista->head != NULL) {
        lista->head->anterior = novoNo;
    } else {
        // Lista estava vazia, novo nó é também o tail
        lista->tail = novoNo;
    }
    
    lista->head = novoNo;
    lista->tamanho++;
    
    return true;
}

bool inserirNoFim(Lista* lista, void* dados) {
    if (lista == NULL || dados == NULL) {
        return false;
    }
    
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        return false;
    }
    
    novoNo->dados = dados;
    novoNo->proximo = NULL;
    novoNo->anterior = lista->tail;
    
    if (lista->tail != NULL) {
        lista->tail->proximo = novoNo;
    } else {
        // Lista estava vazia, novo nó é também o head
        lista->head = novoNo;
    }
    
    lista->tail = novoNo;
    lista->tamanho++;
    
    return true;
}

bool removerNo(Lista* lista, void* dados, bool (*comparar)(void*, void*)) {
    if (lista == NULL || dados == NULL || comparar == NULL) {
        return false;
    }
    
    No* atual = lista->head;
    
    while (atual != NULL) {
        if (comparar(atual->dados, dados)) {
            // Encontrou o nó a ser removido
            
            // Ajustar ponteiros do nó anterior
            if (atual->anterior != NULL) {
                atual->anterior->proximo = atual->proximo;
            } else {
                // Era o primeiro nó
                lista->head = atual->proximo;
            }
            
            // Ajustar ponteiros do nó posterior
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            } else {
                // Era o último nó
                lista->tail = atual->anterior;
            }
            
            free(atual);
            lista->tamanho--;
            
            return true;
        }
        atual = atual->proximo;
    }
    
    return false; // Não encontrou o elemento
}

No* buscarNo(Lista* lista, void* chave, bool (*comparar)(void*, void*)) {
    if (lista == NULL || chave == NULL || comparar == NULL) {
        return NULL;
    }
    
    No* atual = lista->head;
    
    while (atual != NULL) {
        if (comparar(atual->dados, chave)) {
            return atual;
        }
        atual = atual->proximo;
    }
    
    return NULL; // Não encontrou
}

void percorrerLista(Lista* lista, void (*processar)(void*)) {
    if (lista == NULL || processar == NULL) {
        return;
    }
    
    No* atual = lista->head;
    
    while (atual != NULL) {
        processar(atual->dados);
        atual = atual->proximo;
    }
}

bool listaVazia(Lista* lista) {
    if (lista == NULL) {
        return true;
    }
    
    return lista->tamanho == 0;
}

int tamanhoLista(Lista* lista) {
    if (lista == NULL) {
        return 0;
    }
    
    return lista->tamanho;
}

// ============= IMPLEMENTAÇÃO DAS FUNÇÕES DO SISTEMA =============

// Funções de inicialização
SistemaSeguros* inicializarSistema() {
    SistemaSeguros* sistema = (SistemaSeguros*)malloc(sizeof(SistemaSeguros));
    if (sistema == NULL) {
        return NULL;
    }
    
    sistema->listaTitulares = criarLista();
    if (sistema->listaTitulares == NULL) {
        free(sistema);
        return NULL;
    }
    
    sistema->totalTitulares = 0;
    sistema->totalDependentes = 0;
    
    return sistema;
}

void destruirSistema(SistemaSeguros* sistema) {
    if (sistema == NULL) {
        return;
    }
    
    if (sistema->listaTitulares != NULL) {
        destruirLista(sistema->listaTitulares, liberarTitular);
    }
    
    free(sistema);
}

// Funções de criação
Titular* criarTitular(const char* nome, const char* cpf, int idade, SituacaoConveniado situacao) {
    if (nome == NULL || cpf == NULL || strlen(nome) == 0 || strlen(cpf) == 0) {
        return NULL;
    }
    
    Titular* titular = (Titular*)malloc(sizeof(Titular));
    if (titular == NULL) {
        return NULL;
    }
    
    // Copiar dados
    strncpy(titular->nome, nome, MAX_NOME - 1);
    titular->nome[MAX_NOME - 1] = '\0';
    
    strncpy(titular->cpf, cpf, MAX_CPF - 1);
    titular->cpf[MAX_CPF - 1] = '\0';
    
    titular->idade = idade;
    titular->situacao = situacao;
    
    // Criar lista de dependentes
    titular->listaDependentes = criarLista();
    if (titular->listaDependentes == NULL) {
        free(titular);
        return NULL;
    }
    
    return titular;
}

Dependente* criarDependente(const char* nome, const char* cpf, int idade, SituacaoConveniado situacao, GrauParentesco grau) {
    if (nome == NULL || cpf == NULL || strlen(nome) == 0 || strlen(cpf) == 0) {
        return NULL;
    }
    
    Dependente* dependente = (Dependente*)malloc(sizeof(Dependente));
    if (dependente == NULL) {
        return NULL;
    }
    
    // Copiar dados
    strncpy(dependente->nome, nome, MAX_NOME - 1);
    dependente->nome[MAX_NOME - 1] = '\0';
    
    strncpy(dependente->cpf, cpf, MAX_CPF - 1);
    dependente->cpf[MAX_CPF - 1] = '\0';
    
    dependente->idade = idade;
    dependente->situacao = situacao;
    dependente->grauParentesco = grau;
    
    return dependente;
}

// Funções de inserção
bool inserirTitular(SistemaSeguros* sistema, const char* nome, const char* cpf, int idade, SituacaoConveniado situacao) {
    if (sistema == NULL || nome == NULL || cpf == NULL) {
        return false;
    }
    
    // Verificar se CPF já existe
    if (buscarTitular(sistema, cpf) != NULL) {
        return false; // CPF já cadastrado
    }
    
    Titular* novoTitular = criarTitular(nome, cpf, idade, situacao);
    if (novoTitular == NULL) {
        return false;
    }
    
    if (!inserirNoFim(sistema->listaTitulares, novoTitular)) {
        // Falha ao inserir na lista
        destruirLista(novoTitular->listaDependentes, liberarDependente);
        free(novoTitular);
        return false;
    }
    
    sistema->totalTitulares++;
    return true;
}

bool inserirDependente(SistemaSeguros* sistema, const char* cpfTitular, const char* nome, const char* cpf, int idade, SituacaoConveniado situacao, GrauParentesco grau) {
    if (sistema == NULL || cpfTitular == NULL || nome == NULL || cpf == NULL) {
        return false;
    }
    
    // Buscar o titular
    Titular* titular = buscarTitular(sistema, cpfTitular);
    if (titular == NULL) {
        return false; // Titular não encontrado
    }
    
    // Verificar se CPF do dependente já existe no sistema
    Titular* titularExistente;
    Dependente* dependenteExistente;
    if (buscarConveniado(sistema, cpf, &titularExistente, &dependenteExistente)) {
        return false; // CPF já cadastrado
    }
    
    Dependente* novoDependente = criarDependente(nome, cpf, idade, situacao, grau);
    if (novoDependente == NULL) {
        return false;
    }
    
    if (!inserirNoFim(titular->listaDependentes, novoDependente)) {
        // Falha ao inserir na lista
        free(novoDependente);
        return false;
    }
    
    sistema->totalDependentes++;
    return true;
}

// ============= FUNÇÕES AUXILIARES =============

// Funções de comparação
bool compararTitularPorCPF(void* titular, void* cpf) {
    if (titular == NULL || cpf == NULL) {
        return false;
    }
    
    Titular* t = (Titular*)titular;
    const char* c = (const char*)cpf;
    
    return strcmp(t->cpf, c) == 0;
}

bool compararDependentePorCPF(void* dependente, void* cpf) {
    if (dependente == NULL || cpf == NULL) {
        return false;
    }
    
    Dependente* d = (Dependente*)dependente;
    const char* c = (const char*)cpf;
    
    return strcmp(d->cpf, c) == 0;
}

// Funções de liberação de memória
void liberarTitular(void* titular) {
    if (titular == NULL) {
        return;
    }
    
    Titular* t = (Titular*)titular;
    
    if (t->listaDependentes != NULL) {
        destruirLista(t->listaDependentes, liberarDependente);
    }
    
    free(t);
}

void liberarDependente(void* dependente) {
    if (dependente == NULL) {
        return;
    }
    
    free(dependente);
}

// Funções de busca
Titular* buscarTitular(SistemaSeguros* sistema, const char* cpf) {
    if (sistema == NULL || cpf == NULL || sistema->listaTitulares == NULL) {
        return NULL;
    }
    
    No* no = buscarNo(sistema->listaTitulares, (void*)cpf, compararTitularPorCPF);
    
    if (no != NULL) {
        return (Titular*)no->dados;
    }
    
    return NULL;
}

Dependente* buscarDependente(Titular* titular, const char* cpf) {
    if (titular == NULL || cpf == NULL || titular->listaDependentes == NULL) {
        return NULL;
    }
    
    No* no = buscarNo(titular->listaDependentes, (void*)cpf, compararDependentePorCPF);
    
    if (no != NULL) {
        return (Dependente*)no->dados;
    }
    
    return NULL;
}

bool buscarConveniado(SistemaSeguros* sistema, const char* cpf, Titular** titular, Dependente** dependente) {
    if (sistema == NULL || cpf == NULL) {
        return false;
    }
    
    // Inicializar ponteiros de saída
    if (titular != NULL) {
        *titular = NULL;
    }
    if (dependente != NULL) {
        *dependente = NULL;
    }
    
    // Primeiro, verificar se é um titular
    Titular* titularEncontrado = buscarTitular(sistema, cpf);
    if (titularEncontrado != NULL) {
        if (titular != NULL) {
            *titular = titularEncontrado;
        }
        return true;
    }
    
    // Se não é titular, procurar nos dependentes
    No* noTitular = sistema->listaTitulares->head;
    
    while (noTitular != NULL) {
        Titular* t = (Titular*)noTitular->dados;
        Dependente* dependenteEncontrado = buscarDependente(t, cpf);
        
        if (dependenteEncontrado != NULL) {
            if (titular != NULL) {
                *titular = t;
            }
            if (dependente != NULL) {
                *dependente = dependenteEncontrado;
            }
            return true;
        }
        
        noTitular = noTitular->proximo;
    }
    
    return false; // Não encontrado
}

// ============= FUNÇÕES AUXILIARES DE CONVERSÃO E VALIDAÇÃO =============

const char* situacaoParaString(SituacaoConveniado situacao) {
    switch (situacao) {
        case ATIVO:
            return "ATIVO";
        case INATIVO:
            return "INATIVO";
        case INADIMPLENTE:
            return "INADIMPLENTE";
        default:
            return "DESCONHECIDA";
    }
}

const char* parentescoParaString(GrauParentesco grau) {
    switch (grau) {
        case CONJUGE:
            return "CONJUGE";
        case FILHO:
            return "FILHO";
        case FILHA:
            return "FILHA";
        case PAI:
            return "PAI";
        case MAE:
            return "MAE";
        case IRMAO:
            return "IRMAO";
        case IRMA:
            return "IRMA";
        case SOGRO:
            return "SOGRO";
        case SOGRA:
            return "SOGRA";
        case GENRO:
            return "GENRO";
        case NORA:
            return "NORA";
        case NETO:
            return "NETO";
        case NETA:
            return "NETA";
        case AVO:
            return "AVO";
        case AVA:
            return "AVA";
        case OUTRO:
            return "OUTRO";
        default:
            return "DESCONHECIDO";
    }
}

GrauParentesco stringParaParentesco(const char* str) {
    if (str == NULL) {
        return OUTRO;
    }
    
    if (strcmp(str, "CONJUGE") == 0) return CONJUGE;
    if (strcmp(str, "FILHO") == 0) return FILHO;
    if (strcmp(str, "FILHA") == 0) return FILHA;
    if (strcmp(str, "PAI") == 0) return PAI;
    if (strcmp(str, "MAE") == 0) return MAE;
    if (strcmp(str, "IRMAO") == 0) return IRMAO;
    if (strcmp(str, "IRMA") == 0) return IRMA;
    if (strcmp(str, "SOGRO") == 0) return SOGRO;
    if (strcmp(str, "SOGRA") == 0) return SOGRA;
    if (strcmp(str, "GENRO") == 0) return GENRO;
    if (strcmp(str, "NORA") == 0) return NORA;
    if (strcmp(str, "NETO") == 0) return NETO;
    if (strcmp(str, "NETA") == 0) return NETA;
    if (strcmp(str, "AVO") == 0) return AVO;
    if (strcmp(str, "AVA") == 0) return AVA;
    
    return OUTRO;
}

SituacaoConveniado stringParaSituacao(const char* str) {
    if (str == NULL) {
        return ATIVO;
    }
    
    if (strcmp(str, "ATIVO") == 0) return ATIVO;
    if (strcmp(str, "INATIVO") == 0) return INATIVO;
    if (strcmp(str, "INADIMPLENTE") == 0) return INADIMPLENTE;
    
    return ATIVO; // Padrão
}

bool validarCPF(const char* cpf) {
    if (cpf == NULL) {
        return false;
    }
    
    int len = strlen(cpf);
    
    
    if (len != 11 && len != 14) {
        return false;
    }
    
    
    char digitos[12] = {0};
    int pos = 0;
    
    for (int i = 0; i < len && pos < 11; i++) {
        if (cpf[i] >= '0' && cpf[i] <= '9') {
            digitos[pos++] = cpf[i];
        } else if (cpf[i] != '.' && cpf[i] != '-') {
            return false; // Caractere inválido
        }
    }
    
    if (pos != 11) {
        return false;
    }
    
    
    bool todosIguais = true;
    for (int i = 1; i < 11; i++) {
        if (digitos[i] != digitos[0]) {
            todosIguais = false;
            break;
        }
    }
    
    if (todosIguais) {
        return false;
    }
    
    
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (digitos[i] - '0') * (10 - i);
    }
    
    int resto = soma % 11;
    int digito1 = (resto < 2) ? 0 : 11 - resto;
    
    if ((digitos[9] - '0') != digito1) {
        return false;
    }
    
    
    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (digitos[i] - '0') * (11 - i);
    }
    
    resto = soma % 11;
    int digito2 = (resto < 2) ? 0 : 11 - resto;
    
    if ((digitos[10] - '0') != digito2) {
        return false;
    }
    
    return true;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {

    }
}

// ============= FUNÇÕES DE EXIBIÇÃO =============

void processarTitular(void* titular) {
    if (titular == NULL) return;
    
    Titular* t = (Titular*)titular;
    printf("\n📋 TITULAR:\n");
    printf("  Nome: %s\n", t->nome);
    printf("  CPF: %s\n", t->cpf);
    printf("  Idade: %d anos\n", t->idade);
    printf("  Situação: %s\n", situacaoParaString(t->situacao));
    printf("  Dependentes: %d\n", tamanhoLista(t->listaDependentes));
    
    if (!listaVazia(t->listaDependentes)) {
        printf("  👥 Lista de Dependentes:\n");
        percorrerLista(t->listaDependentes, processarDependente);
    }
}

void processarDependente(void* dependente) {
    if (dependente == NULL) return;
    
    Dependente* d = (Dependente*)dependente;
    printf("    • %s (CPF: %s) - %d anos - %s - %s\n",
           d->nome, d->cpf, d->idade,
           situacaoParaString(d->situacao),
           parentescoParaString(d->grauParentesco));
}

void exibirTodosConveniados(SistemaSeguros* sistema) {
    if (sistema == NULL || listaVazia(sistema->listaTitulares)) {
        printf("\n❌ Nenhum conveniado cadastrado no sistema.\n");
        return;
    }
    
    printf("\n===============================================\n");
    printf("           TODOS OS CONVENIADOS\n");
    printf("===============================================\n");
    
    percorrerLista(sistema->listaTitulares, processarTitular);
    
    printf("\n===============================================\n");
    printf("Total: %d titulares e %d dependentes\n", 
           sistema->totalTitulares, sistema->totalDependentes);
}

void exibirDependentesTitular(SistemaSeguros* sistema, const char* cpfTitular) {
    if (sistema == NULL || cpfTitular == NULL) {
        printf("❌ Parâmetros inválidos!\n");
        return;
    }
    
    Titular* titular = buscarTitular(sistema, cpfTitular);
    if (titular == NULL) {
        printf("❌ Titular não encontrado!\n");
        return;
    }
    
    printf("\n===============================================\n");
    printf("         DEPENDENTES DO TITULAR\n");
    printf("===============================================\n");
    printf("Titular: %s (CPF: %s)\n", titular->nome, titular->cpf);
    printf("-----------------------------------------------\n");
    
    if (listaVazia(titular->listaDependentes)) {
        printf("❌ Este titular não possui dependentes.\n");
    } else {
        printf("Total de dependentes: %d\n\n", tamanhoLista(titular->listaDependentes));
        percorrerLista(titular->listaDependentes, processarDependente);
    }
}

void exibirDadosConveniado(SistemaSeguros* sistema, const char* cpf) {
    if (sistema == NULL || cpf == NULL) {
        printf("❌ Parâmetros inválidos!\n");
        return;
    }
    
    Titular* titular;
    Dependente* dependente;
    
    if (buscarConveniado(sistema, cpf, &titular, &dependente)) {
        printf("\n===============================================\n");
        printf("           DADOS DO CONVENIADO\n");
        printf("===============================================\n");
        
        if (dependente == NULL) {
            // É um titular
            processarTitular(titular);
        } else {
            // É um dependente
            printf("👤 DEPENDENTE:\n");
            printf("  Nome: %s\n", dependente->nome);
            printf("  CPF: %s\n", dependente->cpf);
            printf("  Idade: %d anos\n", dependente->idade);
            printf("  Situação: %s\n", situacaoParaString(dependente->situacao));
            printf("  Parentesco: %s\n", parentescoParaString(dependente->grauParentesco));
            printf("  Titular: %s (CPF: %s)\n", titular->nome, titular->cpf);
        }
    } else {
        printf("❌ Conveniado não encontrado!\n");
    }
}

void processarTitularInadimplente(void* titular) {
    if (titular == NULL) return;
    
    Titular* t = (Titular*)titular;
    if (t->situacao == INADIMPLENTE) {
        printf("• %s (CPF: %s) - %d anos\n", t->nome, t->cpf, t->idade);
        if (!listaVazia(t->listaDependentes)) {
            printf("  Dependentes: %d\n", tamanhoLista(t->listaDependentes));
        }
        printf("\n");
    }
}

void exibirTitularesInadimplentes(SistemaSeguros* sistema) {
    if (sistema == NULL || listaVazia(sistema->listaTitulares)) {
        printf("\n❌ Nenhum titular cadastrado no sistema.\n");
        return;
    }
    
    printf("\n===============================================\n");
    printf("           TITULARES INADIMPLENTES\n");
    printf("===============================================\n");
    
    // Contar inadimplentes
    int countInadimplentes = 0;
    No* atual = sistema->listaTitulares->head;
    while (atual != NULL) {
        Titular* t = (Titular*)atual->dados;
        if (t->situacao == INADIMPLENTE) {
            countInadimplentes++;
        }
        atual = atual->proximo;
    }
    
    if (countInadimplentes == 0) {
        printf("✅ Não há titulares inadimplentes no sistema.\n");
    } else {
        printf("Total de inadimplentes: %d\n\n", countInadimplentes);
        percorrerLista(sistema->listaTitulares, processarTitularInadimplente);
    }
}

// ============= FUNÇÕES DE REMOÇÃO =============

bool excluirDependente(SistemaSeguros* sistema, const char* cpfTitular, const char* cpfDependente) {
    if (sistema == NULL || cpfTitular == NULL || cpfDependente == NULL) {
        return false;
    }
    
    Titular* titular = buscarTitular(sistema, cpfTitular);
    if (titular == NULL) {
        return false; // Titular não encontrado
    }
    
    // Buscar e remover o dependente
    if (removerNo(titular->listaDependentes, (void*)cpfDependente, compararDependentePorCPF)) {
        sistema->totalDependentes--;
        return true;
    }
    
    return false; // Dependente não encontrado
}

bool excluirTitular(SistemaSeguros* sistema, const char* cpf) {
    if (sistema == NULL || cpf == NULL) {
        return false;
    }
    
    Titular* titular = buscarTitular(sistema, cpf);
    if (titular == NULL) {
        return false; // Titular não encontrado
    }
    
    // Contar dependentes para atualizar estatísticas
    int numDependentes = tamanhoLista(titular->listaDependentes);
    
    // Remover titular (isso também liberará todos os dependentes via liberarTitular)
    if (removerNo(sistema->listaTitulares, (void*)cpf, compararTitularPorCPF)) {
        sistema->totalTitulares--;
        sistema->totalDependentes -= numDependentes;
        return true;
    }
    
    return false;
}


