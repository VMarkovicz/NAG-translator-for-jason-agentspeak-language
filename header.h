/*estrutura de dados*/
struct symbol{
    char *name;
    struct beliefslist *beliefs;
    struct goalslist *goals;
    struct planslist *plans;
};

struct beliefslist{
    char *sym;
    struct beliefs *next;
};

struct beliefs{
    char *sym;
    struct belief *next;
};

struct goalslist{
    char *sym;
    struct goals *next;
};

struct goals{
    char *sym;
    struct goal *next;
};

struct planslist{
    char *sym;
    struct plans *next;
};

struct plans{
    char *sym;
    struct plan *next;
};

