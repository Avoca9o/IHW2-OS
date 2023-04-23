Программа на 4 балла: 

В данной программе обмен данными происходит через общую память с использованием неименованных POSIX семафоров. 

При завершении программы горячими клавишами она пишет, что война закончилась ничьей. 

Семафор удаляется командой sem_destroy

примеры работы программы:

avo@avo-Yoga-Slim-7-14IIL05:~/IHW2-OS/4$ gcc main.c -o main -lpthread
avo@avo-Yoga-Slim-7-14IIL05:~/IHW2-OS/4$ ./main 4 3
field 1
1 0 0 
1 0 1 
1 0 0 

field2
0 0 1 
1 0 1 
0 0 1 
team 1 shot 1 2 (weapon 1)
team 1 kill one of enemies
team 2 shot 2 1 (weapon 3)
team 1 shot 2 2 (weapon 2)
team 1 kill one of enemies
team 1 shot 2 0 (weapon 4)
team 1 shot 2 1 (weapon 1)
team 2 shot 1 0 (weapon 3)
team 2 kill one of enemies
team 1 shot 1 0 (weapon 2)
team 1 kill one of enemies
team 1 shot 0 1 (weapon 4)
team 1 shot 0 0 (weapon 3)
team 2 shot 1 2 (weapon 1)
team 2 kill one of enemies
team 1 shot 0 2 (weapon 2)
team 1 kill one of enemies
first team win
field1: 
1 0 0 
-1 0 -1 
1 -1 0 

field2: 
-1 -1 -1 
-1 0 -1 
-1 -1 -1 

------------------------------------------------------------------------------

пример с прерыванием программы:

avo@avo-Yoga-Slim-7-14IIL05:~/IHW2-OS/4$ ./main 4 3
field 1
0 0 1 
1 0 0 
1 0 1 

field2
0 0 1 
1 0 1 
1 0 0 
team 1 shot 1 0 (weapon 2)
team 1 kill one of enemies
team 2 shot 1 2 (weapon 4)
team 1 shot 0 2 (weapon 4)
team 1 kill one of enemies
^C
end of war. Draw
