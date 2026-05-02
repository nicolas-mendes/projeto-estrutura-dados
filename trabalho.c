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
	if (*N == NULL) {
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

// Valida os dados de entrada de um elemento e depois chama a inserção
void menu_insere_elemento(Matriz_Lista *matriz_vez, int max_l, int max_c)
{
	int continuar = 1;
	while (continuar)
	{
		float dado;
		int l, c;
		printf("Dado a ser inserido: ");
		scanf("%f", &dado);
		do {
			printf("Linha de input: ");
			scanf("%d", &l);
			if (l>max_l) {
				printf("Linha nao disponivel. (Limite: %d)\n", max_l);
				printf("Tente Novamente\n\n");
			}
		} while (l>max_l);
		do {
			printf("Coluna de input: ");
			scanf("%d", &c);
			if (c>max_c) {
				printf("Coluna nao disponivel. (Limite: %d)\n", max_c);
				printf("Tente Novamente\n\n");
			} 
		} while (c>max_c);

		insere_elemento(&(matriz_vez->prim),dado, l, c);

		printf("Continuar a inserir dados? (0 para sair): ");
		scanf("%d", &continuar);
	}
}

// ================= CHAMADAS MENU =================

// Inserção da matriz na lista
void menu_insere_matriz(Matriz_Lista **lista)
{	
	Matriz_Lista *nova_m, *aux;
	nova_m = cria_matriz();
	nova_m->prox = NULL;
	nova_m->prim = NULL;

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
		while (aux->prox != NULL) {
			aux = aux->prox;
		}
		aux->prox = nova_m;
		nova_m->id = aux->id + 1;
	}
	printf("Nova matriz adicionada a lista | ID : %d\n\n", nova_m->id);

	menu_insere_elemento(nova_m, nova_m->lin, nova_m->col);
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
		{"Inicializar Nova Matriz", menu_insere_matriz}};

	int quantidadeOpcoes = sizeof(menu) / sizeof(menu[0]);
	int escolha;
	int i;

	while (1)
	{
		printf("\n====== MENU PRINCIPAL ======\n");

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

