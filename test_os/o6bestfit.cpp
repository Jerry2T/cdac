#include <iostream>
#include <vector>
using namespace std;

void printResult(const vector<int>& allocation, const vector<int>& processSize, const vector<int>& blockSizeCopy) {
    cout << "ProcessID\tProcessSize\tBlockID\t\tBlockSize\tFragmentedMemory\n";
    for (size_t i = 0; i < processSize.size(); ++i) {
        if (allocation[i] != -1) {
            int blkID = allocation[i];
            int fragment = blockSizeCopy[blkID] - processSize[i];
            cout << i + 1 << "\t\t" << processSize[i] << "\t\t" << blkID + 1 << "\t\t" << blockSizeCopy[blkID] << "\t\t" << fragment << "\n";
        } else {
            cout << i + 1 << "\t\t" << processSize[i] << "\t\tNot Allocated\t-\t\t-\n";
        }
    }
}

void firstFit(vector<int> blockSize, const vector<int>& processSize) {
    vector<int> allocation(processSize.size(), -1);
    vector<int> originalBlockSize = blockSize;

    for (size_t i = 0; i < processSize.size(); ++i) {
        for (size_t j = 0; j < blockSize.size(); ++j) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "First Fit Allocation:\n";
    printResult(allocation, processSize, originalBlockSize);
    cout << endl;
}

void nextFit(vector<int> blockSize, const vector<int>& processSize) {
    vector<int> allocation(processSize.size(), -1);
    vector<int> originalBlockSize = blockSize;

    int j = 0, n = blockSize.size();
    for (size_t i = 0; i < processSize.size(); ++i) {
        int count = 0;
        while (count < n) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
            j = (j + 1) % n;
            count++;
        }
    }

    cout << "Next Fit Allocation:\n";
    printResult(allocation, processSize, originalBlockSize);
    cout << endl;
}

void bestFit(vector<int> blockSize, const vector<int>& processSize) {
    vector<int> allocation(processSize.size(), -1);
    vector<int> originalBlockSize = blockSize;

    for (int i = 0; i < processSize.size(); i++) {
        int bestid = -1;
        for (int j = 0; j < blockSize.size(); j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestid == -1 || blockSize[j] < blockSize[bestid]) {
                    bestid = j;
                }
            }
        }
        if (bestid != -1) {
            allocation[i] = bestid;
            blockSize[bestid] -= processSize[i];
        }
    }

    cout << "Best Fit Allocation:\n";
    printResult(allocation, processSize, originalBlockSize);
    cout << endl;
}

void worstFit(vector<int> blockSize, const vector<int>& processSize) {
    vector<int> allocation(processSize.size(), -1);
    vector<int> originalBlockSize = blockSize;

    for (int i = 0; i < processSize.size(); i++) {
        int worstIdx = -1;
        for (int j = 0; j < blockSize.size(); j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
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
    printResult(allocation, processSize, originalBlockSize);
    cout << endl;
}

int main() {
    vector<int> blockSize = {100, 500, 200, 300, 600};
    vector<int> processSize = {212, 417, 112, 426};

    firstFit(blockSize, processSize);
    nextFit(blockSize, processSize);
    bestFit(blockSize, processSize);
    worstFit(blockSize, processSize);

    return 0;
}
