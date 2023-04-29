translator: lexic-analyzer.l sintatic-analyzer.y functions.c
	bison -d sintatic-analyzer.y
	flex -o sintatic-analyzer.lex.c lexic-analyzer.l
	gcc -o translator sintatic-analyzer.tab.c sintatic-analyzer.lex.c functions.c -lfl -lm
	@echo "Translator is ready to use!"