	#include <stdio.h>
#include <stdlib.h>

// Cria??o do tipo Elemento (Cada dado de uma Matriz Esparsa)
typedef struct elemento
{
	float dado;
	int lin, col;
	struct elemento *prox;
} Elemento;

// Cria??o do tipo Item_Lista (Cada ind?ce que aponta para o primeiro elemento de uma Matriz)
typedef struct item
{
	int id;
	Elemento *prim;
	struct item *prox;
} Item_Lista;

typedef struct Bloco
{
	int dado;
	struct Bloco *prox;
} Nodo;

// Cria??o do tipo OpcaoMenu (Apenas para organiza??o do menu de op??es)
typedef struct
{
	char titulo[50];
	void (*funcao)(Nodo **);
} OpcaoMenu;

// Cria um elemento para uma Matriz Esparsa
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

// Cria um item para a lista de Matrizes
Item_Lista *cria_item()
{
	Item_Lista *p;
	p = (Item_Lista *)malloc(sizeof(Item_Lista));
	if (!p)
	{
		printf("Problema de alocacao");
		exit(0);
	}
	return p;
}

// Insere um novo Elemento em uma Matriz Esparsa
void insere_matriz(Elemento **N, float dado, int lin, int col)
{
	Elemento *novo, *aux;
	novo = cria_elem();
	novo->dado = dado;
	novo->lin = lin;
	novo->col = col;
	novo->prox = NULL;
	if (*N == NULL)
		*N = novo;
	else
	{
		aux = *N;
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}
}

// Insere um novo item na Lista de Matrizes Esparsas
void insere_lista(Item_Lista **N)
{
	Item_Lista *novo, *aux;
	novo = cria_item();
	novo->prox = NULL;
	novo->prim = NULL;
	if (*N == NULL)
	{
		*N = novo;
		novo->id = 1;
	}
	else
	{
		aux = *N;
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
		novo->id = aux->id + 1;
		printf("Nova Matriz Adicionada A lista, ID : %d", novo->id);
	}
}

// Chamada via menu do insere_matriz
void menu_insere_matriz(Elemento **matriz)
{
	float valor;
	int lin;
	int col;
	printf("Digite o valor do Elemento: ");
	scanf("%f", &valor);
	printf("Digite a linha a ser inserida: ");
	scanf("$d", &lin);
	printf("Digite a coluna a ser inserida: ");
	scanf("%d", &col);
	insere_matriz(matriz, valor, lin, col);
	printf("Valor %.2f inserido com sucesso na linha &d e Coluna &d \n", valor, lin, col);
}

// Chamada via menu do insere_lista
void menu_insere_lista(Item_Lista **lista)
{
	insere_lista(lista);
	printf("Nova Matriz Inicializada com Sucesso.");
}

// Inicializa a lista que armazena todas as Matrizes da sess?o
void inicializa_lista(Item_Lista **N)
{
	*N = NULL;
}

int main()
{
	Item_Lista *lista;
	
	inicializa_lista(&lista);
	
	OpcaoMenu menu[] = {
		{"Inicializar Nova Lista", menu_insere_lista}};

	int quantidadeOpcoes = sizeof(menu) / sizeof(menu[0]);
	int escolha;
	int i;

	while (1)
	{
		printf("\n====MENU PRINCIPAL====\n");

		for (i = 0; i < quantidadeOpcoes; i++)
		{
			printf("[%d] - %s\n", i + 1, menu[i].titulo);
		}
		printf("[%d] - Sair\n", quantidadeOpcoes + 1);
		printf("Escolha uma opcao:");
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
		system("cls");
	}

	return 0;
}

