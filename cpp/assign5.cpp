#include<iostream>
#include<vector>
using namespace std;

void calculateNeed(int need[][10], int maxm[][10], int allot[][10], int P, int R) {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maxm[i][j] - allot[i][j];
}

void printMatrices(int maxm[][10], int allot[][10], int need[][10], int P, int R) {
    // Print Max Matrix
    cout << "\nMax Matrix:\n";
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            cout << maxm[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nAllocation Matrix:\n";
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            cout << allot[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
}

void findSafeSequences(int processes[], int avail[], int maxm[][10], int allot[][10], int need[][10], bool finish[], int work[], vector<int>& safeSeq, int P, int R) {
    bool found = false;
    for (int p = 0; p < P; p++) {
        if (!finish[p]) {
            int j;
            for (j = 0; j < R; j++) {
                if (need[p][j] > work[j])
                    break;
            }

            if (j == R) {
                for (int k = 0; k < R; k++) {
                    work[k] += allot[p][k];
                }

                safeSeq.push_back(p);
                finish[p] = true;
                findSafeSequences(processes, avail, maxm, allot, need, finish, work, safeSeq, P, R);

                safeSeq.pop_back();
                finish[p] = false;
                for (int k = 0; k < R; k++) {
                    work[k] -= allot[p][k];
                }
                found = true;
            }
        }
    }

    if (!found) {
        if (safeSeq.size() == P) {
            cout << "\nSafe sequence: ";
            for (int i = 0; i < P; i++) {
                cout << "P" << safeSeq[i] << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    int P, R;
    cout << "\nEnter the number of processes: ";
    cin >> P;
    cout << "Enter the number of resources: ";
    cin >> R;

    int processes[P]; // Process IDs
    for (int i = 0; i < P; i++) {
        processes[i] = i;
    }

    int avail[R];
    cout << "\nEnter available resources (space-separated): ";
    for (int i = 0; i < R; i++) {
        cin >> avail[i];
    }

    int maxm[P][10];
    cout << "\nEnter the maximum demand matrix for each process:-\n";
    for (int i = 0; i < P; i++) {
        cout << "Enter the maximum resources needed by process P" << i << ": ";
        for (int j = 0; j < R; j++) {
            cin >> maxm[i][j];
        }
    }

    int allot[P][10];
    cout << "\nEnter the allocation matrix for each process:-\n";
    for (int i = 0; i < P; i++) {
        cout << "Enter the resources allocated to process P" << i << ": ";
        for (int j = 0; j < R; j++) {
            cin >> allot[i][j];
        }
    }

    int need[10][10];
    calculateNeed(need, maxm, allot, P, R);
    printMatrices(maxm, allot, need, P, R);

    bool finish[10] = {0};
    int work[10];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }
    vector<int> safeSeq;
    findSafeSequences(processes, avail, maxm, allot, need, finish, work, safeSeq, P, R);
    return 0;
}


