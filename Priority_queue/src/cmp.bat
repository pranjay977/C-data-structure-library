del pqueue.o
gcc -c *.c -I ..\..\singlyLinkedList\include -I ..\..\Heap\include -I ..\..\stack\include -I ..\..\Array\include -I ..\..\queue\include -I ..\include 
ar rcs ..\lib\pqueuelib.lib *.o 