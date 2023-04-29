/*estrutura de dados*/
extern int yylineno;
void yyerror(char *s, ...);
int yyparse(void);
int yylex(void);
void yyrestart();

struct agent{
    char *name;
    struct beliefs *beliefs;
    struct goals *goals;
    struct plans *plans;
    struct agent *next;
};

struct beliefs{
    char *name;
    struct beliefs *next;
};

struct goals{
    char *name;
    struct goals *next;
};

struct plans{
    char *name;
    struct plans *next;
};

struct agent *createAgent(char *name, struct beliefs *beliefs, struct goals *goals, struct plans *plans);
struct beliefs *createBelief(char *belief1, struct beliefs *belief2);
struct goals *createGoal(char *goal1, struct goals *goal2);
struct plans *createPlan(char *plan1, struct plans *plan2);
char *concatenateTuple(char *eventoGatilho, char *contexto, char *corpo);
char *concatenateExpression(char *name1, char *op, char *name2);
char *concatenateBody(char *name1, char *name2);

void printAgent(struct agent *agentlist);