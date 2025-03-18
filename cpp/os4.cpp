#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int balance = 1000; // Shared bank balance
pthread_mutex_t balance_mutex; // Mutex for synchronization

void* reader(void* arg) {
    int id = *((int*)arg);
    cout << "Reader " << id << " checking balance: $" << balance << endl;
    sleep(1); // Simulate processing time
    return nullptr;
}

void* writer(void* arg) {
    int* params = (int*)arg;
    int id = params[0];
    int amount = params[1];
    bool deposit = params[2];

    if (deposit) {
        balance += amount;
        cout << "Writer " << id << " deposited $" << amount << ", new balance: $" << balance << endl;
    } else {
        if (balance >= amount) {
            balance -= amount;
            cout << "Writer " << id << " withdrew $" << amount << ", new balance: $" << balance << endl;
        } else {
            cout << "Writer " << id << " failed to withdraw $" << amount << " (Insufficient funds)" << endl;
        }
    }
    sleep(1); // Simulate processing time
    return nullptr;
}

void* synchronized_reader(void* arg) {
    int id = *((int*)arg);
    pthread_mutex_lock(&balance_mutex); // Lock for reading
    cout << "[SYNC] Reader " << id << " checking balance: $" << balance << endl;
    pthread_mutex_unlock(&balance_mutex); // Unlock after reading
    sleep(1);
    return nullptr;
}

void* synchronized_writer(void* arg) {
    int* params = (int*)arg;
    int id = params[0];
    int amount = params[1];
    bool deposit = params[2];

    pthread_mutex_lock(&balance_mutex); // Lock for writing
    if (deposit) {
        balance += amount;
        cout << "[SYNC] Writer " << id << " deposited $" << amount << ", new balance: $" << balance << endl;
    } else {
        if (balance >= amount) {
            balance -= amount;
            cout << "[SYNC] Writer " << id << " withdrew $" << amount << ", new balance: $" << balance << endl;
        } else {
            cout << "[SYNC] Writer " << id << " failed to withdraw $" << amount << " (Insufficient funds)" << endl;
        }
    }
    pthread_mutex_unlock(&balance_mutex); // Unlock after writing
    sleep(1);
    return nullptr;
}

void runSimulation(bool useSync) {
    pthread_t readers[3], writers[2];
    int reader_ids[3] = {1, 2, 3};
    int writer_params[2][3] = {{1, 500, 1}, {2, 700, 0}}; // {id, amount, deposit(1)/withdraw(0)}

    // Create reader threads
    for (int i = 0; i < 3; i++) {
        if (useSync)
            pthread_create(&readers[i], nullptr, synchronized_reader, &reader_ids[i]);
        else
            pthread_create(&readers[i], nullptr, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        if (useSync)
            pthread_create(&writers[i], nullptr, synchronized_writer, writer_params[i]);
        else
            pthread_create(&writers[i], nullptr, writer, writer_params[i]);
    }

    // Join threads
    for (int i = 0; i < 3; i++)
        pthread_join(readers[i], nullptr);

    for (int i = 0; i < 2; i++)
        pthread_join(writers[i], nullptr);
}

int main() {
    int choice;
    cout << "Select mode:\n";
    cout << "1. Without Synchronization\n";
    cout << "2. With Synchronization\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 2) {
        pthread_mutex_init(&balance_mutex, nullptr);
        cout << "Running with synchronization...\n";
        runSimulation(true);
        pthread_mutex_destroy(&balance_mutex);
    } else {
        cout << "Running without synchronization...\n";
        runSimulation(false);
    }

    return 0;
}

