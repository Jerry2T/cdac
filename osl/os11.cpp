#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
using namespace std;

void simulate_cp(const char* source, const char* destination) {
    pid_t pid = fork();
    if (pid == -1) {
        cerr << "Fork failed!" << endl;
        exit(1);
    } else if (pid == 0) {
        cout << "Child process (PID " << getpid() << ") is running cp: " << source << " to " << destination << endl;
        execlp("cp", "cp", source, destination, (char*) NULL);
        cerr << "Exec failed!" << endl;
        exit(1);
    } else {
        wait(NULL);
        cout << "Parent process (PID " << getpid() << ") has finished waiting." << endl;
    }
}

void simulate_grep(const char* pattern, const char* filename, bool count_only) {
    pid_t pid = fork();
    if (pid == -1) {
        cerr << "Fork failed!" << endl;
        exit(1);
    } else if (pid == 0) {
        if (count_only) {
            cout << "Child process (PID " << getpid() << ") is running grep -c: " << pattern << " in " << filename << endl;
            execlp("grep", "grep", "-c", pattern, filename, (char*) NULL);
        } else {
            cout << "Child process (PID " << getpid() << ") is running grep: " << pattern << " in " << filename << endl;
            execlp("grep", "grep", pattern, filename, (char*) NULL);
        }
        cerr << "Exec failed!" << endl;
        exit(1);
    } else {
        wait(NULL);
        cout << "Parent process (PID " << getpid() << ") has finished waiting." << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./program <operation> [args]" << endl;
        return 1;
    }
    const char* operation = argv[1];
    if (strcmp(operation, "cp") == 0) {
        if (argc != 4) {
            cerr << "Usage: ./program cp <source> <destination>" << endl;
            return 1;
        }
        simulate_cp(argv[2], argv[3]);
    } else if (strcmp(operation, "grep") == 0) {
        if (argc < 4 || argc > 5) {
            cerr << "Usage: ./program grep <pattern> <filename> [-c]" << endl;
            return 1;
        }
        bool count_only = (argc == 5 && strcmp(argv[4], "-c") == 0);
        simulate_grep(argv[2], argv[3], count_only);
    } else {
        cerr << "Unknown operation: " << operation << endl;
        return 1;
    }
    cout << "Main process (PID " << getpid() << ") finished." << endl;
    return 0;
}
