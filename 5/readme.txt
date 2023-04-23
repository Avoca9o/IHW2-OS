на 5 баллов

в этой программе уже используются именованные семафоры POSIX

создается он при помощи команды sem_open, удаляется при помощи
команды sem_unlink. 

пример работы программы:

avo@avo-Yoga-Slim-7-14IIL05:~/IHW2-OS/5$ gcc main.c -o main -lpthread
avo@avo-Yoga-Slim-7-14IIL05:~/IHW2-OS/5$ ./main 3 4
field 1
0 1 0 0 
0 0 0 1 
0 0 0 0 
0 0 0 1 

field2
0 0 0 0 
0 0 0 1 
0 1 0 0 
0 0 0 1 
team 1 shot 1 2 (weapon 1)
team 2 shot 1 2 (weapon 2)
team 1 shot 0 2 (weapon 2)
team 2 shot 2 2 (weapon 1)
team 2 shot 0 2 (weapon 3)
team 1 shot 3 3 (weapon 3)
team 1 kill one of enemies
team 1 shot 1 0 (weapon 1)
team 2 shot 2 3 (weapon 2)
team 2 shot 3 3 (weapon 2)
team 2 kill one of enemies
team 1 shot 0 0 (weapon 1)
team 1 shot 2 3 (weapon 2)
team 2 shot 0 1 (weapon 3)
team 2 kill one of enemies
team 2 shot 3 2 (weapon 2)
team 2 shot 3 1 (weapon 2)
team 1 shot 3 0 (weapon 2)
team 2 shot 1 0 (weapon 3)
team 2 shot 0 0 (weapon 2)
team 2 shot 2 0 (weapon 2)
team 1 shot 2 0 (weapon 2)
team 2 shot 1 3 (weapon 3)
team 2 kill one of enemies
second team win
field1: 
-1 -1 -1 0 
-1 0 -1 -1 
-1 0 -1 -1 
0 -1 -1 -1 

field2: 
-1 0 -1 0 
-1 0 -1 1 
-1 1 0 -1 
-1 0 0 -1
