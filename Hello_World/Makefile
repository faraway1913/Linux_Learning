#Makefile内容通常由以下部分组成
#<目标>：<前置依赖>
#	<需要执行的命令>

#定义变量 objects
objects := hello.o\
			main.o

#放在第一个的是默认目标
#目标为编译出main文件，依赖main.o和hello.o文件
#编译的命令为gcc -o main hello.o main.o

main: $(objects)
	gcc -o main $(objects) 

#main.o目标依赖main.c hello.h
#编译命令为gcc -c main.c
# main.o: main.c hello.h
# 	gcc -c main.c 
main.o: hello.h

#目标是hello，依赖是hello.c hello.h
#编译命令为gcc -c hello.c
# hello.o: hello.c hello.h
# 	gcc -c hello.c 
hello.o: hello.h

#引入伪目标
.PHONY: clean 

#clean目标可以清理编译的临时文件
clean:
	-rm main $(objects) 