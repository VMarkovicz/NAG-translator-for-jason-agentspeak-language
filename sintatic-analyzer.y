/* Analisador Sintatico */
%{
    #include <stdio.h>
    #include "header.h" 
%}

%token NUMBER
%token NAME
%token CRENCA
%token OBJETIVO
%token PLANO
%token E 
%token OU
%token NAO

%token EOL

%agentlist;

%%
agent: CRENCA':' Lcrencas OBJETIVO':' Lobjetivos PLANO':' Lplanos;

Lcrencas: '(''{'nomeCrenca ';' '}'')' Lcrencas;

nomeCrenca: NAME;

Lobjetivos: '(''{'nomeObjetivo ';' '}'')' Lobjetivos;

nomeObjetivo: NAME;

Lplanos: '(''{'nomePlano ';' '}'')' Lplanos;

nomePlano: NAME tuplaPlano;

tuplaPlano: '('eventoGatilho';'contexto';'corpo')';

eventoGatilho: NAME;

contexto: /*Vazio*/ | expressaoLogica | NAME;

expressaoLogica: NAME E NAME | NAME OU NAME | NAO NAME;

corpo: '{'formulasCorpo ';' '}';

formulasCorpo: NAME;

agentlist: /*vazio*/
    | agentlist agent EOL
    ;

%%

