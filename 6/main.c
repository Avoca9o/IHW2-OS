#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#define SEM "/my_semaphore"

key_t key;
int mutex_id;
struct sembuf plus, minus;

int n, k;
int base1[10][10];
int base2[10][10];

int first_weapons_x[10];
int first_weapons_y[10];
int second_weapons_x[10];
int second_weapons_y[10];

int count1, count2;

void end(int d) {
    if (d == 1) {
        printf("first team win\n");
    } else {
        printf("second team win\n");
    }
    printf("field1: \n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", base1[i][j]);
        }
        printf("\n");
    }
    printf("\nfield2: \n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", base2[i][j]);
        }
        printf("\n");
    }
    semctl(mutex_id, 0, IPC_RMID, 0);
    exit(0);
}

void my_handler(int nsig){
    printf("\nend of war. Draw\n");
    semctl(mutex_id, 0, IPC_RMID, 0);
    exit(0);
}

void *weapon1(void* number) {
    int d = *(int *)number;
    while (1) {
        sleep(first_weapons_y[d] + 1);
        semop(mutex_id, &minus, 1);
        if (base1[first_weapons_x[d]][first_weapons_y[d]] == -1) {
            semop(mutex_id, &plus, 1);
            break;
        }
        int x, y;
        do {
            x = rand() % n;
            y = rand() % n;
        } while (base2[x][y] == -1);
        printf("team 1 shot %d %d (weapon %d)\n", x, y, d + 1);
        if (base2[x][y] == 1) {
            printf("team 1 kill one of enemies\n");
            --count2;
        }
        base2[x][y] = -1;
        if (count2 == 0) {
            end(1);
        }
        semop(mutex_id, &plus, 1);
    }
}

void *weapon2(void* number) {
    int d = *(int *)number;
    while (1) {
        sleep(second_weapons_y[d] + 1);
        semop(mutex_id, &minus, 1);
        if (base2[second_weapons_x[d]][second_weapons_y[d]] == -1) {
            semop(mutex_id, &plus, 1);
            break;
        }
        int x, y;
        do {
            x = rand() % n;
            y = rand() % n;
        } while (base1[x][y] == -1);
        printf("team 2 shot %d %d (weapon %d)\n", x, y, d + 1);
        if (base1[x][y] == 1) {
            printf("team 2 kill one of enemies\n");
            --count1;
        }
        base1[x][y] = -1;
        if (count1 == 0) {
            end(2);
        }
        semop(mutex_id, &plus, 1);
    }
}

int main(int argc, char* argv[]) {
    (void)signal(SIGINT, my_handler);
    key = ftok(SEM, 0);

    if (argc != 3) {
        fprintf(stderr, "You should enter number of weapons and size of field\n");
        exit(0);
    }
    k = atoi(argv[1]);
    n = atoi(argv[2]);

    if (k < 3 || k > 8 || strlen(argv[1]) > 1) {
        fprintf(stderr, "You should enter an integer from 3 to 8 as number of weapons\n");
        exit(0);
    }

    if (n < 3 || n > 8 || strlen(argv[2]) > 1) {
        fprintf(stderr, "You should enter an integer from 3 to 8 as size of field\n");
        exit(0);
    }

    mutex_id = semget(key, 1, 0666 | IPC_CREAT);
    plus.sem_num = 0;
    plus.sem_flg = 0;
    plus.sem_op = 1;

    minus.sem_num = 0;
    minus.sem_op = -1;
    minus.sem_flg = 0;
    semop(mutex_id, &plus, 1);
    count1 = k;
    count2 = k;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            base1[i][j] = 0;
            base2[i][j] = 0;
        }
    }

    srand(time(NULL));
    pthread_t first[k];
    pthread_t second[k];
    int buf1[k];
    int buf2[k];
    for (int i = 0; i < k; ++i) {
        buf1[i] = i;
        buf2[i] = i;
    }

    for (int i = 0; i < k; ++i) {
        int x = rand() % n;
        int y = rand() % n;
        if (base1[x][y] == 1) {
            --i;
            continue;
        }
        first_weapons_x[i] = x;
        first_weapons_y[i] = y;
        base1[x][y] = 1;
    }

    for (int i = 0; i < k; ++i) {
        int x = rand() % n;
        int y = rand() % n;
        if (base2[x][y] == 1) {
            --i;
            continue;
        }
        second_weapons_x[i] = x;
        second_weapons_y[i] = y;
        base2[x][y] = 1;
    }

    semop(mutex_id, &minus, 1);
    printf("field 1\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", base1[i][j]);
        }
        printf("\n");
    }
    printf("\nfield2\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", base2[i][j]);
        }
        printf("\n");
    }
    semop(mutex_id, &plus, 1);

    for (int i = 0; i < k; ++i) {
        pthread_create(&first[i], 0, weapon1, (void *)(&buf1[i]));
        pthread_create(&second[i], 0, weapon2, (void *)(&buf2[i]));
    }

    for (int i = 0; i < k; ++i) {
        pthread_join(first[i], NULL);
        pthread_join(second[i], NULL);
    }
    my_handler(2);
}
