/*Implementação de funcoes auxiliares em C*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"

struct agent *list = NULL;

char *createBody(char *body1, char *body2) {
    char *body = NULL;
    if(!body2){
        body = (char *) malloc(sizeof(char) * (strlen(body1) + 3));
        strcpy(body, body1);
        strcat(body, ". ");
    } else {
        body = (char *) malloc(sizeof(char) * (strlen(body1) + strlen(body2) + 4));
        strcpy(body, body1);
        strcat(body, " ; ");
        strcat(body, body2);
    }
    return body;
}

char *createExpression(char *name1, char *op, char *name2) {
    char *expression = NULL;
    if(!name1){
        expression = (char *) malloc(sizeof(char) * (strlen(op) + strlen(name2) + 1));
        strcpy(expression, op);
        strcat(expression, name2);
    } else{
        expression = (char *) malloc(sizeof(char) * (strlen(name1) + strlen(op) + strlen(name2) + 1));
        strcpy(expression, name1);
        strcat(expression, op);
        strcat(expression, name2);
    }
    return expression;
}

char *createTuple(char *eventoGatilho, char *contexto, char *corpo) {
    char *tuple = (char *) malloc(sizeof(char) * (strlen(eventoGatilho) + strlen(contexto) + strlen(corpo) + 8));
    strcpy(tuple, "+!");
    strcat(tuple, eventoGatilho);
    strcat(tuple, ": ");
    strcat(tuple, contexto);
    strcat(tuple, " <- ");
    strcat(tuple, corpo);
    return tuple;
}

struct plans *createPlan(char *plan1, struct plans *plan2) {
    struct plans *plans = (struct plans *) malloc(sizeof(struct plans));
    plans->plans = plan1;
    plans->next = plan2;
    return plans;
}

struct goals *createGoal(char *goal1, struct goals *goal2) {
    char *aux = malloc(sizeof(char) * (strlen(goal1) + 3));
    strcpy(aux, "!");
    strcat(aux, goal1);
    strcat(aux, ".");
    struct goals *goals = (struct goals *) malloc(sizeof(struct goals));
    goals->goals = aux;
    goals->next = goal2;
    return goals;
}

struct beliefs *createBelief(char *belief1, struct beliefs *belief2) {
    strcat(belief1, ".");
    struct beliefs *beliefs = (struct beliefs *) malloc(sizeof(struct beliefs));
    beliefs->beliefs = belief1;
    beliefs->next = belief2;
    return beliefs;
}

struct agent *createAgent(char *name, struct beliefs *beliefs, struct goals *goals, struct plans *plans){
    struct agent *agent = (struct agent *) malloc(sizeof(struct agent));
    agent->name = strcat(name, ".asl");
    agent->beliefs = beliefs;
    agent->goals = goals;
    agent->plans = plans;
    agent->next = NULL;
    return agent;
}

struct agent *concatenateAgent(struct agent *agent, struct agent *agentlist) {
    if(!agentlist){
        copyList(agent);
        return agent;
    }
    else{
        copyList(agent);
        struct agent *aux = agent;
        aux->next = agentlist;
        return aux;
    }
}

void copyList(struct agent *agentlist) {
    if(!list){
        list = (struct agent *) malloc(sizeof(struct agent));
        list->name = agentlist->name;
        list->beliefs = agentlist->beliefs;
        list->goals = agentlist->goals;
        list->plans = agentlist->plans;
        list->next = NULL;
    }
    else{
        struct agent *aux = malloc(sizeof(struct agent));
        aux->name = agentlist->name;
        aux->beliefs = agentlist->beliefs;
        aux->goals = agentlist->goals;
        aux->plans = agentlist->plans;
        aux->next = list;
        list = aux;
    }
}

void printAgent(struct agent *agentlist) {
    if(!agentlist){
        return;
    }
    else{
        FILE *fp;
        fp = fopen(agentlist->name, "w");
        if (fp == NULL) {
            printf("Erro ao criar arquivo .asl\n");
            exit(1);
        }

        //beliefs
        while(agentlist->beliefs){
            fprintf(fp, "%s\n", agentlist->beliefs->beliefs);
            agentlist->beliefs = agentlist->beliefs->next;
        }

        //goals
        while(agentlist->goals){
            fprintf(fp, "%s\n", agentlist->goals->goals);
            agentlist->goals = agentlist->goals->next;
        }

        //plans
        while(agentlist->plans){
            fprintf(fp, "%s\n", agentlist->plans->plans);
            agentlist->plans = agentlist->plans->next;
        }
        fclose(fp);
        printAgent(agentlist->next);
    }
}

void yyerror(char *s, ...) {
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int main(int argc, char *argv[]) {
    int i;
    if(argc<2){
        yyparse();
        return(0);
    }
    for(i = 1; i < argc; i++){
        FILE *f = fopen(argv[i], "r");
        if(!f){
            perror(argv[i]);
            return(1);
        }
        yyrestart(f);
        yylineno = 1;
        yyparse();
        fclose(f);        
    }
    printAgent(list);
    return 0;
}

