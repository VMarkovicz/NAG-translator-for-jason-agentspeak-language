/* Analisador Sintatico */
%{
#include <stdio.h>
#include "header.h" 

extern struct agent *agentList;
extern struct beliefs *beliefsList;
extern struct goals *goalsList;
extern struct plans *plansList;
%}

%union {
    struct agent *agentList;
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

%token EOL

%type <agentList>agent
%type <beliefs>Lcrencas
%type <goals>Lobjetivos
%type <plans>Lplanos
%type <name>nomeCrenca nomeObjetivo nomePlano
%type <name>eventoGatilho contexto
%type <name>expressaoLogica
%type <name>formulasCorpo
%type <name>tuplaPlano
%type <name>corpo

%start agentlist;

%%
agent:NAME CRENCA':' '{' Lcrencas '}' OBJETIVO':' '{' Lobjetivos '}' PLANO':' '{' Lplanos '}'
    ;
Lcrencas: /*Vazio*/ { $$ = NULL; }
    | nomeCrenca ';' Lcrencas    { $$ = createBelief($1); }
    ;
nomeCrenca: NAME    { $$ = $1 }
    ;
Lobjetivos: /*Vazio*/ { $$ = NULL; }
    | nomeObjetivo ';' Lobjetivos { $$ = createGoal($1);}
    ;
nomeObjetivo: NAME  { $$ = $1 }
    ;
Lplanos: /*Vazio*/ { $$ = NULL; }
    | nomePlano ';' Lplanos  { $$ = createPlan(&plansList ,$1, $3);}
    ;
nomePlano: NAME tuplaPlano { $$ = $2; } 
    ;
tuplaPlano: '('eventoGatilho';'contexto';' '{' corpo '}' ')' { $$ = concatenateTuple($2, $4, $7); }
    ;
eventoGatilho: NAME { $$ = $1; }   //sem :
    ;
contexto: /*Vazio*/ 
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
agentlist: /*vazio*/
    | agentlist agent EOL
    {printf("start");}
    ;

%%

