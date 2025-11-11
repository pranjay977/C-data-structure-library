cd ..\testcases
gcc remove.c -o remove.exe -I ..\..\singlyLinkedList\include -I ..\..\stack\include -I ..\..\queue\include -I ..\include -L ..\..\singlyLinkedList\lib -L ..\..\stack\lib -L ..\..\queue\lib -L ..\lib -l avllib -l stacklib -l queuelib -l slllib



