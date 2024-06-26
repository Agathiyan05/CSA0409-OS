#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
sem_t room;

void *philosopher(void *arg) {
    int philosopherID = *(int *)arg;
    int leftFork = philosopherID;
    int rightFork = (philosopherID + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking.\n", philosopherID);

        sem_wait(&room);

        pthread_mutex_lock(&forks[leftFork]);
        printf("Philosopher %d picks up left fork (%d).\n", philosopherID, leftFork);

        pthread_mutex_lock(&forks[rightFork]);
        printf("Philosopher %d picks up right fork (%d).\n", philosopherID, rightFork);

        printf("Philosopher %d is eating.\n", philosopherID);

        pthread_mutex_unlock(&forks[leftFork]);
        pthread_mutex_unlock(&forks[rightFork]);

        sem_post(&room);
        usleep(1000000);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopherIDs[NUM_PHILOSOPHERS];

    sem_init(&room, 0, NUM_PHILOSOPHERS);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        philosopherIDs[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopherIDs[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
        pthread_mutex_destroy(&forks[i]);
    }

    sem_destroy(&room);

    return 0;
}