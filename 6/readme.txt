на 6

Программа написана с использованием общей памяти и семафоров из 
system V. 

семафоры создаюстся при помощи команды semget, а удаляются при помощи 
semctl со специальными опциями
все действия с семафорами происходят при помощи команды sem_op и
и вспомогательных структур sembuf.


пример работы программы:

avo@avo-Yoga-Slim-7-14IIL05:~/IHW2-OS/6$ gcc main.c -o main -lpthread
avo@avo-Yoga-Slim-7-14IIL05:~/IHW2-OS/6$ ./main 4 3
field 1
0 1 0 
0 0 1 
1 0 1 

field2
1 0 0 
1 1 0 
0 1 0 
team 2 shot 0 0 (weapon 1)
team 1 shot 1 1 (weapon 3)
team 1 kill one of enemies
team 2 shot 2 2 (weapon 4)
team 2 kill one of enemies
team 1 shot 0 2 (weapon 1)
team 2 shot 2 1 (weapon 3)
team 2 shot 1 0 (weapon 1)
team 1 shot 0 0 (weapon 3)
team 1 kill one of enemies
team 2 shot 1 2 (weapon 4)
team 2 kill one of enemies
team 2 shot 1 1 (weapon 4)
team 1 shot 1 0 (weapon 3)
team 1 kill one of enemies
team 2 shot 0 2 (weapon 3)
team 1 shot 2 2 (weapon 1)
team 1 shot 2 0 (weapon 3)
team 1 shot 1 2 (weapon 3)
team 2 shot 0 1 (weapon 3)
team 2 kill one of enemies
team 1 shot 2 1 (weapon 3)
team 1 kill one of enemies
first team win
field1: 
-1 -1 -1 
-1 -1 -1 
1 -1 -1 

field2: 
-1 0 -1 
-1 -1 -1 
-1 -1 -1
