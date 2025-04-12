#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

void printallocation(const vector<int> &allocation, const vector<int> &processSize, vector<int> &blockSize) {
    cout << "ProcessID\tProcessSize\tBlockID\tBlockSize\tFragmentedMemory\n";
    for (int i = 0; i < processSize.size(); i++) {
        if (allocation[i] != -1) {
            cout << i + 1 << "\t\t" << processSize[i] << "\t\t" << allocation[i] + 1 << "\t\t" << blockSize[allocation[i]] + processSize[i] << "\t\t" << blockSize[allocation[i]] << endl;
        } else {
            cout << i + 1 << "\t\t" << processSize[i] << "\t\tNot Allocated\t-\t-" << endl;
        }
    }
}

void firstFit(vector<int> &blockSize, vector<int> &processSize) {
    int n = processSize.size(), m = blockSize.size();
    vector<int> allocation(n, -1);    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }    
    cout << "First Fit Allocation:\n";
    printallocation(allocation, processSize, blockSize);
}

void nextfit(vector<int> blocksize, vector<int> processsize) {
    int n=processsize.size() ,m=blocksize.size(), lastallocated = 0;
    vector<int> allocation(n, -1);
    for(int i=0; i<n; i++) {
        for(int j=lastallocated; j<m; j++) {
            if(blocksize[j] >= processsize[i]) {
                allocation[i] = j;
                blocksize[j] -= processsize[i];
                lastallocated = j;
                break;
            }
        }
    }
    cout<<"Next Fit Allocation:\n";
    printallocation(allocation, processsize, blocksize);
}

void worstFit(vector<int> &blockSize, vector<int> &processSize) {
    int n = processSize.size(), m = blockSize.size();
    vector<int> allocation(n, -1);    
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if(worstIdx== -1 || blockSize[j]>blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }    
    cout << "Worst Fit Allocation:\n";
    printallocation(allocation, processSize, blockSize);
}

void bestFit(vector<int> &blockSize, vector<int> &processSize) {
    int n = processSize.size(), m = blockSize.size();
    vector<int> allocation(n, -1);    
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) bestIdx = j;                
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }    
    cout << "Best Fit Allocation:\n";
    printallocation(allocation, processSize, blockSize);
}

int main(){
    int choice, numblocks, numprocesses;
    vector<int> blocksize, processsize;
    cout<<"Enter the number of blocks: ";
    cin>>numblocks;

    cout << "Enter sizes for " << numblocks << " blocks: ";
    for (int i = 0; i < numblocks; i++) {
        int size;
        cin >> size;
        blocksize.push_back(size);
    }    
    cout << "Enter number of processes: ";
    cin >> numprocesses;
    cout << "Enter sizes for " << numprocesses << " processes: ";
    for (int i = 0; i < numprocesses; i++) {
        int size;
        cin >> size;
        processsize.push_back(size);
    }

    cout << "Choose a Memory Allocation Strategy:\n";
    cout << "1. First Fit\n";
    cout << "2. Next Fit\n";
    cout << "3. Best Fit\n";
    cout << "4. Worst Fit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch(choice) {
        case 1: firstFit(blocksize, processsize);
                break;
        case 2: nextfit(blocksize, processsize);
                break;
        case 3: bestFit(blocksize, processsize);
                break;
        case 4: worstFit(blocksize, processsize);
                break;
        default: cout << "Invalid choice!" << endl;
    }
    return 0;
}