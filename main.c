#include "seguradora.h"

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void exibirMenu() {
    printf("\n===============================================\n");
    printf("         SISTEMA DE SEGUROS - MENU PRINCIPAL\n");
    printf("===============================================\n");
    printf("1. Inserir Titular\n");
    printf("2. Inserir Dependente\n");
    printf("3. Buscar Conveniado\n");
    printf("4. Exibir Todos os Conveniados\n");
    printf("5. Exibir Dependentes de um Titular\n");
    printf("6. Exibir Titulares Inadimplentes\n");
    printf("7. Excluir Dependente\n");
    printf("8. Excluir Titular\n");
    printf("9. Estatísticas do Sistema\n");
    printf("0. Sair\n");
    printf("===============================================\n");
    printf("Digite sua opção: ");
}

void menuInserirTitular(SistemaSeguros* sistema) {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    int idade;
    int opcaoSituacao;
    
    printf("\n--- INSERIR TITULAR ---\n");
    
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0; // Remove \n
    
    printf("CPF: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    
    if (!validarCPF(cpf)) {
        printf("❌ CPF inválido!\n");
        return;
    }
    
    printf("Idade: ");
    if (scanf("%d", &idade) != 1) {
        printf("❌ Idade inválida!\n");
        limparBuffer();
        return;
    }
    limparBuffer();
    
    printf("Situação:\n");
    printf("1. ATIVO\n");
    printf("2. INATIVO\n");
    printf("3. INADIMPLENTE\n");
    printf("Opção: ");
    
    if (scanf("%d", &opcaoSituacao) != 1) {
        printf("❌ Opção inválida!\n");
        limparBuffer();
        return;
    }
    limparBuffer();
    
    SituacaoConveniado situacao;
    switch (opcaoSituacao) {
        case 1: situacao = ATIVO; break;
        case 2: situacao = INATIVO; break;
        case 3: situacao = INADIMPLENTE; break;
        default:
            printf("❌ Opção inválida!\n");
            return;
    }
    
    if (inserirTitular(sistema, nome, cpf, idade, situacao)) {
        printf("✅ Titular inserido com sucesso!\n");
    } else {
        printf("❌ Erro ao inserir titular. CPF pode já estar cadastrado.\n");
    }
}

void menuInserirDependente(SistemaSeguros* sistema) {
    char cpfTitular[MAX_CPF];
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    int idade;
    int opcaoSituacao;
    int opcaoParentesco;
    
    printf("\n--- INSERIR DEPENDENTE ---\n");
    
    printf("CPF do Titular: ");
    fgets(cpfTitular, sizeof(cpfTitular), stdin);
    cpfTitular[strcspn(cpfTitular, "\n")] = 0;
    
    if (!validarCPF(cpfTitular)) {
        printf("❌ CPF do titular inválido!\n");
        return;
    }
    
    printf("Nome do Dependente: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    printf("CPF do Dependente: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    
    if (!validarCPF(cpf)) {
        printf("❌ CPF do dependente inválido!\n");
        return;
    }
    
    printf("Idade: ");
    if (scanf("%d", &idade) != 1) {
        printf("❌ Idade inválida!\n");
        limparBuffer();
        return;
    }
    limparBuffer();
    
    printf("Situação:\n");
    printf("1. ATIVO\n");
    printf("2. INATIVO\n");
    printf("3. INADIMPLENTE\n");
    printf("Opção: ");
    
    if (scanf("%d", &opcaoSituacao) != 1) {
        printf("❌ Opção inválida!\n");
        limparBuffer();
        return;
    }
    limparBuffer();
    
    SituacaoConveniado situacao;
    switch (opcaoSituacao) {
        case 1: situacao = ATIVO; break;
        case 2: situacao = INATIVO; break;
        case 3: situacao = INADIMPLENTE; break;
        default:
            printf("❌ Opção inválida!\n");
            return;
    }
    
    printf("Grau de Parentesco:\n");
    printf("1. CONJUGE\n2. FILHO\n3. FILHA\n4. PAI\n5. MAE\n");
    printf("6. IRMAO\n7. IRMA\n8. SOGRO\n9. SOGRA\n10. GENRO\n");
    printf("11. NORA\n12. NETO\n13. NETA\n14. AVO\n15. AVA\n16. OUTRO\n");
    printf("Opção: ");
    
    if (scanf("%d", &opcaoParentesco) != 1) {
        printf("❌ Opção inválida!\n");
        limparBuffer();
        return;
    }
    limparBuffer();
    
    GrauParentesco grau;
    switch (opcaoParentesco) {
        case 1: grau = CONJUGE; break;
        case 2: grau = FILHO; break;
        case 3: grau = FILHA; break;
        case 4: grau = PAI; break;
        case 5: grau = MAE; break;
        case 6: grau = IRMAO; break;
        case 7: grau = IRMA; break;
        case 8: grau = SOGRO; break;
        case 9: grau = SOGRA; break;
        case 10: grau = GENRO; break;
        case 11: grau = NORA; break;
        case 12: grau = NETO; break;
        case 13: grau = NETA; break;
        case 14: grau = AVO; break;
        case 15: grau = AVA; break;
        case 16: grau = OUTRO; break;
        default:
            printf("❌ Opção inválida!\n");
            return;
    }
    
    if (inserirDependente(sistema, cpfTitular, nome, cpf, idade, situacao, grau)) {
        printf("✅ Dependente inserido com sucesso!\n");
    } else {
        printf("❌ Erro ao inserir dependente. Verifique se o titular existe e se o CPF não está duplicado.\n");
    }
}

void menuBuscarConveniado(SistemaSeguros* sistema) {
    char cpf[MAX_CPF];
    
    printf("\n--- BUSCAR CONVENIADO ---\n");
    printf("CPF: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    
    if (!validarCPF(cpf)) {
        printf("❌ CPF inválido!\n");
        return;
    }
    
    Titular* titular;
    Dependente* dependente;
    
    if (buscarConveniado(sistema, cpf, &titular, &dependente)) {
        if (dependente == NULL) {
            // É um titular
            printf("\n✅ TITULAR ENCONTRADO:\n");
            printf("Nome: %s\n", titular->nome);
            printf("CPF: %s\n", titular->cpf);
            printf("Idade: %d anos\n", titular->idade);
            printf("Situação: %s\n", situacaoParaString(titular->situacao));
            printf("Dependentes: %d\n", tamanhoLista(titular->listaDependentes));
        } else {
            // É um dependente
            printf("\n✅ DEPENDENTE ENCONTRADO:\n");
            printf("Nome: %s\n", dependente->nome);
            printf("CPF: %s\n", dependente->cpf);
            printf("Idade: %d anos\n", dependente->idade);
            printf("Situação: %s\n", situacaoParaString(dependente->situacao));
            printf("Parentesco: %s\n", parentescoParaString(dependente->grauParentesco));
            printf("Titular: %s (CPF: %s)\n", titular->nome, titular->cpf);
        }
    } else {
        printf("❌ Conveniado não encontrado!\n");
    }
}

void menuExibirDependentes(SistemaSeguros* sistema) {
    char cpf[MAX_CPF];
    
    printf("\n--- EXIBIR DEPENDENTES ---\n");
    printf("CPF do Titular: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    
    if (!validarCPF(cpf)) {
        printf("❌ CPF inválido!\n");
        return;
    }
    
    exibirDependentesTitular(sistema, cpf);
}

void menuExcluirDependente(SistemaSeguros* sistema) {
    char cpfTitular[MAX_CPF];
    char cpfDependente[MAX_CPF];
    
    printf("\n--- EXCLUIR DEPENDENTE ---\n");
    printf("CPF do Titular: ");
    fgets(cpfTitular, sizeof(cpfTitular), stdin);
    cpfTitular[strcspn(cpfTitular, "\n")] = 0;
    
    printf("CPF do Dependente: ");
    fgets(cpfDependente, sizeof(cpfDependente), stdin);
    cpfDependente[strcspn(cpfDependente, "\n")] = 0;
    
    if (!validarCPF(cpfTitular) || !validarCPF(cpfDependente)) {
        printf("❌ CPF inválido!\n");
        return;
    }
    
    if (excluirDependente(sistema, cpfTitular, cpfDependente)) {
        printf("✅ Dependente excluído com sucesso!\n");
    } else {
        printf("❌ Erro ao excluir dependente. Verifique os CPFs informados.\n");
    }
}

void menuExcluirTitular(SistemaSeguros* sistema) {
    char cpf[MAX_CPF];
    
    printf("\n--- EXCLUIR TITULAR ---\n");
    printf("CPF do Titular: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    
    if (!validarCPF(cpf)) {
        printf("❌ CPF inválido!\n");
        return;
    }
    
    printf("⚠️  ATENÇÃO: Esta operação também excluirá todos os dependentes deste titular.\n");
    printf("Deseja continuar? (s/N): ");
    
    char confirmacao;
    scanf("%c", &confirmacao);
    limparBuffer();
    
    if (confirmacao == 's' || confirmacao == 'S') {
        if (excluirTitular(sistema, cpf)) {
            printf("✅ Titular e seus dependentes excluídos com sucesso!\n");
        } else {
            printf("❌ Erro ao excluir titular. Verifique o CPF informado.\n");
        }
    } else {
        printf("❌ Operação cancelada.\n");
    }
}

void menuEstatisticas(SistemaSeguros* sistema) {
    printf("\n--- ESTATÍSTICAS DO SISTEMA ---\n");
    printf("Total de Titulares: %d\n", sistema->totalTitulares);
    printf("Total de Dependentes: %d\n", sistema->totalDependentes);
    printf("Total de Conveniados: %d\n", sistema->totalTitulares + sistema->totalDependentes);
}

void executarSistema() {
    limparTela();
    
    SistemaSeguros* sistema = inicializarSistema();
    
    if (sistema == NULL) {
        printf("❌ Erro ao inicializar o sistema!\n");
        return;
    }
    
    printf("🏥 Sistema de Seguros inicializado com sucesso!\n");
    
    int opcao;
    
    do {
        exibirMenu();
        
        if (scanf("%d", &opcao) != 1) {
            printf("❌ Opção inválida!\n");
            limparBuffer();
            continue;
        }
        limparBuffer();
        
        switch (opcao) {
            case 1:
                menuInserirTitular(sistema);
                break;
            case 2:
                menuInserirDependente(sistema);
                break;
            case 3:
                menuBuscarConveniado(sistema);
                break;
            case 4:
                exibirTodosConveniados(sistema);
                break;
            case 5:
                menuExibirDependentes(sistema);
                break;
            case 6:
                exibirTitularesInadimplentes(sistema);
                break;
            case 7:
                menuExcluirDependente(sistema);
                break;
            case 8:
                menuExcluirTitular(sistema);
                break;
            case 9:
                menuEstatisticas(sistema);
                break;
            case 0:
                printf("👋 Encerrando sistema...\n");
                break;
            default:
                printf("❌ Opção inválida! Tente novamente.\n");
                break;
        }
        
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
            limparTela();
        }
        
    } while (opcao != 0);
    
    destruirSistema(sistema);
    printf("✅ Sistema encerrado com sucesso!\n");
}

int main() {
    executarSistema();
    return 0;
}
