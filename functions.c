/*Implementação de funcoes auxiliares em C*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"

struct agent *agentlist = NULL;
struct beliefs *beliefslist = NULL;
struct goals *goalslist = NULL;
struct plans *planslist = NULL;

struct agent *createAgent(char *name, struct beliefs *beliefs, struct goals *goals, struct plans *plans){
    if(!agentlist){
        agentlist = malloc(sizeof(struct agent));
        agentlist->name = strcat(name, ".asl");
        agentlist->beliefs = beliefs;
        agentlist->goals = goals;
        agentlist->plans = plans;
        agentlist->next = NULL;
    }
    else{
        struct agent *aux = malloc(sizeof(struct agent));
        aux->name = name;
        aux->beliefs = beliefs;
        aux->goals = goals;
        aux->plans = plans;
        aux->next = agentlist;
        agentlist = aux;
    }
    return agentlist;
}

struct beliefs *createBelief(char *belief1, struct beliefs *belief2) {
    if(!beliefslist){
        beliefslist = malloc(sizeof(struct beliefs));
        beliefslist->name = belief1;
        beliefslist->next = belief2;
    }
    else{
        struct beliefs *aux = malloc(sizeof(struct beliefs));
        aux->name = belief1;
        aux->next = beliefslist;
        beliefslist = aux;
    }
    printf("BELIEF: %s\n", beliefslist->name);
    return beliefslist;
}

struct goals *createGoal(char *goal1, struct goals *goal2) {
    if(!goalslist){
        goalslist = malloc(sizeof(struct goals));
        goalslist->name = goal1;
        goalslist->next = goal2;
    }
    else{
        struct goals *aux = malloc(sizeof(struct goals));
        aux->name = goal1;
        aux->next = goalslist;
        goalslist = aux;
    }
    printf("GOAL: %s\n", goalslist->name);
    return goalslist;
}

struct plans *createPlan(char *plan1, struct plans *plan2) {
    if(!planslist){
        planslist = (struct plans *)malloc(sizeof(struct plans));
        planslist->name = plan1;
        planslist->next = plan2;
    }
    else{
        struct plans *aux = (struct plans*) malloc(sizeof(struct plans));
        aux->name = plan1;
        aux->next = planslist;
        planslist = aux;
    }
    printf("PLAN: %s\n", planslist->name);
    return planslist;
}

char *concatenateTuple(char *eventoGatilho, char *contexto, char *corpo) {
    char *tuple = (char *) malloc(sizeof(char) * (strlen(eventoGatilho) + strlen(contexto) + strlen(corpo) + 8));
    strcpy(tuple, "+!");
    strcat(tuple, eventoGatilho);
    strcat(tuple, ": ");
    strcat(tuple, contexto);
    strcat(tuple, " <- ");
    strcat(tuple, corpo);
    printf("TUPLE: %s\n", tuple);
    return tuple;
}

char *concatenateExpression(char *name1, char *op, char *name2) {
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
    printf("EXPRESSION: %s\n", expression);
    return expression;
}

char *concatenateBody(char *name1, char *name2) {
    char *body = NULL;
    if(!name2){
        body = (char *) malloc(sizeof(char) * (strlen(name1) + 3));
        strcpy(body, name1);
        strcat(body, ". ");
    } else {
        body = (char *) malloc(sizeof(char) * (strlen(name1) + strlen(name2) + 4));
        strcpy(body, name1);
        strcat(body, " ; ");
        strcat(body, name2);
    }
 
    printf("BODY: %s\n", body);
    return body;
}

void printAgent(struct agent *agentlist) {
    if(!agentlist){
        return;
    }
    else{
        //criar arquivo .asl 
        FILE *fp;
        fp = fopen(agentlist->name, "w");
        if (fp == NULL) {
            printf("Erro ao criar arquivo .asl\n");
            exit(1);
        }

        //escrever no arquivo .asl
        //beliefs
        while(agentlist->beliefs){
            fprintf(fp, "%s.\n", agentlist->beliefs->name);
            agentlist->beliefs = agentlist->beliefs->next;
        }

        //goals
        while(agentlist->goals){
            fprintf(fp, "!%s.\n", agentlist->goals->name);
            agentlist->goals = agentlist->goals->next;
        }

        //plans
        while(agentlist->plans){
            fprintf(fp, "%s\n", agentlist->plans->name);
            agentlist->plans = agentlist->plans->next;
        }
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
    return 0;
}

