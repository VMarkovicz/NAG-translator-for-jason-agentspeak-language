translator: lexic-analyzer.l sintatic-analyzer.y
	bison -d sintatic-analyzer.y
	flex lexic-analyzer.l
	gcc -o translator lex.yy.c sintatic-analyzer.tab.c -lfl
	@echo "Translator is ready to use!"