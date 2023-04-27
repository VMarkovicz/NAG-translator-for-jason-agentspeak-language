/* Analisador Lexico */

%{
#include "header.h" 
#include <stdio.h>
#include "sintatic-analyser.tab.h"
%}

%%
"E"             { return E; }
"OU"            { return OU; }
"NAO"           { return NAO; }
"crencas"       { return CRENCA; }
"objetivos"     { return OBJETIVO; }
"planos"        { return PLANO; }
[a-zA-Z0-9]+    { return NAME; }
[ \t\r]+        {/*ignora espaços brancos*/}
\n              { return EOL; }
.               { printf("Caractere nao reconhecido %c\n", *yytext); }

%%