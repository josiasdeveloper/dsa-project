#ifndef SEGURADORA_H
#define SEGURADORA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Constantes do sistema
#define MAX_NOME 100
#define MAX_CPF 15
#define MAX_PARENTESCO 30

// Enum para situação do conveniado
typedef enum {
    ATIVO,
    INATIVO,
    INADIMPLENTE
} SituacaoConveniado;

// Enum para grau de parentesco
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

// Estrutura para dependente (lista duplamente encadeada)
typedef struct Dependente {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    int idade;
    SituacaoConveniado situacao;
    GrauParentesco grauParentesco;
    struct Dependente* proximo;
    struct Dependente* anterior;
} Dependente;

// Estrutura para titular 
typedef struct Titular {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    int idade;
    SituacaoConveniado situacao;
    Dependente* listaDependentes;  // Ponteiro para lista de dependentes
    struct Titular* proximo;
} Titular;

// Estrutura principal da multilista
typedef struct {
    Titular* primeiroTitular;
    int totalTitulares;
    int totalDependentes;
} SistemaSeguros;

// ============= DECLARAÇÃO DAS FUNÇÕES =============

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

// Funções de exibição
void exibirTodosConveniados(SistemaSeguros* sistema);
void exibirDependentesTitular(SistemaSeguros* sistema, const char* cpfTitular);
void exibirDadosConveniado(SistemaSeguros* sistema, const char* cpf);
void exibirTitularesInadimplentes(SistemaSeguros* sistema);

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