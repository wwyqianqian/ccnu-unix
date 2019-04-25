编写多个C语言程序，其中p1.c调用p2.c中的函数，p2.c调用p1.c中的函数。main.c调用p1.c和p2.c中的函数。p1.c与p2.c的头文件分别为p1.h与p2.h 
-----------------------------------------
gcc *.c -o main        
./main           
3
12

-----------------------------------------
增加 makefile：
~/w/ccnu-unix/p1p2 make
gcc -c main.c
gcc -c p1.c
gcc -c p2.c
gcc -o qian main.o p1.o p2.o

make clean

 ~/w/ccnu-unix/p1p2 ./qian
3
12
