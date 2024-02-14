#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

using namespace std;

// To hold shared data
struct ShD {
    int counter;
};

int main() {
    int shmid;  // Shared memory segment ID
    key_t key = IPC_PRIVATE;  // Unique key for shared memory

    // shared memory segment
    if ((shmid = shmget(key, sizeof(ShD), IPC_CREAT | 0666)) < 0) {
        cerr << "shmget failed" << endl;
        return 1;
    }

    // Attaching shared memory segment to process address space
    ShD *shared_data = (ShD *) shmat(shmid, NULL, 0);
    if (shared_data == (ShD *) -1) {
        cerr << "shmat failed" << endl;
        return 1;
    }
    shared_data->counter = 0;  // Initialize the counter

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed" << endl;
        return 1;
    }

    else if (pid == 0) {
        // Child process - Process 1: Counter
        while (true) {
            sleep(5);
            (shared_data->counter)++;
        }
    }

    else {
        // Parent process - Process 2: Square calculator
        while (true) {
            // Wait for the counter to increment
            sleep(1);
            int current_value = shared_data->counter;
            int square = current_value*current_value;
            cout << "Square of " << current_value << ": " << square << endl;
        }
    }

//Detaching shared memory segment
shmdt(shared_data)

//Removing shared mem segment
shmctl(shmid, IPC_RMID, NULL)

return 0;
}
