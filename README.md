# Especificação Técnica - Sistema de Seguros

## Compilação e Execução

```bash
gcc -o seguradora main.c seguradora.c
./seguradora
```

## Arquivos do Projeto

- `main.c` - Interface de usuário e menu interativo
- `seguradora.c` - Implementação das estruturas de dados e funções
- `seguradora.h` - Definições de tipos e declarações de funções

## Funcionamento do Sistema

### Estrutura de Dados
O sistema organiza conveniados em uma hierarquia de duas camadas:
- **Titulares**: Conveniados principais
- **Dependentes**: Vinculados a um titular específico

### Operações Disponíveis

1. **Inserir Titular**: Cadastra novo titular no sistema
2. **Inserir Dependente**: Vincula dependente a um titular existente
3. **Buscar Conveniado**: Localiza titular ou dependente por CPF
4. **Exibir Todos**: Lista completa hierárquica
5. **Exibir Dependentes**: Lista dependentes de um titular
6. **Exibir Inadimplentes**: Filtra titulares com situação inadimplente
7. **Excluir Dependente**: Remove dependente específico
8. **Excluir Titular**: Remove titular e todos seus dependentes
9. **Estatísticas**: Totais de titulares e dependentes

### Estados dos Conveniados
- `ATIVO`: Conveniado ativo no sistema
- `INATIVO`: Conveniado temporariamente inativo
- `INADIMPLENTE`: Conveniado com pendências

### Graus de Parentesco (15 tipos)
`CONJUGE`, `FILHO`, `FILHA`, `PAI`, `MAE`, `IRMAO`, `IRMA`, `SOGRO`, `SOGRA`, `GENRO`, `NORA`, `NETO`, `NETA`, `AVO`, `OUTRO`

## Funcionamento do Código

### Estruturas Base

```c
// Lista duplamente encadeada genérica
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

// Sistema principal
typedef struct {
    Lista* listaTitulares;
    int totalTitulares;
    int totalDependentes;
} SistemaSeguros;

// Titular com lista própria de dependentes
typedef struct Titular {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    int idade;
    SituacaoConveniado situacao;
    Lista* listaDependentes;
} Titular;

// Dependente (sem ponteiros de lista)
typedef struct Dependente {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    int idade;
    SituacaoConveniado situacao;
    GrauParentesco grauParentesco;
} Dependente;
```

### Organização dos Dados

```
SistemaSeguros
└── Lista de Titulares
    ├── Titular 1
    │   └── Lista de Dependentes
    │       ├── Dependente 1.1
    │       └── Dependente 1.2
    ├── Titular 2
    │   └── Lista de Dependentes
    │       └── Dependente 2.1
    └── Titular N
        └── Lista de Dependentes (vazia)
```

### Funções Principais

#### Lista Genérica
- `criarLista()` - Inicializa lista vazia
- `inserirNoFim()` - Adiciona elemento ao final
- `buscarNo()` - Localiza elemento usando função de comparação
- `removerNo()` - Remove elemento usando função de comparação
- `destruirLista()` - Libera toda a memória da lista

#### Sistema de Seguros
- `inicializarSistema()` - Cria sistema com lista de titulares vazia
- `inserirTitular()` - Cria titular e adiciona à lista principal
- `inserirDependente()` - Localiza titular e adiciona dependente à sua lista
- `buscarConveniado()` - Busca primeiro em titulares, depois em dependentes
- `excluirTitular()` - Remove titular e todos seus dependentes

#### Funções de Comparação
```c
bool compararTitularPorCPF(void* titular, void* cpf);
bool compararDependentePorCPF(void* dependente, void* cpf);
```

#### Funções de Exibição
```c
void processarTitular(void* titular);      // Callback para exibir titular
void processarDependente(void* dependente); // Callback para exibir dependente
```

### Algoritmo de Busca

1. **Busca de Conveniado por CPF**:
   - Procura primeiro na lista de titulares
   - Se não encontrar, percorre cada titular buscando nos dependentes
   - Retorna titular encontrado + dependente (se aplicável)

2. **Inserção de Dependente**:
   - Localiza titular pelo CPF
   - Verifica se CPF do dependente já existe no sistema
   - Cria dependente e adiciona à lista do titular
   - Incrementa contador global

3. **Exclusão de Titular**:
   - Localiza titular na lista principal
   - Remove titular (liberação automática inclui todos os dependentes)
   - Atualiza contadores globais

### Interface do Menu

O menu principal executa em loop até opção 0 (sair):
- Lê opção do usuário
- Chama função correspondente
- Exibe resultado
- Pausa para leitura
- Limpa tela
- Volta ao menu

### Gerenciamento de Memória

- Cada titular possui sua própria lista de dependentes
- Exclusão de titular automaticamente libera todos os dependentes
- Sistema principal mantém apenas uma lista de titulares
- Funções callback são usadas para liberação específica de cada tipo 