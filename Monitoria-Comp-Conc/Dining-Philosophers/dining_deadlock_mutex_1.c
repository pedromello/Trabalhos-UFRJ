/***********************************************************
* You can use all the programs on  www.c-program-example.com
* for personal and learning purposes. For permissions to use the
* programs for commercial purposes,
* contact info@c-program-example.com
* To find more C programs, do visit www.c-program-example.com
* and browse!
* 
*                      Happy Coding
***********************************************************/

// PROBLEM:
// The philosophers will always get the left chopstick first
// and then get the right one. If all of them get their
// respective left at the same time, then they will wait forever
// for the right one.

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 // number of philosophers

#define LEFT  ((ph_num + 0) % N)
#define RIGHT ((ph_num + 1) % N)

pthread_mutex_t chopsticks[N]; // mutexes controling the access to each chopstick

void *philospher(void *num);
void take_fork(int);
void put_fork(int);

int main()
{
    printf("Dining Philosophers: deadlock example 1\n");

    int phil_num[N];
    int i;
    pthread_t thread_id[N]; // each thread will simulate the behavior of one philosopher

    for (i = 0; i < N; i++)
        pthread_mutex_init(&chopsticks[i], NULL);

    for (i = 0; i < N; i++)
    {
        phil_num[i] = i;
        pthread_create(&thread_id[i], NULL, philospher, &phil_num[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    for (i = 0; i < N; i++)
        pthread_mutex_destroy(&chopsticks[i]);
}

void *philospher(void *num)
{
    int i = *((int*)num);
    printf("Philosopher %d is thinking\n", i + 1);
    while (1)
    {
        take_fork(i);
        sleep(0);
        put_fork(i);
    }
}

void take_fork(int ph_num)
{
    // waiting for left chopstick
    printf("Philosopher %d is Hungry and waits for chopstick %d\n", ph_num + 1, LEFT + 1);
    pthread_mutex_lock(&chopsticks[LEFT]);
    // got left chopstick
    printf("Philosopher %d got chopstick %d\n", ph_num + 1, LEFT + 1);

    sleep(1);

    // waiting for right chopstick
    printf("Philosopher %d now waits for chopstick %d\n", ph_num + 1, RIGHT + 1);
    pthread_mutex_lock(&chopsticks[RIGHT]);
    // got right chopstick
    printf("Philosopher %d took chopstick %d and %d, and now is Eating\n", ph_num + 1, LEFT + 1, RIGHT + 1);

}

void put_fork(int ph_num)
{
    printf("Philosopher %d putting fork %d and %d down\n", ph_num + 1, LEFT + 1, ph_num + 1);
    printf("Philosopher %d is thinking\n", ph_num + 1);
    pthread_mutex_unlock(&chopsticks[LEFT]);
    sleep(1);
    pthread_mutex_unlock(&chopsticks[RIGHT]);
    sleep(1);
}
