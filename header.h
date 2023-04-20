struct symbol{
    char *name;
    struct ref *reflist;
};

struct ref{
    struct ref *next;
    int lineno;
};

/*Tabela de tamanho fixo*/
#define NHASH 9997
struct symbol symtab[NHASH];
struct symbol *lookup(char*);

void addref(char *name, int lineno);
static unsigned symhash(char *sym);
struct symbol *lookup(char *sym);
void writerefs();
