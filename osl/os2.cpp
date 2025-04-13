#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

class Process {
public:
    int id, arrival, burst, remaining, priority, start = -1, completion = 0;
    Process(int i, int a, int b, int p = 0) : id(i), arrival(a), burst(b), remaining(b), priority(p) {}
};

void printTable(const vector<Process>& processes) {
    cout << left << setw(10) << "PID" << setw(15) << "Arrival Time"<< setw(15) << "Burst Time" << setw(15) << "Priority" 
         << setw(15) << "Start Time"<< setw(15) << "Completion"<< setw(15) << "Turnaround"<< setw(15) << "Waiting" << endl;
    for (const auto& p : processes) {
        int tat = p.completion - p.arrival;
        int wt = tat - p.burst;
        cout << left << setw(10) << p.id << setw(15) << p.arrival << setw(15) << p.burst << setw(15) << p.priority
             << setw(15) << p.start<< setw(15) << p.completion << setw(15) << tat << setw(15) << wt << endl;
    }
}

bool compareArrival(const Process& a, const Process& b) { return a.arrival < b.arrival; }

void FCFS(vector<Process> processes) {
    sort(processes.begin(), processes.end(), compareArrival);
    int time = 0;
    for (auto& p : processes) {
        if (time < p.arrival) time = p.arrival;
        p.start = time;
        time += p.burst;
        p.completion = time;
    }
    cout << "\n--- FCFS Scheduling ---\n";
    printTable(processes);
}

void SRTF(vector<Process> processes, bool preemptive = true) {
    int time = 0, completed = 0, n = processes.size();
    vector<Process> original = processes;
    while (completed < n) {
        int idx = -1, minRemaining = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= time && processes[i].remaining > 0) {
                if (processes[i].remaining < minRemaining || (!preemptive && processes[i].start == -1)) {
                    minRemaining = processes[i].remaining;
                    idx = i;
                    if (!preemptive) break;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        if (processes[idx].start == -1) processes[idx].start = time;
        processes[idx].remaining--;
        time++;
        if (processes[idx].remaining == 0) {
            processes[idx].completion = time;
            completed++;
        }
        if (!preemptive && processes[idx].remaining > 0) {
            time += processes[idx].remaining;
            processes[idx].completion = time;
            processes[idx].remaining = 0;
            completed++;
        }
    }
    cout << "\n--- SRTF " << (preemptive ? "(Preemptive)" : "(Non-Preemptive)") << " Scheduling ---\n";
    printTable(processes);
}

void PriorityScheduling(vector<Process> processes, bool preemptive = true) {
    int time = 0, completed = 0, n = processes.size();
    while (completed < n) {
        int idx = -1, maxPriority = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= time && processes[i].remaining > 0) {
                if (processes[i].priority > maxPriority) {
                    maxPriority = processes[i].priority;
                    idx = i;
                    if (!preemptive) break;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        if (processes[idx].start == -1) processes[idx].start = time;
        processes[idx].remaining--;
        time++;
        if (processes[idx].remaining == 0) {
            processes[idx].completion = time;
            completed++;
        }
        if (!preemptive && processes[idx].remaining > 0) {
            time += processes[idx].remaining;
            processes[idx].completion = time;
            processes[idx].remaining = 0;
            completed++;
        }
    }
    cout << "\n--- Priority " << (preemptive ? "(Preemptive)" : "(Non-Preemptive)") << " Scheduling ---\n";
    printTable(processes);
}

void RoundRobin(vector<Process> processes, int quantum) {
    queue<int> q;
    int time = 0, completed = 0, n = processes.size();
    vector<bool> visited(n, false);
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= time && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
        if (!q.empty()) {
            int idx = q.front(); q.pop();
            if (processes[idx].start == -1) processes[idx].start = time;
            int exec = min(quantum, processes[idx].remaining);
            processes[idx].remaining -= exec;
            time += exec;
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival <= time && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
            if (processes[idx].remaining > 0) q.push(idx);
            else {
                processes[idx].completion = time;
                completed++;
            }
        } else { time++; }
    }
    cout << "\n--- Round Robin Scheduling (Quantum = " << quantum << ") ---\n";
    printTable(processes);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;    
    vector<Process> processes;    
    cout << "\nEnter process details:\n";
    for (int i = 0; i < n; i++) {
        int id, arrival, burst, priority;
        cout << "\nProcess " << (i+1) << ":\n";
        cout << "Process ID: ";
        cin >> id;
        cout << "Arrival Time: ";
        cin >> arrival;
        cout << "Burst Time: ";
        cin >> burst;
        cout << "Priority: ";
        cin >> priority;        
        processes.push_back(Process(id, arrival, burst, priority));
    }    
    FCFS(processes);
    SRTF(processes, false); // Non-preemptive
    SRTF(processes, true); // Preemptive
    PriorityScheduling(processes, false); // Non-preemptive
    PriorityScheduling(processes, true); // Preemptive    
    int quantum;
    cout << "\nEnter time quantum for Round Robin: ";
    cin >> quantum;
    RoundRobin(processes, quantum);    
    return 0;
}