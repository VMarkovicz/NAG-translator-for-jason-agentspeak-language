/* Analisador Lexico */
%option noyywrap nodefault yylineno
%{
#include "header.h" 
#include "sintatic-analyzer.tab.h"
%}

%%
":"|";"|"{"|"}"|"("|")"     { return yytext[0]; }
"E"                         { return E; }
"OU"                        { return OU; }
"NAO"                       { return NAO; }
"crencas"                   { return CRENCA; }
"objetivos"                 { return OBJETIVO; }
"planos"                    { return PLANO; }
[a-zA-Z0-9]+                { yylval.name = strdup(yytext); return NAME; }
[ \t\r]+                    {/*ignora espaços brancos*/}
[\n]                        { }
[\\\n]                      { }
.                           { yyerror("Caractere nao reconhecido %c\n", *yytext); }

%%

