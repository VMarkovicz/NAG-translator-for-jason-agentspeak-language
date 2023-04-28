/*Implementação de funcoes auxiliares em C*/
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct agent *agentlist = NULL;
struct beliefs *beliefslist = NULL;
struct goals *goalslist = NULL;
struct plans *planslist = NULL;

void createAgent(struct agent **agentlist, char *name1, char *name2){
    if(!*agentlist){
        *agentlist = malloc(sizeof(struct agent));
        (*agentlist)->name = name1;
        (*agentlist)->next = name2;
    }
    else{
        struct agent *aux = malloc(sizeof(struct agent));
        aux->name = name1;
        aux->next = agentlist;
        *agentlist = aux;
    }
}

void createBelief(struct beliefs **beliefslist, char *belief1, char *belief2) {
    if(!*beliefslist){
        *beliefslist = malloc(sizeof(struct beliefs));
        (*beliefslist)->name = belief1;
        (*beliefslist)->next = belief2;
    }
    else{
        struct beliefs *aux = malloc(sizeof(struct beliefs));
        aux->name = belief1;
        aux->next = beliefslist;
        *beliefslist = aux;
    }
}

void createGoals(struct goals **goalslist, char *goal1, char *goal2) {
    if(!*goalslist){
        *goalslist = malloc(sizeof(struct goals));
        (*goalslist)->name = goal1;
        (*goalslist)->next = goal2;
    }
    else{
        struct goals *aux = malloc(sizeof(struct goals));
        aux->name = goal1;
        aux->next = goalslist;
        *goalslist = aux;
    }
}

void createPlans(struct plans **planslist, char *plan1, char *plan2) {
    if (!*planslist) {
        *planslist = malloc(sizeof(struct plans));
        (*planslist)->name = plan1;
        (*planslist)->next = plan2;
    } else {
        struct plans *aux = malloc(sizeof(struct plans));
        aux->name = plan1;
        aux->next = planslist;
        *planslist = aux;
    }
}

char *concatenateTuple(char *eventoGatilho, char *contexto, char *corpo) {
    char *tuple = malloc(sizeof(char) * (strlen(eventoGatilho) + strlen(contexto) + strlen(corpo) + 1));
    strcpy(tuple, "+!");
    strcat(tuple, eventoGatilho);
    strcat(tuple, ": ");
    strcat(tuple, contexto);
    strcat(tuple, " <- ");
    strcat(tuple, corpo);
    return tuple;
}

char *concatenateExpression(char *name1, char *op, char *name2) {
    char *expression = malloc(sizeof(char) * (strlen(name1) + strlen(op) + strlen(name2) + 1));
    strcpy(expression, name1);
    strcat(expression, op);
    strcat(expression, name2);
    return expression;
}

char *concatenateBody(char *name1, char *name2) {
    char *body = malloc(sizeof(char) * (strlen(name1) + strlen(name2) + 1));
    
    if(!name2){
        strcpy(body, name1);
        strcat(body, " . ");
        return body;
    }
    else{
        strcpy(body, name1);
        strcat(body, " ; ");
        strcat(body, name2);
        return body;
    }
}

void printAgent(struct agent *agentlist) {

}

int main() {

}