del bst.o
del ..\lib\*.*
gcc -c *.c -I ..\..\singlyLinkedList\include -I ..\..\stack\include -I ..\..\queue\include -I ..\include  
ar rcs ..\lib\bstlib.lib *.o 
