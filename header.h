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
    char *beliefs;
    struct beliefs *next;
};

struct goals{
    char *goals;
    struct goals *next;
};

struct plans{
    char *plans;
    struct plans *next;
};

struct agent *concatenateAgent(struct agent *agentlist, struct agent *agent);
struct agent *createAgent(char *name, struct beliefs *beliefs, struct goals *goals, struct plans *plans);
struct beliefs *createBelief(char *belief1, struct beliefs *belief2);
struct goals *createGoal(char *goal1, struct goals *goal2);
struct plans *createPlan(char *plan1, struct plans *plan2);
char *createTuple(char *eventoGatilho, char *contexto, char *corpo);
char *createExpression(char *name1, char *op, char *name2);
char *createBody(char *body1, char *body2);

void printAgent(struct agent *agentlist);