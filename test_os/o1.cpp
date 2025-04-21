#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void execute_cp(const string &command){
    stringstream ss(command);
    string cmd,src,dest;
    ss>>cmd>>src>>dest;
    if(!fileExists(src)){
        cout<<"File "<<src<<" does not exist."<<endl;
        return;
    }
    if(fileExists(dest)){
        cout<<"File "<<dest<<" already exists."<<endl;
        return;
    }
    ifstream srcFile(src, ios::binary);
    ofstream destFile(dest, ios::binary);
    destFile<<srcFile.rdbuf();    
}

void execute_grep(const string& command){
    stringstream ss(command);
    string cmd,pattern,filename;
    ss>>cmd>>pattern>>filename;  
    ifstream file(filename);
    if(!file.good()){
        cout<<"File "<<filename<<" does not exist."<<endl;
        return;
    }
    ifstream infile(filename);
    string line;
    bool found = false;
    while (getline(infile, line)) {
        if (line.find(pattern) != string::npos) {
            cout << line << endl;
            found = true;
        }
    }
    if (!found) {
        cerr << "Error: Pattern " << pattern << " not found in file " << filename << ".\n";
    }
}

int main(){
    int choice, pid;
    cout << "\nMenu:\n1. fork\n2. wait\n3. execlp\n4. exit\n5. cp (copy file)\n";
    cout << "6. grep (search in file)\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.get();
    switch(choice){
        case 1: pid = fork();
            if (pid == 0) {
                cout << "Child process created. PID: " << getpid() << ", PPID: " << getppid() << "\n";
            } else if (pid > 0) {
                cout << "Parent process. PID: " << getpid() << ", Child PID: " << pid << "\n";
            } else {
                cerr << "Fork failed!\n";
            }
            break;                            
        
            case 2: pid = fork();
                    if (pid == 0) {
                        cout << "Child process running. PID: " << getpid() << "\n";
                        exit(0);
                    } else {
                        int status;
                        wait(&status);
                        cout << "Child process completed. Exit status: " << WEXITSTATUS(status) << "\n";
                    }
                    break;
                
            case 3: pid= fork();
                    if(pid==0){
                        cout << "Executing ls command with execlp.\n";
                        execlp("ls", "ls", "-l", nullptr);
                        cerr << "execlp failed!\n";
                    } else {
                        wait(nullptr);                        
                    }
                    break;

            case 4: cout << "Exiting program.\n";
                    exit(0);
                    break;
            case 5: {
                string command;
                cout << "Enter the cp command (e.g., 'cp source.txt destination.txt'): ";
                getline(cin, command);
                execute_cp(command);
                break;
            }
            case 6: {
                string command;
                cout << "Enter the grep command (e.g., 'grep pattern filename'): ";
                getline(cin, command);
                execute_grep(command);
                break;
            }           
    }
    return 0;
}