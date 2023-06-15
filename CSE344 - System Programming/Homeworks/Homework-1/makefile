GO: APPEND_COMP DUPLICATION_COMP

CLEAR:
	clear

APPEND_COMP:
	gcc appendMeMore.c -o appendMeMore

APPEND_RUN:
	./appendMeMore f1 1000000 & ./appendMeMore f1 1000000

LSEEK_RUN:
	./appendMeMore f2 1000000 x & ./appendMeMore f2 1000000 x

LIST:
	ls -l f1 f2

DUPLICATION_COMP:
	gcc duplication.c -o duplication

DUPLICATION_RUN:
	./duplication

clean:
	rm -f appendMeMore duplication f1 f2 *.txt
