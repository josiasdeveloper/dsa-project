#ifndef SEGURADORA_H
#define SEGURADORA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOME 100
#define MAX_CPF 15
#define MAX_PARENTESCO 30

// ============= DEFINIÇÕES DE LISTAS GENÉRICAS =============


typedef struct No {
    void* dados;
    struct No* proximo;
    struct No* anterior;
} No;


typedef struct Lista {
    No* head;
    No* tail;
    int tamanho;
} Lista;

// ============= ENUMERAÇÕES =============



typedef enum {
    ATIVO,
    INATIVO,
    INADIMPLENTE
} SituacaoConveniado;


typedef enum {
    CONJUGE,
    FILHO,
    FILHA,
    PAI,
    MAE,
    IRMAO,
    IRMA,
    SOGRO,
    SOGRA,
    GENRO,
    NORA,
    NETO,
    NETA,
    AVO,
    AVA,
    OUTRO
} GrauParentesco;



// ============= ESTRUTURAS DE DADOS =============


typedef struct Dependente {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    int idade;
    SituacaoConveniado situacao;
    GrauParentesco grauParentesco;
} Dependente;

typedef struct Titular {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    int idade;
    SituacaoConveniado situacao;
    Lista* listaDependentes;  // Lista de dependentes 
} Titular;

typedef struct {
    Lista* listaTitulares;    // Lista de titulares
    int totalTitulares;
    int totalDependentes;
} SistemaSeguros;



// ============= DECLARAÇÃO DAS FUNÇÕES DE LISTA =============



Lista* criarLista();
void destruirLista(Lista* lista, void (*liberarDados)(void*));
bool inserirNoInicio(Lista* lista, void* dados);
bool inserirNoFim(Lista* lista, void* dados);
bool removerNo(Lista* lista, void* dados, bool (*comparar)(void*, void*));
No* buscarNo(Lista* lista, void* chave, bool (*comparar)(void*, void*));
void percorrerLista(Lista* lista, void (*processar)(void*));
bool listaVazia(Lista* lista);
int tamanhoLista(Lista* lista);



// ============= DECLARAÇÃO DAS FUNÇÕES DO SISTEMA =============



// Funções de inicialização
SistemaSeguros* inicializarSistema();
void destruirSistema(SistemaSeguros* sistema);


// Funções de criação
Titular* criarTitular(const char* nome, const char* cpf, int idade, SituacaoConveniado situacao);
Dependente* criarDependente(const char* nome, const char* cpf, int idade, SituacaoConveniado situacao, GrauParentesco grau);


// Funções de inserção
bool inserirTitular(SistemaSeguros* sistema, const char* nome, const char* cpf, int idade, SituacaoConveniado situacao);
bool inserirDependente(SistemaSeguros* sistema, const char* cpfTitular, const char* nome, const char* cpf, int idade, SituacaoConveniado situacao, GrauParentesco grau);


// Funções de busca
Titular* buscarTitular(SistemaSeguros* sistema, const char* cpf);
Dependente* buscarDependente(Titular* titular, const char* cpf);
bool buscarConveniado(SistemaSeguros* sistema, const char* cpf, Titular** titular, Dependente** dependente);


// Funções de comparação (para usar com as listas genéricas)
bool compararTitularPorCPF(void* titular, void* cpf);
bool compararDependentePorCPF(void* dependente, void* cpf);


// Funções de liberação de memória
void liberarTitular(void* titular);
void liberarDependente(void* dependente); // aqui


// Funções de exibição
void exibirTodosConveniados(SistemaSeguros* sistema);
void exibirDependentesTitular(SistemaSeguros* sistema, const char* cpfTitular);
void exibirDadosConveniado(SistemaSeguros* sistema, const char* cpf);
void exibirTitularesInadimplentes(SistemaSeguros* sistema);


// Funções de processamento para percorrer listas
void processarTitular(void* titular);
void processarDependente(void* dependente);


// Funções de remoção
bool excluirDependente(SistemaSeguros* sistema, const char* cpfTitular, const char* cpfDependente);
bool excluirTitular(SistemaSeguros* sistema, const char* cpf);


// Funções auxiliares
const char* situacaoParaString(SituacaoConveniado situacao);
const char* parentescoParaString(GrauParentesco grau);
GrauParentesco stringParaParentesco(const char* str);
SituacaoConveniado stringParaSituacao(const char* str);
bool validarCPF(const char* cpf);
void limparBuffer();


// Função do menu
void exibirMenu();
void executarSistema();


#endif // SEGURADORA_H 