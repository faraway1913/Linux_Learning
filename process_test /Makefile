CC:=gcc

system_test: system_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


fork_test: fork_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


erlou: erlou.c
	-$(CC) -o $@ $^


execve_test: execve_test.c erlou
	-$(CC) -o $@ $<
	-./$@
	-rm ./$@ ./$(word 2,$^)