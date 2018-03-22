#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define natural unsigned int

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

#define assert_timeout(condition) assert(condition);

#if 1

typedef struct my_struct {
	void *valor;
	struct my_struct* next;
} listilla_nodo;

typedef struct my_list {
	struct my_struct* head;
	struct my_struct* tail;
	natural elementos_cnt;
} listilla_fifo;

typedef struct listilla_iterador {
	listilla_fifo *ctx;
	listilla_nodo *nodo_act;
	bool primera_llamada;
	natural llamadas;
} listilla_iterador;

/* Will always return the pointer to my_list */
struct my_list* list_add_element(struct my_list* s, void *valor) {
	struct my_struct* p = malloc(1 * sizeof(*p));

	if (NULL == p) {
		fprintf(stderr, "IN %s, %s: malloc() failed\n", __FILE__, "list_add");
		return s;
	}

	p->valor = valor;
	p->next = NULL;

	if (NULL == s) {
		printf("Queue not initialized\n");
		free(p);
		return s;
	} else if (NULL == s->head && NULL == s->tail) {
		/* printf("Empty list, adding p->num: %d\n\n", p->num);  */
		s->head = s->tail = p;
		return s;
	} else if (NULL == s->head || NULL == s->tail) {
		fprintf(stderr,
				"There is something seriously wrong with your assignment of head/tail to the list\n");
		free(p);
		return NULL;
	} else {
		/* printf("List not empty, adding element to tail\n"); */
		s->tail->next = p;
		s->tail = p;
	}
	s->elementos_cnt++;

	return s;
}

/* This is a queue and it is FIFO, so we will always remove the first element */
static void *list_remove_element(struct my_list* s) {
	struct my_struct* h = NULL;
	struct my_struct* p = NULL;
	void *valor = NULL;

	if (NULL == s) {
		printf("List is empty\n");
		return s;
	} else if (NULL == s->head && NULL == s->tail) {
		printf("Well, List is empty\n");
		return s;
	} else if (NULL == s->head || NULL == s->tail) {
		printf("There is something seriously wrong with your list\n");
		printf("One of the head/tail is empty while other is not \n");
		abort();
	}

	h = s->head;
	valor = h->valor;
	p = h->next;
	free(h);
	s->head = p;
	if (NULL == s->head)
		s->tail = s->head; /* The element tail was pointing to is free(), so we need an update */

	s->elementos_cnt--;
	return valor;
}

/* ---------------------- small helper fucntions ---------------------------------- */
struct my_list* list_free(struct my_list* s) {
	while (s->head) {
		list_remove_element(s);
	}

	return s;
}

struct my_list* list_new(void) {
	struct my_list* p = malloc(1 * sizeof(*p));

	assert_timeout(p);

	p->head = p->tail = NULL;

	return p;
}

void list_print_element(const struct my_struct* p) {
	if (p) {
		printf("Num = %p\n", p->valor);
	} else {
		printf("Can not print NULL struct \n");
	}
}

void list_print(const struct my_list* ps) {
	struct my_struct* p = NULL;

	if (ps) {
		for (p = ps->head; p; p = p->next) {
			list_print_element(p);
		}
	}

	printf("------------------\n");
}

static bool list_empty(struct my_list *s) {
	return !s->head;
}

static void list_iterador_init(listilla_fifo *ctx, listilla_iterador *iter) {
	assert_timeout(!iter->ctx);
	assert_timeout(!iter->primera_llamada);
	assert_timeout(!iter->nodo_act);
	assert_timeout(!iter->llamadas);
	iter->ctx = ctx;
	iter->nodo_act = NULL;
	iter->primera_llamada = verdadero;
	iter->llamadas = 0;
}
static void list_iterador_fini(listilla_iterador *iter) {
	iter->ctx = NULL;
	iter->nodo_act = NULL;
	iter->primera_llamada = falso;
	iter->llamadas = 0;
}

static void *list_iterador_peekea_actual(listilla_iterador *iter) {
	return iter->nodo_act ? iter->nodo_act->valor : NULL;
}

static void *list_iterador_obten_siguiente(listilla_iterador *iter) {
	if (iter->nodo_act) {
		iter->nodo_act = iter->nodo_act->next;
	} else {
		if (iter->primera_llamada) {
			iter->primera_llamada = falso;
			iter->nodo_act = iter->ctx->head;
		}
	}
	if (iter->nodo_act) {
		iter->llamadas++;
	}
	return iter->nodo_act ? iter->nodo_act->valor : NULL;
}
static void *list_iterador_hay_siguiente(listilla_iterador *iter) {
	listilla_nodo *siguiente = NULL;
	if (!iter->nodo_act) {
		if (iter->primera_llamada) {
			siguiente = iter->ctx->head;
		}
	} else {
		siguiente = iter->nodo_act->next;
	}

	return siguiente ? siguiente->valor : NULL;
}

static bool list_iterador_esta_initializado(listilla_iterador *iter) {
	return !!iter->ctx;
}

#endif

#if 1
typedef struct stackaca_nodo {
	void *data;
	struct stackaca_nodo* next;
} stackaca_nodo;
typedef struct stackaca {
	stackaca_nodo *cabeza;
} stackaca;

/*
 init the stack
 */
static void stackaca_init(stackaca *ctx) {
	ctx->cabeza = NULL;
}

/*
 push an element into stack
 */
static void stackaca_push(stackaca *ctx, void *data) {
	stackaca_nodo* tmp = (stackaca_nodo*) malloc(sizeof(stackaca_nodo));
	assert_timeout(tmp);
	tmp->data = data;
	tmp->next = ctx->cabeza;
	ctx->cabeza = tmp;
}
/*
 pop an element from the stack
 */
static void *stackaca_pop(stackaca *ctx) {
	stackaca_nodo* tmp = ctx->cabeza;
	void *caca = tmp->data;
	ctx->cabeza = tmp->next;
	free(tmp);
	return caca;
}
/*
 returns 1 if the stack is empty, otherwise returns 0
 */
static bool stackaca_empty(stackaca *ctx) {
	return ctx->cabeza == NULL ? verdadero : falso;
}

static void stackaca_fini(stackaca *ctx) {
	while (!stackaca_empty(ctx)) {
		stackaca_pop(ctx);
	}
}

static void *stackaca_peekea(stackaca *ctx) {
	return ctx->cabeza ? ctx->cabeza->data : NULL;
}
#endif

typedef enum {
	WHITE, GREY, BLACK
} Color;

typedef struct Node {
	int k;
	Color c;
	listilla_fifo *ne;
} Node;

typedef struct Vertex {
	int k1;
	int k2;
} Vertex;

static inline bool topologicalSortRecursive(Node *n, stackaca *sorted_nodes) {
	bool done = verdadero;
	listilla_iterador *it = &(listilla_iterador ) { 0 };
	Node *cn = NULL;

	n->c = GREY;

	list_iterador_init(n->ne, it);

	while ((cn = list_iterador_obten_siguiente(it))) {
		switch (cn->c) {
		case WHITE:
			done = topologicalSortRecursive(cn, sorted_nodes);
			break;
		case GREY:
			done = falso;
			break;
		default:
			assert(cn->c == BLACK);
			break;
		}
		if (!done) {
			break;
		}
	}

	if (done) {
		n->c = BLACK;
		stackaca_push(sorted_nodes, n);
	}

	list_iterador_fini(it);
	return done;
}

static inline bool topologicalSort(Node *adj_list, int adj_list_sz,
		Node **sorted_nodes_list) {
	bool done = falso;
	stackaca *sorted_nodes = &(stackaca ) { 0 };

	stackaca_init(sorted_nodes);

	for (int i = adj_list_sz; i > 0; i--) {
		Node *n = adj_list + i;
		if (n->c == WHITE) {
			done = topologicalSortRecursive(n, sorted_nodes);
		}
		if (!done) {
			break;
		}
	}

	if (done) {
		int i = 0;
		while (!stackaca_empty(sorted_nodes)) {
			sorted_nodes_list[i++] = stackaca_pop(sorted_nodes);
		}
	}

	stackaca_fini(sorted_nodes);

	return done;
}

int comp_vertex(const void *pa, const void *pb) {
	Vertex *a = (Vertex *) pa;
	Vertex *b = (Vertex *) pb;
	int r = 0;

	if (a->k1 == b->k1) {
		r = b->k2 - a->k2;
	} else {
		r = b->k1 - a->k1;
	}
	return r;
}

int main() {
	int n = 0;
	int m = 0;
	int i = 0;
	Node *adj_list = NULL;
	Vertex *vs = NULL;
	bool done = falso;
	Node **sorted_nodes = NULL;

	scanf("%u %u\n", &n, &m);

	adj_list = calloc(n + 1, sizeof(Node));
	assert(adj_list);

	vs = calloc(m, sizeof(Vertex));
	assert(vs);

	sorted_nodes = calloc(n, sizeof(Node*));
	assert(sorted_nodes);

	for (i = 1; i <= n; i++) {
		Node *n = adj_list + i;
		n->k = i;
		n->c = WHITE;
		n->ne = list_new();
	}

	for (i = 0; i < m; i++) {
		Vertex *v = vs + i;

		scanf("%u %u\n", &v->k1, &v->k2);
	}

	qsort(vs, m, sizeof(Vertex), comp_vertex);

	for (i = 0; i < m; i++) {
		Vertex *v = vs + i;

		list_add_element(adj_list[v->k1].ne, adj_list + v->k2);
	}

	done = topologicalSort(adj_list, n, sorted_nodes);
	if (done) {
		printf("%u", sorted_nodes[0]->k);
		for (i = 1; i < n; i++) {
			printf(" %u", sorted_nodes[i]->k);
		}
		printf("\n");
	} else {
		printf("Sandro fails.\n");
	}

	return EXIT_SUCCESS;
}
