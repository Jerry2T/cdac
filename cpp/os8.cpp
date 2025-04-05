#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

void fcfs(vector<int> requests, int head) {
    int seek = 0;
    cout << "Sequence: ";
    for (int r : requests) {
        cout << r << " ";
        seek += abs(head - r);
        head = r;
    }
    cout << "\nTotal Seek Time: " << seek << endl;
}

void sstf(vector<int> requests, int head) {
    int seek = 0;
    vector<bool> visited(requests.size(), false);
    cout << "Sequence: ";
    for (int i = 0; i < requests.size(); ++i) {
        int minDist = INT_MAX, index = -1;
        for (int j = 0; j < requests.size(); ++j) {
            if (!visited[j] && abs(requests[j] - head) < minDist) {
                minDist = abs(requests[j] - head);
                index = j;
            }
        }
        visited[index] = true;
        seek += abs(head - requests[index]);
        head = requests[index];
        cout << head << " ";
    }
    cout << "\nTotal Seek Time: " << seek << endl;
}

void scan(vector<int> requests, int head, int diskSize, string direction) {
    int seek = 0;
    vector<int> left, right;
    vector<int> seq;
    if (direction == "left") left.push_back(0);
    else right.push_back(diskSize - 1);
    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    cout << "Sequence: ";
    if (direction == "left") {
        for (int i = left.size() - 1; i >= 0; --i) {
            seq.push_back(left[i]);
        }
        for (int i = 0; i < right.size(); ++i) {
            seq.push_back(right[i]);
        }
    } else {
        for (int i = 0; i < right.size(); ++i) {
            seq.push_back(right[i]);
        }
        for (int i = left.size() - 1; i >= 0; --i) {
            seq.push_back(left[i]);
        }
    }

    for (int r : seq) {
        cout << r << " ";
        seek += abs(head - r);
        head = r;
    }
    cout << "\nTotal Seek Time: " << seek << endl;
}

void cscan(vector<int> requests, int head, int diskSize) {
    int seek = 0;
    vector<int> left, right;
    vector<int> seq;
    right.push_back(diskSize - 1);
    left.push_back(0);

    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    cout << "Sequence: ";
    for (int i = 0; i < right.size(); ++i) {
        seq.push_back(right[i]);
    }
    for (int i = 0; i < left.size(); ++i) {
        seq.push_back(left[i]);
    }

    for (int r : seq) {
        cout << r << " ";
        seek += abs(head - r);
        head = r;
        if (head == diskSize - 1) {
            seek += (diskSize - 1); // jump from end to 0
            head = 0;
        }
    }
    cout << "\nTotal Seek Time: " << seek << endl;
}

int main() {
    int n, head, diskSize, choice;
    string direction;
    vector<int> requests;
    cout << "Enter number of disk requests: ";
    cin >> n;

    cout << "Enter the disk requests:\n";
    requests.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> requests[i];
    cout << "Enter initial head position: ";
    cin >> head;
    cout << "Enter disk size (max cylinder number): ";
    cin >> diskSize;
    cout << "\nChoose Algorithm:\n";
    cout << "1. FCFS\n2. SSTF\n3. SCAN\n4. CSCAN\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: fcfs(requests, head);
                break;
        case 2: sstf(requests, head);
                break;
        case 3: cout << "Enter direction (left/right): ";
                cin >> direction;
                scan(requests, head, diskSize, direction);
                break;
        case 4: cscan(requests, head, diskSize);
                break;
        default:cout << "Invalid choice.\n";
    }
    return 0;
}
