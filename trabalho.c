#include <stdio.h>
#include <stdlib.h>

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
	int lin, col; // limite de l e c do elemento
	Elemento *prim;
	struct matriz *prox;
} Matriz_Lista;

// typedef struct Bloco
// {
// 	int dado;
// 	struct Bloco *prox;
// } Nodo;

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

	printf("Elemento inserido com sucesso!\n");
	printf("Dado: %.2f | Linha %d Coluna %d\n", dado, l, c);
}

// IMPRESSÃO DE TDA

// Imprime os dados de uma matriz em formato de grade no terminal
void imprime_matriz(Matriz_Lista *matriz)
{
	int i, j;
	Elemento *aux;
	int achou;

	printf("\n--- Exibindo Matriz %02d (%dx%d) ---\n", matriz->id, matriz->lin, matriz->col);
	printf("\n----------------------------------\n");

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
	printf("----------------------------------\n\n");
}

// Imprime apenas a diagonal principal de uma matriz
void imprime_diagonal_principal(Matriz_Lista *matriz)
{
	int i, j;
	Elemento *aux;
	int achou;

	printf("\n--- Exibindo Diagonal Principal da Matriz %02d (%dx%d) ---\n", matriz->id, matriz->lin, matriz->col);
	printf("\n----------------------------------\n");

	// Varre todas as posicoes possiveis baseadas nas dimensoes da matriz
	for (i = 0; i < matriz->lin; i++)
	{
		for (j = 0; j < matriz->col; j++)
		{
			achou = 0;
			aux = matriz->prim;

			while (aux != NULL)
			{
				if (aux->l == i && aux->c == j && i==j)
				{
					printf("%8.2f ", aux->dado);
					achou = 1;
					break;
				}
				aux = aux->prox;
			}

			// Se nao achou o elemento na lista encadeada, ou imprime " " ou 0.00
			if (!achou)
			{
				if (i==j) {
					printf("%8.2f ", 0.0);
				} else {
					printf("%8s", "");
				}
			}
		}
		printf("\n");
	}
	printf("----------------------------------\n\n");
}

// Imprime a matriz escolhida em sua forma transposta
void imprime_transposta(Matriz_Lista *matriz)
{
	int i, j;
	Elemento *aux;
	int achou;

	printf("\n--- Exibindo Transposta da Matriz %02d (%dx%d) ---\n", matriz->id, matriz->lin, matriz->col);
	printf("--- Dimensao Original (%dx%d) | Dimensao Transposta (%dx%d) ---\n", matriz->lin, matriz->col, matriz->col, matriz->lin);
	printf("\n----------------------------------\n");

	// Varre todas as posicoes possiveis baseadas nas dimensoes da matriz
	for (i = 0; i < matriz->col; i++)
	{
		for (j = 0; j < matriz->lin; j++)
		{
			achou = 0;
			aux = matriz->prim;

			while (aux != NULL)
			{
				if (aux->c == i && aux->l == j)
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
	printf("----------------------------------\n\n");
}

// ================= OPERAÇÕES MATEMÁTICAS =================

// Realiza a soma de duas matrizes e imprime o resultado na tela
void imprime_soma_matrizes(Matriz_Lista *m1, Matriz_Lista *m2)
{
	// Validacao matematica estrita: Matrizes precisam ter exatamente as mesmas dimensoes (ordem)
	if (m1->lin != m2->lin || m1->col != m2->col)
	{
		printf("\nERRO MATEMATICO: As matrizes possuem ordens diferentes (dimensoes) e nao podem ser somadas!\n");
		printf("Matriz %02d (%dx%d) vs Matriz %02d (%dx%d)\n\n", m1->id, m1->lin, m1->col, m2->id, m2->lin, m2->col);
		return;
	}

	int i, j;
	Elemento *aux;
	float val1, val2;

	printf("\n--- Exibindo Soma (Matriz %02d + Matriz %02d) ---\n", m1->id, m2->id);

	// Varre as coordenadas possiveis (as dimensoes sao iguais, entao podemos usar as da m1)
	for (i = 0; i < m1->lin; i++)
	{
		for (j = 0; j < m1->col; j++)
		{
			val1 = 0.0;
			val2 = 0.0;

			// Busca o valor para esta coordenada na Matriz 1
			aux = m1->prim;
			while (aux != NULL)
			{
				if (aux->l == i && aux->c == j)
				{
					val1 = aux->dado;
					break;
				}
				aux = aux->prox;
			}

			// Busca o valor para esta coordenada na Matriz 2
			aux = m2->prim;
			while (aux != NULL)
			{
				if (aux->l == i && aux->c == j)
				{
					val2 = aux->dado;
					break;
				}
				aux = aux->prox;
			}

			// Realiza a soma e imprime o resultado no formato da grade
			printf("%8.2f ", val1 + val2);
		}
		printf("\n");
	}
	printf("-------------------------------------------\n\n");
}

// Realiza a subtracao de duas matrizes e imprime o resultado na tela
void imprime_subtracao_matrizes(Matriz_Lista *m1, Matriz_Lista *m2)
{
	// Validacao matematica estrita: Matrizes precisam ter exatamente as mesmas dimensoes (ordem)
	if (m1->lin != m2->lin || m1->col != m2->col)
	{
		printf("\nERRO MATEMATICO: As matrizes possuem ordens diferentes (dimensoes) e nao podem ser somadas!\n");
		printf("Matriz %02d (%dx%d) vs Matriz %02d (%dx%d)\n\n", m1->id, m1->lin, m1->col, m2->id, m2->lin, m2->col);
		return;
	}

	int i, j;
	Elemento *aux;
	float val1, val2;

	printf("\n--- Exibindo Soma (Matriz %02d - Matriz %02d) ---\n", m1->id, m2->id);

	// Varre as coordenadas possiveis (as dimensoes sao iguais, entao podemos usar as da m1)
	for (i = 0; i < m1->lin; i++)
	{
		for (j = 0; j < m1->col; j++)
		{
			val1 = 0.0;
			val2 = 0.0;

			// Busca o valor para esta coordenada na Matriz 1
			aux = m1->prim;
			while (aux != NULL)
			{
				if (aux->l == i && aux->c == j)
				{
					val1 = aux->dado;
					break;
				}
				aux = aux->prox;
			}

			// Busca o valor para esta coordenada na Matriz 2
			aux = m2->prim;
			while (aux != NULL)
			{
				if (aux->l == i && aux->c == j)
				{
					val2 = aux->dado;
					break;
				}
				aux = aux->prox;
			}

			// Realiza a soma e imprime o resultado no formato da grade
			printf("%8.2f ", val1 - val2);
		}
		printf("\n");
	}
	printf("-------------------------------------------\n\n");
}

void busca_dados(Matriz_Lista *matriz_vez) {
	int continuar = 1;
	while (continuar) 
	{
		Elemento *aux;
		aux = matriz_vez->prim;
		float dado;
		int encontrado = 0;
		
		printf("\nDigite o dado que deseja buscar na matriz: ");
		scanf("%f", &dado);

		while (aux!=NULL)
		{
			if (aux->dado==dado) {
				printf("\nDado %.2f encontrado na linha %d coluna %d\n", dado, aux->l, aux->c);
				encontrado = 1;
			}
			aux = aux->prox;
		}

		if (!encontrado)
		{
			printf("\nDado nao encontrado na matriz.\n");
		}

		do {
			printf("\nContinuar a buscar dados? \n[1] Continuar \n[0] Sair \nOpcao: ");
			scanf("%d", &continuar);
			if (continuar<0 || continuar>1) {
				printf("\nOpcao Invalida. Tente Novamente.\n");
			}
		} while (continuar<0 || continuar>1);
		
	}
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

		if (dado==0) {
			printf("Apenas dados diferentes de zero sao alocados na matriz.\n");
		} else {
			do {
				// exibe o limite real (max - 1) conforme a base 0
				printf("\nLinha de input (0 a %d): ", max_l - 1);
				scanf("%d", &l);
				if (l >= max_l || l < 0)
					{
						printf("Linha nao disponivel. (Limites validos: 0 a %d)\n", max_l - 1);
						printf("Tente Novamente\n");
					}
			} while (l >= max_l || l < 0);

			do
			{
				// exibe o limite real (max - 1) conforme a base 0
				printf("\nColuna de input (0 a %d): ", max_c - 1);
				scanf("%d", &c);
				if (c >= max_c || c < 0)
					{
						printf("Coluna nao disponivel. (Limites validos: 0 a %d)\n", max_c - 1);
						printf("Tente Novamente\n");
					}
			} while (c >= max_c || c < 0);

			insere_elemento(&(matriz_vez->prim), dado, l, c);
		}
		

		do {
			printf("\nContinuar a inserir dados? \n[1] Continuar \n[0] Sair \nOpcao: ");
			scanf("%d", &continuar);
			if (continuar<0 || continuar>1) {
				printf("\nOpcao Invalida. Tente Novamente.\n");
			}
		} while (continuar<0 || continuar>1);
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
	printf("Nova Matriz Adicionada a Lista! | ID : %d\n", nova_m->id);

	do {
		printf("\nDeseja inserir elementos? \n[1] Continuar \n[0] Sair \nOpcao: ");
		scanf("%d", &continuar);
		if (continuar<0 || continuar>1) {
			printf("\nOpcao Invalida. Tente Novamente.\n");
		}
	} while (continuar<0 || continuar>1);

	if (continuar) {
		menu_insere_elemento(nova_m, nova_m->lin, nova_m->col);
	}
}

// Exibe as matrizes disponiveis e chama a funcao de impressao da escolhida
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
		printf("[%d] - Matriz %02d (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->lin, aux->col);
		aux = aux->prox;
	}
	printf("[0] - Voltar\n");

	printf("Escolha a matriz que deseja imprimir: ");
	scanf("%d", &escolha);

	if (escolha == 0)
	{
		return;
	}

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
	{
		printf("Opcao invalida!\n\n");
	}
}

// Recebe as duas matrizes do usuario e envia para a funcao de soma
void menu_soma_matrizes(Matriz_Lista **lista)
{
	if (*lista == NULL)
	{
		printf("\nNenhuma matriz foi inicializada ainda!\n\n");
		return;
	}

	Matriz_Lista *aux = *lista;
	Matriz_Lista *m1 = NULL;
	Matriz_Lista *m2 = NULL;
	int id1, id2;

	// Lista as opcoes
	printf("\n====== MATRIZES DISPONIVEIS ======\n");
	while (aux != NULL)
	{
		printf("[%d] - Matriz %02d (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->lin, aux->col);
		aux = aux->prox;
	}
	printf("[0] - Voltar\n");

	printf("\nEscolha o ID da Primeira Matriz: ");
	scanf("%d", &id1);
	if (id1 == 0)
		return;

	printf("Escolha o ID da Segunda Matriz (Pode ser o mesmo ID): ");
	scanf("%d", &id2);
	if (id2 == 0)
		return;

	// Varre a lista uma vez e resgata os ponteiros das matrizes escolhidas
	aux = *lista;
	while (aux != NULL)
	{
		if (aux->id == id1)
			m1 = aux;
		if (aux->id == id2)
			m2 = aux;
		aux = aux->prox;
	}

	// Se achou ambas na lista, tenta somar. Se nao, alerta o usuario
	if (m1 != NULL && m2 != NULL)
	{
		imprime_soma_matrizes(m1, m2);
	}
	else
	{
		printf("Um ou ambos os IDs informados sao invalidos!\n\n");
	}
}

// Recebe as duas matrizes do usuario e envia para a funcao de subtracao
void menu_subtracao_matrizes(Matriz_Lista **lista)
{
	if (*lista == NULL)
	{
		printf("\nNenhuma matriz foi inicializada ainda!\n\n");
		return;
	}

	Matriz_Lista *aux = *lista;
	Matriz_Lista *m1 = NULL;
	Matriz_Lista *m2 = NULL;
	int id1, id2;

	// Lista as opcoes
	printf("\n====== MATRIZES DISPONIVEIS ======\n");
	while (aux != NULL)
	{
		printf("[%d] - Matriz %02d (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->lin, aux->col);
		aux = aux->prox;
	}
	printf("[0] - Voltar\n");

	printf("\nEscolha o ID da Primeira Matriz: ");
	scanf("%d", &id1);
	if (id1 == 0)
		return;

	printf("Escolha o ID da Segunda Matriz (Pode ser o mesmo ID): ");
	scanf("%d", &id2);
	if (id2 == 0)
		return;

	// Varre a lista uma vez e resgata os ponteiros das matrizes escolhidas
	aux = *lista;
	while (aux != NULL)
	{
		if (aux->id == id1)
			m1 = aux;
		if (aux->id == id2)
			m2 = aux;
		aux = aux->prox;
	}

	// Se achou ambas na lista, tenta somar. Se nao, alerta o usuario
	if (m1 != NULL && m2 != NULL)
	{
		imprime_subtracao_matrizes(m1, m2);
	}
	else
	{
		printf("Um ou ambos os IDs informados sao invalidos!\n\n");
	}
}

// Recebe uma matriz do usuário e envia para a função de transposta
void menu_imprime_transposta(Matriz_Lista **lista)
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
		printf("[%d] - Matriz %02d (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->lin, aux->col);
		aux = aux->prox;
	}
	printf("[0] - Voltar\n");

	printf("Escolha a matriz que deseja imprimir: ");
	scanf("%d", &escolha);

	if (escolha == 0)
	{
		return;
	}

	aux = *lista;
	while (aux != NULL)
	{
		if (aux->id == escolha)
		{
			imprime_transposta(aux);
			encontrada = 1;
			break;
		}
		aux = aux->prox;
	}

	if (!encontrada)
	{
		printf("Opcao invalida!\n\n");
	}
}

// Recebe uma matriz quadrada do usuario e envia para a função de diagonal principal
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
		if (aux->lin == aux->col) {
			printf("[%d] - Matriz %02d (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->lin, aux->col);
			quadradaencontrada = 1;
		}
		aux = aux->prox;
	}

	printf("[0] - Voltar\n");

	if (!quadradaencontrada) {
		printf("Nao ha matrizes disponiveis para esta escolha. ");
	} else {
		printf("Escolha a matriz que deseja imprimir: ");
	}
	scanf("%d", &escolha);

	if (escolha == 0)
	{
		return;
	} 

	aux = *lista;
	while (aux != NULL)
	{
		if (aux->id == escolha)
		{
			if (aux->lin == aux->col) {
				imprime_diagonal_principal(aux);
				encontrada = 1;
				break;
			}
		}
		aux = aux->prox;
	}

	if (!encontrada)
	{
		printf("Opcao invalida!\n\n");
	}
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
		printf("[%d] - Matriz %02d (Dimensoes: %dx%d)\n", aux->id, aux->id, aux->lin, aux->col);
		aux = aux->prox;
	}
	printf("[0] - Voltar\n");

	printf("Escolha a matriz que deseja buscar os dados: ");
	scanf("%d", &escolha);

	if (escolha == 0)
	{
		return;
	}

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
	{
		printf("Opcao invalida!\n\n");
	}
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
		{"Imprimir Matrizes", menu_imprime_matriz},
		{"Imprimir Transpostas", menu_imprime_transposta},
		{"Imprimir Diagonal Principal", menu_imprime_diagonal_principal},
		{"Somar Matrizes", menu_soma_matrizes},
		{"Subtrair Matrizes", menu_subtracao_matrizes},
		{"Buscar Dados", menu_busca_dados}
	};

	int quantidadeOpcoes = sizeof(menu) / sizeof(menu[0]);
	int escolha;
	int i;

	while (1)
	{
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
		}
		else if (escolha == quantidadeOpcoes + 1)
		{
			printf("Saindo... \n");
			break;
		}
		else
		{
			printf("Opcao Invalida!\n");
		}
	}

	return 0;
}
