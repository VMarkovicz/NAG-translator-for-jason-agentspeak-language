/* Analisador Lexico */

%{
    #include "header.h" 
%}

%%
"E"             {return E;}
"OU"            {return OU;}
"NAO"           {return NAO;}
"crencas"       {return CRENCA;}
"objetivos"     {return OBJETIVO;}
"planos"        {return PLANO;}
[0-9]+          {return NUMBER;}
[a-zA-Z0-9]+    {return NAME;}
[ \t\r]+        {/*ignora espaços brancos*/}
\n              { return EOL; }
.               { yyerror("Caracter nao reconhecido felipe é burrao %c\n", *yytext); }

%%

int main(int nArgs, char* szArgs[]) {
    yylex();
    return 0;
}
