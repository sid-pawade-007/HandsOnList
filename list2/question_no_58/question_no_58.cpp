
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void* threadFunction(void* arg) {
    int threadNum = *(int*)arg;

    cout << "Thread " << threadNum
         << " is running. Thread ID: "
         << pthread_self() << endl;

    return nullptr;
}

int main() {
    pthread_t threads[3];
    int threadNum[3] = {1, 2, 3};

    // Create three threads
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], nullptr,
                           threadFunction, &threadNum[i]) != 0) {
            cerr << "Failed to create thread " << i + 1 << endl;
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], nullptr);
    }

    cout << "All three threads completed." << endl;

    return 0;
}
