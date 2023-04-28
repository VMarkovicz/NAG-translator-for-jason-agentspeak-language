/*estrutura de dados*/

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

void createAgent(struct agent **agentlist, char *name, struct beliefs *beliefs, struct goals *goals, struct plans *plans);
void createBelief(struct beliefs **beliefslist, char *belief1, char *belief2);
void createGoal(struct goals **goalslist, char *goal1, char *goal2);
void createPlan(struct plans **planslist, char *plan1, char *plan2);
char *concatenateTuple(char *eventoGatilho, char *contexto, char *corpo);
char *concatenateExpression(char *name1, char *op, char *name2);
char *concatenateBody(char *name1, char *name2);

void printAgent(struct agent *agentlist);

