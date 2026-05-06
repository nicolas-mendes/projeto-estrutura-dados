#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================= STRUCTS =================

// Tipo Elemento (Cada dado de uma Matriz_Lista (Matriz Esparsa))
typedef struct elemento
{
    float dado;
    int l, c; // linha e coluna do elemento, que deve respeitar o limite lin e col da matriz
    struct elemento *prox;
} Elemento;

// Tipo Matriz_Lista (Como a matriz está representada na lista)
typedef struct matriz
{
    int id;
    char nome[50]; // NOVA VARIAVEL: Nome de identificacao automatica da matriz
    int lin, col;  // limite de l e c do elemento
    Elemento *prim;
    struct matriz *prox;
} Matriz_Lista;

// Criação do tipo OpcaoMenu (Apenas para organização do menu de opções)
typedef struct
{
    char titulo[50];
    void (*funcao)(Matriz_Lista **);
} OpcaoMenu;

// ================= FUNÇÕES =================

// CRIAÇÃO DE TDA (alocando espaço na memória)

// Cria um elemento para uma Matriz_Lista
Elemento *cria_elem()
{
    Elemento *p;
    p = (Elemento *)malloc(sizeof(Elemento));
    if (!p)
    {
        printf("Problema de alocacao");
        exit(0);
    }
    return p;
}

// Cria uma Matriz_Lista para a Lista de Matrizes
Matriz_Lista *cria_matriz()
{
    Matriz_Lista *p;
    p = (Matriz_Lista *)malloc(sizeof(Matriz_Lista));
    if (!p)
    {
        printf("Problema de alocacao");
        exit(0);
    }
    return p;
}

// INSERÇÃO DE TDA

// Insere um novo Elemento em um Matriz_Lista (Matriz Esparsa)
void insere_elemento(Elemento **N, float dado, int l, int c)
{
    Elemento *novo_e, *aux;
    novo_e = cria_elem();
    novo_e->dado = dado;
    novo_e->l = l;
    novo_e->c = c;
    novo_e->prox = NULL;
    if (*N == NULL)
    {
        *N = novo_e;
    }
    else
    {
        aux = *N;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo_e;
    }
}

// IMPRESSÃO DE TDA

// Imprime os dados de uma matriz no terminal
void imprime_matriz(Matriz_Lista *matriz)
{
    int i, j;
    Elemento *aux;
    int achou;

    printf("\n--- Exibindo Matriz %02d | %s (%dx%d) ---\n", matriz->id, matriz->nome, matriz->lin, matriz->col);
    printf("----------------------------------------------------\n");

    // Varre todas as posicoes possiveis baseadas nas dimensoes da matriz
    for (i = 0; i < matriz->lin; i++)
    {
        for (j = 0; j < matriz->col; j++)
        {
            achou = 0;
            aux = matriz->prim;

            while (aux != NULL)
            {
                if (aux->l == i && aux->c == j)
                {
                    printf("%8.2f ", aux->dado);
                    achou = 1;
                    break;
                }
                aux = aux->prox;
            }

            // Se nao achou o elemento na lista encadeada, imprime 0
            if (!achou)
            {
                printf("%8.2f ", 0.0);
            }
        }
        printf("\n");
    }
    printf("----------------------------------------------------\n\n");
}

// Imprime apenas a diagonal principal de uma matriz
void imprime_diagonal_principal(Matriz_Lista *matriz)
{
    int i, j;
    Elemento *aux;
    int achou;

    printf("\n--- Exibindo Diagonal Principal (%s) ---\n", matriz->nome);
    printf("----------------------------------------------------\n");

    for (i = 0; i < matriz->lin; i++)
    {
        for (j = 0; j < matriz->col; j++)
        {
            achou = 0;
            aux = matriz->prim;

            while (aux != NULL)
            {
                if (aux->l == i && aux->c == j && i == j)
                {
                    printf("%8.2f ", aux->dado);
                    achou = 1;
                    break;
                }
                aux = aux->prox;
            }

            if (!achou)
            {
                if (i == j)
                {
                    printf("%8.2f ", 0.0);
                }
                else
                {
                    printf("%8s", "");
                }
            }
        }
        printf("\n");
    }
    printf("----------------------------------------------------\n\n");
}

// ================= OPERAÇÕES MATEMÁTICAS =================

// Realiza a soma de duas matrizes, salva na lista e imprime
void gera_soma_matrizes(Matriz_Lista **lista, Matriz_Lista *m1, Matriz_Lista *m2)
{
    if (m1->lin != m2->lin || m1->col != m2->col)
    {
        printf("\nERRO MATEMATICO: As matrizes possuem ordens diferentes e nao podem ser somadas!\n\n");
        return;
    }

    Matriz_Lista *nova_m = cria_matriz();
    nova_m->lin = m1->lin;
    nova_m->col = m1->col;
    nova_m->prim = NULL;
    nova_m->prox = NULL;

    Matriz_Lista *aux_lista = *lista;
    while (aux_lista->prox != NULL)
    {
        aux_lista = aux_lista->prox;
    }
    aux_lista->prox = nova_m;
    nova_m->id = aux_lista->id + 1;

    // Gerando o nome padronizado
    sprintf(nova_m->nome, "matriz_soma_%d_%d", m1->id, m2->id);

    int i, j;
    Elemento *aux_e;
    float val1, val2, soma;

    for (i = 0; i < m1->lin; i++)
    {
        for (j = 0; j < m1->col; j++)
        {
            val1 = 0.0;
            val2 = 0.0;

            aux_e = m1->prim;
            while (aux_e != NULL)
            {
                if (aux_e->l == i && aux_e->c == j)
                {
                    val1 = aux_e->dado;
                    break;
                }
                aux_e = aux_e->prox;
            }

            aux_e = m2->prim;
            while (aux_e != NULL)
            {
                if (aux_e->l == i && aux_e->c == j)
                {
                    val2 = aux_e->dado;
                    break;
                }
                aux_e = aux_e->prox;
            }

            soma = val1 + val2;

            // Só armazena o resultado se for diferente de 0
            if (soma != 0.0)
            {
                insere_elemento(&(nova_m->prim), soma, i, j);
            }
        }
    }

    printf("\nOperacao concluida com sucesso! Novo ID Gerado: %d\n", nova_m->id);
    imprime_matriz(nova_m);
}

// Realiza a subtracao de duas matrizes, salva na lista e imprime
void gera_subtracao_matrizes(Matriz_Lista **lista, Matriz_Lista *m1, Matriz_Lista *m2)
{
    if (m1->lin != m2->lin || m1->col != m2->col)
    {
        printf("\nERRO MATEMATICO: As matrizes possuem ordens diferentes e nao podem ser subtraidas!\n\n");
        return;
    }

    Matriz_Lista *nova_m = cria_matriz();
    nova_m->lin = m1->lin;
    nova_m->col = m1->col;
    nova_m->prim = NULL;
    nova_m->prox = NULL;

    Matriz_Lista *aux_lista = *lista;
    while (aux_lista->prox != NULL)
    {
        aux_lista = aux_lista->prox;
    }
    aux_lista->prox = nova_m;
    nova_m->id = aux_lista->id + 1;

    // Gerando o nome padronizado
    sprintf(nova_m->nome, "matriz_subtracao_%d_%d", m1->id, m2->id);

    int i, j;
    Elemento *aux_e;
    float val1, val2, subtracao;

    for (i = 0; i < m1->lin; i++)
    {
        for (j = 0; j < m1->col; j++)
        {
            val1 = 0.0;
            val2 = 0.0;

            aux_e = m1->prim;
            while (aux_e != NULL)
            {
                if (aux_e->l == i && aux_e->c == j)
                {
                    val1 = aux_e->dado;
                    break;
                }
                aux_e = aux_e->prox;
            }

            aux_e = m2->prim;
            while (aux_e != NULL)
            {
                if (aux_e->l == i && aux_e->c == j)
                {
                    val2 = aux_e->dado;
                    break;
                }
                aux_e = aux_e->prox;
            }

            subtracao = val1 - val2;

            // Só armazena o resultado se for diferente de 0
            if (subtracao != 0.0)
            {
                insere_elemento(&(nova_m->prim), subtracao, i, j);
            }
        }
    }

    printf("\nOperacao concluida com sucesso! Novo ID Gerado: %d\n", nova_m->id);
    imprime_matriz(nova_m);
}

// Gera a matriz transposta de uma matriz, salva na lista e imprime
void gera_transposta(Matriz_Lista **lista, Matriz_Lista *orig)
{
    Matriz_Lista *nova_m = cria_matriz();

    nova_m->lin = orig->col;
    nova_m->col = orig->lin;
    nova_m->prim = NULL;
    nova_m->prox = NULL;

    Matriz_Lista *aux_lista = *lista;
    while (aux_lista->prox != NULL)
    {
        aux_lista = aux_lista->prox;
    }
    aux_lista->prox = nova_m;
    nova_m->id = aux_lista->id + 1;

    // Gerando o nome padronizado
    sprintf(nova_m->nome, "matriz_transposta_%d", orig->id);

    Elemento *aux_e = orig->prim;
    while (aux_e != NULL)
    {
        // Envia l para c, e c para l
        insere_elemento(&(nova_m->prim), aux_e->dado, aux_e->c, aux_e->l);
        aux_e = aux_e->prox;
    }

    printf("\nOperacao concluida com sucesso! Novo ID Gerado: %d\n", nova_m->id);
    imprime_matriz(nova_m);
}

// Busca determinado elemento dentro de uma matriz
void busca_dados(Matriz_Lista *matriz_vez)
{
    int continuar = 1;
    while (continuar)
    {
        Elemento *aux;
        aux = matriz_vez->prim;
        float dado;
        int encontrado = 0;

        printf("\nDigite o dado que deseja buscar na matriz: ");
        scanf("%f", &dado);

        while (aux != NULL)
        {
            if (aux->dado == dado)
            {
                printf("\nDado %.2f encontrado na linha %d coluna %d\n", dado, aux->l, aux->c);
                encontrado = 1;
            }
            aux = aux->prox;
        }

        if (!encontrado)
        {
            printf("\nDado nao encontrado na matriz.\n");
        }

        do
        {
            printf("\nContinuar a buscar dados? \n[1] Continuar \n[0] Sair \nOpcao: ");
            scanf("%d", &continuar);
        } while (continuar < 0 || continuar > 1);
    }
}

// Realiza a multiplicacaode duas matrizes, salva na lista e imprime
void gera_multiplicacao_matrizes(Matriz_Lista **lista, Matriz_Lista *m1, Matriz_Lista *m2)
{
    // Verificacao matematica: Colunas da M1 == Linhas da M2
    if (m1->col != m2->lin)
    {
        printf("\nERRO MATEMATICO: O numero de colunas da 1a matriz deve ser igual ao numero de linhas da 2a matriz!\n");
        printf("Matriz %02d (%dx%d) vs Matriz %02d (%dx%d)\n\n", m1->id, m1->lin, m1->col, m2->id, m2->lin, m2->col);
        return;
    }

    // Criando o container do resultado (Dimensoes: Linhas da M1 x Colunas da M2)
    Matriz_Lista *nova_m = cria_matriz();
    nova_m->lin = m1->lin;
    nova_m->col = m2->col;
    nova_m->prim = NULL;
    nova_m->prox = NULL;

    Matriz_Lista *aux_lista = *lista;
    while (aux_lista->prox != NULL)
    {
        aux_lista = aux_lista->prox;
    }
    aux_lista->prox = nova_m;
    nova_m->id = aux_lista->id + 1;

    // Gerando o nome padronizado
    sprintf(nova_m->nome, "matriz_produto_%d_%d", m1->id, m2->id);

    int i, j, k;
    Elemento *aux_e;
    float val1, val2, soma_produto;

    for (i = 0; i < nova_m->lin; i++)
    {
        for (j = 0; j < nova_m->col; j++)
        {
            soma_produto = 0.0;

            for (k = 0; k < m1->col; k++)
            {
                val1 = 0.0;
                val2 = 0.0;

                // Busca o elemento na Matriz 1 (Linha i, Coluna k)
                aux_e = m1->prim;
                while (aux_e != NULL)
                {
                    if (aux_e->l == i && aux_e->c == k)
                    {
                        val1 = aux_e->dado;
                        break;
                    }
                    aux_e = aux_e->prox;
                }

                // Se val1 for zero, a multiplicacao por val2 será sempre zero.
                if (val1 != 0.0)
                {
                    // Busca o elemento na Matriz 2 (Linha k, Coluna j)
                    aux_e = m2->prim;
                    while (aux_e != NULL)
                    {
                        if (aux_e->l == k && aux_e->c == j)
                        {
                            val2 = aux_e->dado;
                            break;
                        }
                        aux_e = aux_e->prox;
                    }

                    soma_produto += (val1 * val2);
                }
            }

            if (soma_produto != 0.0)
            {
                insere_elemento(&(nova_m->prim), soma_produto, i, j);
            }
        }
    }

    printf("\nOperacao concluida com sucesso! Novo ID Gerado: %d\n", nova_m->id);
    imprime_matriz(nova_m);
}

// ================= CHAMADAS MENU =================

// Valida os dados de entrada de um elemento e depois chama a inserção
void menu_insere_elemento(Matriz_Lista *matriz_vez, int max_l, int max_c)
{
    int continuar = 1;
    while (continuar)
    {
        float dado;
        int l, c;
        printf("\nDado a ser inserido: ");
        scanf("%f", &dado);

        if (dado == 0)
        {
            printf("Apenas dados diferentes de zero sao alocados na matriz.\n");
        }
        else
        {
            do
            {
                printf("\nLinha de input (0 a %d): ", max_l - 1);
                scanf("%d", &l);
                if (l >= max_l || l < 0)
                    printf("Linha nao disponivel. Tente Novamente\n");
            } while (l >= max_l || l < 0);

            do
            {
                printf("\nColuna de input (0 a %d): ", max_c - 1);
                scanf("%d", &c);
                if (c >= max_c || c < 0)
                    printf("Coluna nao disponivel. Tente Novamente\n");
            } while (c >= max_c || c < 0);

            insere_elemento(&(matriz_vez->prim), dado, l, c);
            printf("Elemento inserido com sucesso!\n");
            printf("Dado: %.2f | Linha %d Coluna %d\n", dado, l, c);
        }

        do
        {
            printf("\nContinuar a inserir dados? \n[1] Continuar \n[0] Sair \nOpcao: ");
            scanf("%d", &continuar);
        } while (continuar < 0 || continuar > 1);
    }
}

// Inserção da matriz na lista
void menu_insere_matriz(Matriz_Lista **lista)
{
    Matriz_Lista *nova_m, *aux;
    nova_m = cria_matriz();
    nova_m->prox = NULL;
    nova_m->prim = NULL;

    int continuar;

    printf("\nDimensoes da Matriz\n");
    printf("Linhas: ");
    scanf("%d", &nova_m->lin);
    printf("Colunas: ");
    scanf("%d", &nova_m->col);
    printf("\nNova Matriz Inicializada com Sucesso.\n");

    if (*lista == NULL)
    {
        *lista = nova_m;
        nova_m->id = 1;
    }
    else
    {
        aux = *lista;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = nova_m;
        nova_m->id = aux->id + 1;
    }

    sprintf(nova_m->nome, "matriz_manual_%d", nova_m->id);

    printf("Nova Matriz Adicionada a Lista! | ID : %d | Nome : %s\n", nova_m->id, nova_m->nome);

    do
    {
        printf("\nDeseja inserir elementos? \n[1] Continuar \n[0] Sair \nOpcao: ");
        scanf("%d", &continuar);
    } while (continuar < 0 || continuar > 1);

    if (continuar)
    {
        menu_insere_elemento(nova_m, nova_m->lin, nova_m->col);
    }
}

// Exibe as matrizes disponiveis
void menu_imprime_matriz(Matriz_Lista **lista)
{
    if (*lista == NULL)
    {
        printf("\nNenhuma matriz foi inicializada ainda!\n\n");
        return;
    }

    Matriz_Lista *aux = *lista;
    int escolha;
    int encontrada = 0;

    printf("\n====== MATRIZES DISPONIVEIS ======\n");
    while (aux != NULL)
    {
        printf("[%d] - Matriz %02d | %s (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->nome, aux->lin, aux->col);
        aux = aux->prox;
    }
    printf("[0] - Voltar\n");

    printf("Escolha a matriz que deseja imprimir: ");
    scanf("%d", &escolha);

    if (escolha == 0)
        return;

    aux = *lista;
    while (aux != NULL)
    {
        if (aux->id == escolha)
        {
            imprime_matriz(aux);
            encontrada = 1;
            break;
        }
        aux = aux->prox;
    }

    if (!encontrada)
        printf("Opcao invalida!\n\n");
}

// Menu de multiplicacao com verificacao de cache
void menu_multiplicacao_matrizes(Matriz_Lista **lista)
{
    if (*lista == NULL)
    {
        printf("\nNenhuma matriz foi inicializada ainda!\n\n");
        return;
    }

    Matriz_Lista *aux = *lista;
    Matriz_Lista *m1 = NULL, *m2 = NULL;
    int id1, id2;

    printf("\n====== MATRIZES DISPONIVEIS ======\n");
    while (aux != NULL)
    {
        printf("[%d] - Matriz %02d | %s (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->nome, aux->lin, aux->col);
        aux = aux->prox;
    }
    printf("[0] - Voltar\n");

    printf("\nEscolha o ID da Primeira Matriz (Esquerda da Equacao): ");
    scanf("%d", &id1);
    if (id1 == 0)
        return;

    printf("Escolha o ID da Segunda Matriz (Direita da Equacao): ");
    scanf("%d", &id2);
    if (id2 == 0)
        return;

    char nome_busca[50];
    sprintf(nome_busca, "matriz_produto_%d_%d", id1, id2);

    aux = *lista;
    while (aux != NULL)
    {
        if (strcmp(aux->nome, nome_busca) == 0)
        {
            printf("\nOperacao ja calculada anteriormente! Exibindo matriz salva no cache...\n");
            imprime_matriz(aux);
            return;
        }
        aux = aux->prox;
    }

    // Busca os ponteiros originais para o calculo
    aux = *lista;
    while (aux != NULL)
    {
        if (aux->id == id1)
            m1 = aux;
        if (aux->id == id2)
            m2 = aux;
        aux = aux->prox;
    }

    if (m1 != NULL && m2 != NULL)
    {
        gera_multiplicacao_matrizes(lista, m1, m2);
    }
    else
    {
        printf("Um ou ambos os IDs informados sao invalidos!\n\n");
    }
}

// Menu de Soma com verificacao de Cache
void menu_soma_matrizes(Matriz_Lista **lista)
{
    if (*lista == NULL)
    {
        printf("\nNenhuma matriz foi inicializada ainda!\n\n");
        return;
    }

    Matriz_Lista *aux = *lista;
    Matriz_Lista *m1 = NULL, *m2 = NULL;
    int id1, id2;

    printf("\n====== MATRIZES DISPONIVEIS ======\n");
    while (aux != NULL)
    {
        printf("[%d] - Matriz %02d | %s (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->nome, aux->lin, aux->col);
        aux = aux->prox;
    }
    printf("[0] - Voltar\n");

    printf("\nEscolha o ID da Primeira Matriz: ");
    scanf("%d", &id1);
    if (id1 == 0)
        return;

    printf("Escolha o ID da Segunda Matriz: ");
    scanf("%d", &id2);
    if (id2 == 0)
        return;

    char nome_busca_1[50], nome_busca_2[50];
    sprintf(nome_busca_1, "matriz_soma_%d_%d", id1, id2);
    sprintf(nome_busca_2, "matriz_soma_%d_%d", id2, id1); // Em soma, ordem nao altera o resultado

    aux = *lista;
    while (aux != NULL)
    {
        if (strcmp(aux->nome, nome_busca_1) == 0 || strcmp(aux->nome, nome_busca_2) == 0)
        {
            printf("\nOperacao ja calculada anteriormente! Exibindo matriz salva no cache...\n");
            imprime_matriz(aux);
            return;
        }
        aux = aux->prox;
    }

    aux = *lista;
    while (aux != NULL)
    {
        if (aux->id == id1)
            m1 = aux;
        if (aux->id == id2)
            m2 = aux;
        aux = aux->prox;
    }

    if (m1 != NULL && m2 != NULL)
    {
        gera_soma_matrizes(lista, m1, m2);
    }
    else
    {
        printf("Um ou ambos os IDs informados sao invalidos!\n\n");
    }
}

// Menu de subtracao com verificacao de cache
void menu_subtracao_matrizes(Matriz_Lista **lista)
{
    if (*lista == NULL)
    {
        printf("\nNenhuma matriz foi inicializada ainda!\n\n");
        return;
    }

    Matriz_Lista *aux = *lista;
    Matriz_Lista *m1 = NULL, *m2 = NULL;
    int id1, id2;

    printf("\n====== MATRIZES DISPONIVEIS ======\n");
    while (aux != NULL)
    {
        printf("[%d] - Matriz %02d | %s (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->nome, aux->lin, aux->col);
        aux = aux->prox;
    }
    printf("[0] - Voltar\n");

    printf("\nEscolha o ID da Primeira Matriz: ");
    scanf("%d", &id1);
    if (id1 == 0)
        return;

    printf("Escolha o ID da Segunda Matriz: ");
    scanf("%d", &id2);
    if (id2 == 0)
        return;

    char nome_busca[50];
    sprintf(nome_busca, "matriz_subtracao_%d_%d", id1, id2);

    aux = *lista;
    while (aux != NULL)
    {
        if (strcmp(aux->nome, nome_busca) == 0)
        {
            printf("\nOperacao ja calculada anteriormente! Exibindo matriz salva no cache...\n");
            imprime_matriz(aux);
            return;
        }
        aux = aux->prox;
    }

    aux = *lista;
    while (aux != NULL)
    {
        if (aux->id == id1)
            m1 = aux;
        if (aux->id == id2)
            m2 = aux;
        aux = aux->prox;
    }

    if (m1 != NULL && m2 != NULL)
    {
        gera_subtracao_matrizes(lista, m1, m2);
    }
    else
    {
        printf("Um ou ambos os IDs informados sao invalidos!\n\n");
    }
}

// Menu Transposta com verificacao de cache
void menu_gera_transposta(Matriz_Lista **lista)
{
    if (*lista == NULL)
    {
        printf("\nNenhuma matriz foi inicializada ainda!\n\n");
        return;
    }

    Matriz_Lista *aux = *lista;
    int escolha;
    int encontrada = 0;

    printf("\n====== MATRIZES DISPONIVEIS ======\n");
    while (aux != NULL)
    {
        printf("[%d] - Matriz %02d | %s (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->nome, aux->lin, aux->col);
        aux = aux->prox;
    }
    printf("[0] - Voltar\n");

    printf("Escolha a matriz que deseja gerar a transposta: ");
    scanf("%d", &escolha);

    if (escolha == 0)
        return;

    char nome_busca[50];
    sprintf(nome_busca, "matriz_transposta_%d", escolha);

    aux = *lista;
    while (aux != NULL)
    {
        if (strcmp(aux->nome, nome_busca) == 0)
        {
            printf("\nOperacao ja calculada anteriormente! Exibindo matriz salva no cache...\n");
            imprime_matriz(aux);
            return;
        }
        aux = aux->prox;
    }

    aux = *lista;
    while (aux != NULL)
    {
        if (aux->id == escolha)
        {
            gera_transposta(lista, aux);
            encontrada = 1;
            break;
        }
        aux = aux->prox;
    }

    if (!encontrada)
        printf("Opcao invalida!\n\n");
}

void menu_imprime_diagonal_principal(Matriz_Lista **lista)
{
    if (*lista == NULL)
    {
        printf("\nNenhuma matriz foi inicializada ainda!\n\n");
        return;
    }

    Matriz_Lista *aux = *lista;
    int escolha;
    int quadradaencontrada = 0;
    int encontrada = 0;

    printf("\n====== MATRIZES DISPONIVEIS ======\n");
    printf("====== OBS: A Diagonal Principal deriva apenas de matrizes quadradas (NxN)\n");
    while (aux != NULL)
    {
        if (aux->lin == aux->col)
        {
            printf("[%d] - Matriz %02d | %s (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->nome, aux->lin, aux->col);
            quadradaencontrada = 1;
        }
        aux = aux->prox;
    }

    printf("[0] - Voltar\n");

    if (!quadradaencontrada)
    {
        printf("Nao ha matrizes disponiveis para esta escolha.\n");
        return;
    }

    printf("Escolha a matriz que deseja imprimir: ");
    scanf("%d", &escolha);

    if (escolha == 0)
        return;

    aux = *lista;
    while (aux != NULL)
    {
        if (aux->id == escolha)
        {
            if (aux->lin == aux->col)
            {
                imprime_diagonal_principal(aux);
                encontrada = 1;
                break;
            }
        }
        aux = aux->prox;
    }

    if (!encontrada)
        printf("Opcao invalida!\n\n");
}

// Recebe uma matriz do usuario e chama a função busca_matriz
void menu_busca_dados(Matriz_Lista **lista)
{
    if (*lista == NULL)
    {
        printf("\nNenhuma matriz foi inicializada ainda!\n\n");
        return;
    }

    Matriz_Lista *aux = *lista;
    int escolha;
    int encontrada = 0;

    printf("\n====== MATRIZES DISPONIVEIS ======\n");
    while (aux != NULL)
    {
        printf("[%d] - Matriz %02d | %s (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->nome, aux->lin, aux->col);
        aux = aux->prox;
    }
    printf("[0] - Voltar\n");

    printf("Escolha a matriz que deseja buscar os dados: ");
    scanf("%d", &escolha);

    if (escolha == 0)
        return;

    aux = *lista;
    while (aux != NULL)
    {
        if (aux->id == escolha)
        {
            busca_dados(aux);
            encontrada = 1;
            break;
        }
        aux = aux->prox;
    }

    if (!encontrada)
        printf("Opcao invalida!\n\n");
}

// Menu interativo para exclusao
void menu_exclui_matriz(Matriz_Lista **lista)
{
    if (*lista == NULL)
    {
        printf("\nNenhuma matriz foi inicializada ainda!\n\n");
        return;
    }

    Matriz_Lista *aux = *lista;
    int escolha;
    int encontrada = 0;

    printf("\n====== MATRIZES DISPONIVEIS ======\n");
    while (aux != NULL)
    {
        printf("[%d] - Matriz %02d | %s (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->nome, aux->lin, aux->col);
        aux = aux->prox;
    }
    printf("[0] - Voltar\n");

    printf("\nEscolha o ID da matriz que deseja excluir do sistema: ");
    scanf("%d", &escolha);

    if (escolha == 0)
        return;

    aux = *lista;
    while (aux != NULL)
    {
        if (aux->id == escolha)
        {
            encontrada = 1;
            break;
        }
        aux = aux->prox;
    }

    if (encontrada)
    {
        exclui_matriz(lista, escolha);
    }
    else
    {
        printf("\nOpcao invalida! ID nao encontrado.\n\n");
    }
}

// Menu para inserir novos elementos em uma matriz ja existente
void menu_inserir_dados_matriz(Matriz_Lista **lista)
{
    if (*lista == NULL)
    {
        printf("\nNenhuma matriz foi inicializada ainda!\n\n");
        return;
    }

    Matriz_Lista *aux = *lista;
    int escolha;
    int encontrada = 0;

    printf("\n====== MATRIZES DISPONIVEIS ======\n");
    while (aux != NULL)
    {
        printf("[%d] - Matriz %02d | %s (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->nome, aux->lin, aux->col);
        aux = aux->prox;
    }
    printf("[0] - Voltar\n");

    printf("\nEscolha o ID da matriz para inserir novos dados: ");
    scanf("%d", &escolha);

    if (escolha == 0)
        return;

    aux = *lista;
    while (aux != NULL)
    {
        if (aux->id == escolha)
        {
            encontrada = 1;
            printf("\n--- Inserindo dados na Matriz %02d (%dx%d) ---\n", aux->id, aux->lin, aux->col);

            // Aqui esta o reaproveitamento de comportamento!
            // Chama a mesma funcao usada na criacao da matriz
            menu_insere_elemento(aux, aux->lin, aux->col);
            break;
        }
        aux = aux->prox;
    }

    if (!encontrada)
    {
        printf("\nOpcao invalida! ID nao encontrado.\n\n");
    }
}

// ================= GERENCIAMENTO DE MEMÓRIA (EXCLUSÃO) =================

// Libera todos os elementos de dentro de uma matriz especifica
void libera_elementos(Elemento *prim)
{
    Elemento *aux = prim;
    Elemento *prox;

    while (aux != NULL)
    {
        prox = aux->prox;
        free(aux);
        aux = prox;
    }
}

// Remove a matriz da lista principal e deleta seus elementos
void exclui_matriz(Matriz_Lista **lista, int id_excluir)
{
    Matriz_Lista *aux = *lista;
    Matriz_Lista *ant = NULL;

    while (aux != NULL && aux->id != id_excluir)
    {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL)
        return;

    libera_elementos(aux->prim);

    if (ant == NULL)
    {
        *lista = aux->prox;
    }
    else
    {
        ant->prox = aux->prox;
    }

    free(aux);
    printf("\nMatriz %02d excluida com sucesso e memoria totalmente liberada!\n", id_excluir);
}

// ================= UTILITÁRIOS DE TELA =================

// Limpa a tela
void limpa_tela()
{
    system("cls");
}

// Pausa a tela até o usuário apertar ENTER
void pausa_tela()
{
    printf("\n[Pressione ENTER para voltar ao menu principal]");

    // Limpa o buffer do teclado (restos do scanf anterior)
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    getchar();
}

// ================= INICIALIZAÇÃO =================

// Inicializa a lista que armazena todas as Matrizes da sessão
void inicializa_lista(Matriz_Lista **N)
{
    *N = NULL;
}

// ================= MAIN =================

int main()
{
    Matriz_Lista *lista; // ponteiro externo para Lista de Matrizes

    inicializa_lista(&lista);

    OpcaoMenu menu[] = {
        {"Inicializar Nova Matriz", menu_insere_matriz},
        {"Inserir Dados em Matriz Existente", menu_inserir_dados_matriz},
        {"Imprimir Matrizes", menu_imprime_matriz},
        {"Gerar/Imprimir Transpostas", menu_gera_transposta},
        {"Imprimir Diagonal Principal", menu_imprime_diagonal_principal},
        {"Somar Matrizes", menu_soma_matrizes},
        {"Subtrair Matrizes", menu_subtracao_matrizes},
        {"Multiplicar Matrizes", menu_multiplicacao_matrizes},
        {"Buscar Dados", menu_busca_dados},
        {"Excluir Matriz (Liberar Memoria)", menu_exclui_matriz}};

    int quantidadeOpcoes = sizeof(menu) / sizeof(menu[0]);
    int escolha;
    int i;

    while (1)
    {
        limpa_tela();

        printf("\n======== MENU PRINCIPAL ========\n");

        for (i = 0; i < quantidadeOpcoes; i++)
        {
            printf("[%d] - %s\n", i + 1, menu[i].titulo);
        }
        printf("[%d] - Sair\n", quantidadeOpcoes + 1);
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        if (escolha > 0 && escolha <= quantidadeOpcoes)
        {
            menu[escolha - 1].funcao(&lista);
            pausa_tela();
        }
        else if (escolha == quantidadeOpcoes + 1)
        {
            printf("Saindo... \n");
            break;
        }
        else
        {
            printf("Opcao Invalida!\n");
            pausa_tela();
        }
    }

    return 0;
}