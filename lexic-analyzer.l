/* Analisador Lexico */

%{
    #include "header.h" 
    #include <stdio.h>
    #include "sintatic-analyser.tab.h"
%}

%%
"E"             {printf("E: %s\n", yytext);return E;}
"OU"            {printf("OU: %s\n", yytext);return OU;}
"NAO"           {printf("NAO: %s\n", yytext);return NAO;}
"crencas"       {printf("crencas: %s\n", yytext);return CRENCA;}
"objetivos"     {printf("objetivos: %s\n", yytext);return OBJETIVO;}
"planos"        {printf("planos: %s\n", yytext);return PLANO;*/}
[a-zA-Z0-9]+    {printf("pal: %s\n", yytext);return NAME;}
[ \t\r]+        {/*ignora espaços brancos*/}
\n              { return EOL; }
.               { printf("Caracter nao reconhecido felipe é burrao %c\n", *yytext); }

%%

int main(int nArgs, char* szArgs[]) {
    yylex();
    return 0;
}
