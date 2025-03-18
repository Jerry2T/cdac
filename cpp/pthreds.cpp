#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>  // For sleep()

sem_t wrt;
pthread_mutex_t mutex;
int balance = 1000;  // Initial bank balance
int numreader = 0;

void *writer(void *wno)
{
    int writer_no = *((int *)wno);
    sem_wait(&wrt); // Writer locks the resource

    int amount = 200;  // Simulating a deposit or withdrawal
    balance += amount; // Modify balance
    printf("Writer %d updated balance to $%d\n", writer_no, balance);

    sem_post(&wrt); // Unlock for others
    return NULL;
}

void *reader(void *rno)
{
    int reader_no = *((int *)rno);

    pthread_mutex_lock(&mutex);
    numreader++;
    if (numreader == 1) 
    {
        sem_wait(&wrt); // First reader locks writers
    }
    pthread_mutex_unlock(&mutex);

    // Reading section (Check balance)
    printf("Reader %d checked balance: $%d\n", reader_no, balance);
    sleep(1); // Simulate some delay in reading

    pthread_mutex_lock(&mutex);
    numreader--;
    if (numreader == 0) 
    {
        sem_post(&wrt); // Last reader unlocks writers
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t read[10], write[5];
    int readers[10] = {1,2,3,4,5,6,7,8,9,10};
    int writers[5] = {1,2,3,4,5};

    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1); // Initialize semaphore

    // Creating reader threads
    for (int i = 0; i < 10; i++) 
    {
        pthread_create(&read[i], NULL, reader, (void *)&readers[i]);
    }

    // Creating writer threads
    for (int i = 0; i < 5; i++) 
    {
        pthread_create(&write[i], NULL, writer, (void *)&writers[i]);
    }

    // Joining reader threads
    for (int i = 0; i < 10; i++) 
    {
        pthread_join(read[i], NULL);
    }

    // Joining writer threads
    for (int i = 0; i < 5; i++) 
    {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
