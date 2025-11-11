del heap.o
gcc -c *.c -I ..\include -I ..\..\array\include -I ..\..\common\include
ar rcs ..\lib\heaplib.lib *.o
