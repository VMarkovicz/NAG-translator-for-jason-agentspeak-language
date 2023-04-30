/*Implementação de funcoes auxiliares em C*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"

struct agent *listaAgentes = NULL;
struct agent *concatenateAgent(struct agent *agentlist, struct agent *agent) {
    if(!agentlist){
        return agent;
    }
    else{
        struct agent *aux = agentlist;
        while(aux->next){
            aux = aux->next;
        }
        aux->next = agent;
        return agentlist;
    }
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

struct beliefs *createBelief(char *belief1, struct beliefs *belief2) {
    struct beliefs *beliefs = (struct beliefs *) malloc(sizeof(struct beliefs));
    beliefs->beliefs = belief1;
    beliefs->next = belief2;
    return beliefs;
}

struct goals *createGoal(char *goal1, struct goals *goal2) {
    struct goals *goals = (struct goals *) malloc(sizeof(struct goals));
    goals->goals = goal1;
    goals->next = goal2;
    return goals;
}

struct plans *createPlan(char *plan1, struct plans *plan2) {
    struct plans *plans = (struct plans *) malloc(sizeof(struct plans));
    plans->plans = plan1;
    plans->next = plan2;
    return plans;
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
            fprintf(fp, "%s.\n", agentlist->beliefs->beliefs);
            agentlist->beliefs = agentlist->beliefs->next;
        }

        //goals
        while(agentlist->goals){
            fprintf(fp, "!%s.\n", agentlist->goals->goals);
            agentlist->goals = agentlist->goals->next;
        }

        //plans
        while(agentlist->plans){
            fprintf(fp, "%s\n", agentlist->plans->plans);
            agentlist->plans = agentlist->plans->next;
        }
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

void copyList(struct agent *agentlist) {
    if(!agentlist){
        return;
    }
    else{
        listaAgentes = concatenateAgent(listaAgentes, agentlist);
        copyList(agentlist->next);
    }
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
    printAgent(listaAgentes);
    return 0;
}

