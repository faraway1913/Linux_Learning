CC:=gcc

system_test: system_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


fork_test: fork_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@