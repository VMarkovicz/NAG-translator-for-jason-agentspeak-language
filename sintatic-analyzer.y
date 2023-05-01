/* Analisador Sintatico */
%{
#include <stdio.h>
#include <stdlib.h>
#include "header.h"
%}

%union {
    struct agent *agent;
    struct beliefs *beliefs;
    struct goals *goals;
    struct plans *plans;
    char *name;
}

%token <name> NAME
%token <name> CRENCA
%token <name> OBJETIVO
%token <name> PLANO
%token <name> E
%token <name> OU
%token <name> NAO

%type <agent> agentlist
%type <agent> agent
%type <beliefs> Lcrencas
%type <goals> Lobjetivos
%type <plans> Lplanos
%type <name> nomeCrenca nomeObjetivo nomePlano
%type <name> eventoGatilho contexto
%type <name> expressaoLogica
%type <name> formulasCorpo
%type <name> tuplaPlano
%type <name> corpo

%start agentlist;

%%
agentlist: /*Vazio*/ { $$ = NULL; }
    | agent agentlist { $$ = concatenateAgent($1, $2); copyList($$); }
    ;
agent:NAME CRENCA':' '{' Lcrencas '}' OBJETIVO':' '{' Lobjetivos '}' PLANO':' '{' Lplanos '}'   { $$ = createAgent($1, $5, $10, $15); }
    ;
Lcrencas: /*Vazio*/ { $$ = NULL; }
    | nomeCrenca ';' Lcrencas    { $$ = createBelief($1, $3); }
    ;
nomeCrenca: NAME    { $$ = $1; }
    ;
Lobjetivos: /*Vazio*/ { $$ = NULL; }
    | nomeObjetivo ';' Lobjetivos { $$ = createGoal($1, $3);}
    ;
nomeObjetivo: NAME  { $$ = $1; }
    ;
Lplanos: /*Vazio*/ { $$ = NULL; }
    | nomePlano ';' Lplanos  { $$ = createPlan($1, $3);}
    ;
nomePlano: NAME tuplaPlano { $$ = $2; } 
    ;
tuplaPlano: '('eventoGatilho';'contexto';' '{' corpo '}' ')' { $$ = createTuple($2, $4, $7); }
    ;
eventoGatilho: NAME { $$ = $1; }   //sem :
    ;
contexto: /*Vazio*/     { $$ = NULL;}
    | expressaoLogica   { $$ = $1; }    //sem ;
    | NAME              { $$ = $1; }    //sem ;
    ;
expressaoLogica: NAME E NAME { $$ = createExpression($1, " & ", $3); }
        | NAME OU NAME { $$ = createExpression($1, " | ", $3); }
        | NAO NAME { $$ = createExpression(NULL, "not ", $2); }
    ;               
corpo: /*Vazio*/ { $$ = NULL; }
    | formulasCorpo ';' corpo   { $$ = createBody($1, $3); }   //com ; e . mas sem {}
    ;
formulasCorpo: NAME { $$ = $1; }
    ;

%%

