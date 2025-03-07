#include <iostream>
using namespace std;

// Function to find the need of each process
void calculateNeed(int need[][10], int maxm[][10], int allot[][10], int P, int R)
{
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maxm[i][j] - allot[i][j];
}

void printMatrices(int maxm[][10], int allot[][10], int need[][10], int P, int R)
{
    cout << "\nMax Matrix:\n";
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            cout << maxm[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nAllocation Matrix:\n";
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            cout << allot[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(int processes[], int avail[], int maxm[][10], int allot[][10], int P, int R)
{
    int need[10][10];
    calculateNeed(need, maxm, allot, P, R);
    printMatrices(maxm, allot, need, P, R);

    bool finish[10] = {0};
    int safeSeq[10];
    int work[10];
    for (int i = 0; i < R; i++)
    {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < P)
    {
        bool found = false;
        for (int p = 0; p < P; p++)
        {
            if (finish[p] == 0)
            {
                int j;
                for (j = 0; j < R; j++)
                {
                    if (need[p][j] > work[j])
                        break;
                }

                if (j == R)
                {
                    for (int k = 0; k < R; k++)
                    {
                        work[k] += allot[p][k];
                    }

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }

        if (found == false)
        {
            cout << "\nSystem is not in a safe state\n";
            return false;
        }
    }

    cout << "\nSystem is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < P; i++)
    {
        cout << "P" << safeSeq[i] << " ";
    }
    cout << endl;
    return true;
}

// Driver code
int main()
{
    int P, R;
    cout << "\nEnter the number of processes: ";
    cin >> P;

    cout << "Enter the number of resources: ";
    cin >> R;

    int processes[P]; // Process IDs
    for (int i = 0; i < P; i++)
    {
        processes[i] = i;
    }

    // Available resources
    int avail[R];
    cout << "\nEnter available resources (space-separated): ";
    for (int i = 0; i < R; i++)
    {
        cin >> avail[i];
    }

    // Maximum resources that can be allocated to each process
    int maxm[P][10];
    cout << "\nEnter the maximum demand matrix for each process:-\n";
    for (int i = 0; i < P; i++)
    {
        cout << "Enter the maximum resources needed by process P" << i << ": ";
        for (int j = 0; j < R; j++)
        {
            cin >> maxm[i][j];
        }
    }

    // Resources allocated to each process
    int allot[P][10];
    cout << "\nEnter the allocation matrix for each process:-\n";
    for (int i = 0; i < P; i++)
    {
        cout << "Enter the resources allocated to process P" << i << ": ";
        for (int j = 0; j < R; j++)
        {
            cin >> allot[i][j];
        }
    }

    // Check if the system is in a safe state or not
    isSafe(processes, avail, maxm, allot, P, R);

    return 0;
}