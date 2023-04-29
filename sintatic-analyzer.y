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

%token <name>NAME
%token <name>CRENCA
%token <name>OBJETIVO
%token <name>PLANO
%token <name>E
%token <name>OU
%token <name>NAO

%type <agent>agent
%type <beliefs>Lcrencas
%type <goals>Lobjetivos
%type <plans>Lplanos
%type <name>nomeCrenca nomeObjetivo nomePlano
%type <name>eventoGatilho contexto
%type <name>expressaoLogica
%type <name>formulasCorpo
%type <name>tuplaPlano
%type <name>corpo

%start agent;

%%
agent:NAME CRENCA':' '{' Lcrencas '}' OBJETIVO':' '{' Lobjetivos '}' PLANO':' '{' Lplanos '}'   { $$ = createAgent($1, $5, $10, $15); printAgent($$);}
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
tuplaPlano: '('eventoGatilho';'contexto';' '{' corpo '}' ')' { $$ = concatenateTuple($2, $4, $7); }
    ;
eventoGatilho: NAME { $$ = $1; }   //sem :
    ;
contexto: /*Vazio*/     { $$ = NULL;}
    | expressaoLogica   { $$ = $1; }    //sem ;
    | NAME              { $$ = $1; }    //sem ;
    ;
expressaoLogica: NAME E NAME { $$ = concatenateExpression($1, " & ", $3); }
        | NAME OU NAME { $$ = concatenateExpression($1, " | ", $3); }
        | NAO NAME { $$ = concatenateExpression(NULL, "not ", $2); }
    ;               
corpo: /*Vazio*/ { $$ = NULL; }
    | formulasCorpo ';' corpo   { $$ = concatenateBody($1, $3); }   //com ; e . mas sem {}
    ;
formulasCorpo: NAME { $$ = $1; }
    ;

%%

