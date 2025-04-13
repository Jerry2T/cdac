#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
using namespace std;

struct Process {
    int id, arrival_time, burst_time, priority, remaining_time;
    int completion_time, turnaround_time, waiting_time, response_time;
    bool started;
        Process(int i, int at, int bt, int p) {
        id = i;               arrival_time = at;
        burst_time = bt;      priority = p;
        remaining_time = bt;  completion_time = turnaround_time = waiting_time = 0;
        response_time = -1;   started = false;
    }
};

class Scheduler {
private:
    vector<Process> processes;
    vector<pair<int, int>> gantt;  // <process_id, time>    
    void reset() {
        for (auto& p : processes) {
            p.remaining_time = p.burst_time;
            p.completion_time = p.turnaround_time = p.waiting_time = 0;
            p.response_time = -1;
            p.started = false;
        }
        gantt.clear();
    }    
    void calculate_metrics() {
        for (auto& p : processes) {
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;
        }
    }
    
public:
    void add_process(int id, int arrival, int burst, int priority) {
        processes.push_back(Process(id, arrival, burst, priority));
    }
    
    void fcfs() {
        reset();
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.arrival_time < b.arrival_time;
        });
        int current_time = 0;
        
        for (auto& p : processes) {
            if (current_time < p.arrival_time) {
                gantt.push_back({-1, current_time});
                current_time = p.arrival_time;
            }            
            gantt.push_back({p.id, current_time});
            p.response_time = current_time - p.arrival_time;
            current_time += p.burst_time;
            p.completion_time = current_time;
        }        
        calculate_metrics();
        gantt.push_back({-1, current_time});
    }
    
    void round_robin(int quantum) {
        reset();        
        int current_time = 0, completed = 0;
        vector<int> ready_queue;
        vector<bool> in_queue(processes.size(), false);

        while (completed < processes.size()) {
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && !in_queue[i]) {
                    ready_queue.push_back(i);
                    in_queue[i] = true;
                }
            }            
            if (ready_queue.empty()) {
                int next_arrival = numeric_limits<int>::max();
                for (auto& p : processes) {
                    if (p.remaining_time > 0 && p.arrival_time < next_arrival) {
                        next_arrival = p.arrival_time;
                    }
                }
                gantt.push_back({-1, current_time});
                current_time = next_arrival;
                continue;
            }
            
            int idx = ready_queue.front();
            ready_queue.erase(ready_queue.begin());
            in_queue[idx] = false;            
            gantt.push_back({processes[idx].id, current_time});
            if (!processes[idx].started) {
                processes[idx].started = true;
                processes[idx].response_time = current_time - processes[idx].arrival_time;
            }
            
            int exec_time = min(quantum, processes[idx].remaining_time);
            current_time += exec_time;
            processes[idx].remaining_time -= exec_time;            
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrival_time > current_time - exec_time && 
                    processes[i].arrival_time <= current_time && 
                    processes[i].remaining_time > 0 && !in_queue[i]) {
                    ready_queue.push_back(i);
                    in_queue[i] = true;
                }
            }
            if (processes[idx].remaining_time == 0) {
                completed++;
                processes[idx].completion_time = current_time;
            } else {
                ready_queue.push_back(idx);
                in_queue[idx] = true;
            }
        }        
        calculate_metrics();
        gantt.push_back({-1, current_time});
    }
    
    void sjf() {
        reset();
        int current_time = 0, completed = 0;        
        while (completed < processes.size()) {
            int shortest_idx = -1, shortest_burst = numeric_limits<int>::max();            
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                    if (processes[i].burst_time < shortest_burst) {
                        shortest_burst = processes[i].burst_time;
                        shortest_idx = i;
                    }
                }
            }
            
            if (shortest_idx == -1) {
                int next_arrival = numeric_limits<int>::max();
                for (auto& p : processes) {
                    if (p.remaining_time > 0 && p.arrival_time < next_arrival) {
                        next_arrival = p.arrival_time;
                    }
                }
                gantt.push_back({-1, current_time});
                current_time = next_arrival;
            } else {
                gantt.push_back({processes[shortest_idx].id, current_time});
                processes[shortest_idx].response_time = current_time - processes[shortest_idx].arrival_time;
                current_time += processes[shortest_idx].burst_time;
                processes[shortest_idx].remaining_time = 0;
                processes[shortest_idx].completion_time = current_time;
                completed++;
            }
        }        
        calculate_metrics();
        gantt.push_back({-1, current_time});
    }
    
    void srtf() {
        reset();        
        int current_time = 0, completed = 0, prev = -1;
        
        while (completed < processes.size()) {
            int shortest_idx = -1;
            int shortest_remaining = numeric_limits<int>::max();            
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                    if (processes[i].remaining_time < shortest_remaining) {
                        shortest_remaining = processes[i].remaining_time;
                        shortest_idx = i;
                    }
                }
            }            
            if (shortest_idx == -1) {
                int next_arrival = numeric_limits<int>::max();
                for (auto& p : processes) {
                    if (p.remaining_time > 0 && p.arrival_time < next_arrival) {
                        next_arrival = p.arrival_time;
                    }
                }
                if (prev != -1) {
                    gantt.push_back({-1, current_time});
                    prev = -1;
                }
                current_time = next_arrival;
            } else {
                if (prev != processes[shortest_idx].id) {
                    gantt.push_back({processes[shortest_idx].id, current_time});
                    prev = processes[shortest_idx].id;
                }                
                if (!processes[shortest_idx].started) {
                    processes[shortest_idx].started = true;
                    processes[shortest_idx].response_time = current_time - processes[shortest_idx].arrival_time;
                }                
                int run_until = current_time + processes[shortest_idx].remaining_time;
                bool preempted = false;
                
                for (int i = 0; i < processes.size(); i++) {
                    if (i != shortest_idx && processes[i].arrival_time > current_time && 
                        processes[i].arrival_time < run_until && processes[i].remaining_time > 0) {
                        run_until = processes[i].arrival_time;
                        preempted = true;
                    }
                }
                
                int executed = run_until - current_time;
                processes[shortest_idx].remaining_time -= executed;
                current_time = run_until;                
                if (processes[shortest_idx].remaining_time == 0) {
                    processes[shortest_idx].completion_time = current_time;
                    completed++;
                    prev = -1;
                }
            }
        }        
        calculate_metrics();
        gantt.push_back({-1, current_time});
    }

    void priority_non_preemptive() {
        reset();
        int current_time = 0, completed = 0;        
        while (completed < processes.size()) {
            int highest_idx = -1;
            int highest_priority = numeric_limits<int>::max();            
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                    if (processes[i].priority < highest_priority) {
                        highest_priority = processes[i].priority;
                        highest_idx = i;
                    }
                }
            }
            
            if (highest_idx == -1) {                
                int next_arrival = numeric_limits<int>::max();
                for (auto& p : processes) {
                    if (p.remaining_time > 0 && p.arrival_time < next_arrival) {
                        next_arrival = p.arrival_time;
                    }
                }
                gantt.push_back({-1, current_time});
                current_time = next_arrival;
            } else {
                gantt.push_back({processes[highest_idx].id, current_time});
                processes[highest_idx].response_time = current_time - processes[highest_idx].arrival_time;
                current_time += processes[highest_idx].burst_time;
                processes[highest_idx].remaining_time = 0;
                processes[highest_idx].completion_time = current_time;
                completed++;
            }
        }        
        calculate_metrics();
        gantt.push_back({-1, current_time});
    }
    
    void priority_preemptive() {
        reset();        
        int current_time = 0, completed = 0,  prev = -1;        
        while (completed < processes.size()) {
            int highest_idx = -1, highest_priority = numeric_limits<int>::max();            
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                    if (processes[i].priority < highest_priority) {
                        highest_priority = processes[i].priority;
                        highest_idx = i;
                    }
                }
            }
            
            if (highest_idx == -1) {                
                int next_arrival = numeric_limits<int>::max();
                for (auto& p : processes) {
                    if (p.remaining_time > 0 && p.arrival_time < next_arrival) {
                        next_arrival = p.arrival_time;
                    }
                }
                if (prev != -1) {
                    gantt.push_back({-1, current_time});
                    prev = -1;
                }
                current_time = next_arrival;
            } else {
                if (prev != processes[highest_idx].id) {
                    gantt.push_back({processes[highest_idx].id, current_time});
                    prev = processes[highest_idx].id;
                }                
                if (!processes[highest_idx].started) {
                    processes[highest_idx].started = true;
                    processes[highest_idx].response_time = current_time - processes[highest_idx].arrival_time;
                }                
                int run_until = current_time + processes[highest_idx].remaining_time;
                bool preempted = false;                
                for (int i = 0; i < processes.size(); i++) {
                    if (processes[i].arrival_time > current_time && processes[i].arrival_time < run_until && 
                        processes[i].priority < processes[highest_idx].priority) {
                        run_until = processes[i].arrival_time;
                        preempted = true;
                    }
                }
                
                int executed = run_until - current_time;
                processes[highest_idx].remaining_time -= executed;
                current_time = run_until;                
                if (processes[highest_idx].remaining_time == 0) {
                    processes[highest_idx].completion_time = current_time;
                    completed++;
                    prev = -1;
                }
            }
        }        
        calculate_metrics();
        gantt.push_back({-1, current_time});
    }
    
    void display_results(string algorithm) {
        cout << "\n================================ " << algorithm << " ================================\n";
        cout << setw(5) << "PID" << setw(8) << "Arrival" << setw(8) << "Burst" << setw(8) << "Priority" 
             << setw(12) << "Completion" << setw(12) << "Turnaround" << setw(10) << "Waiting" << setw(10) << "Response\n";
        cout << "-----------------------------------------------------------------------------\n";
        
        float avg_tat = 0, avg_wt = 0, avg_rt = 0;        
        for (auto& p : processes) {
            cout << setw(5) << p.id << setw(8) << p.arrival_time << setw(8) << p.burst_time 
                 << setw(8) << p.priority << setw(12) << p.completion_time << setw(12) << p.turnaround_time 
                 << setw(10) << p.waiting_time << setw(10) << p.response_time << endl;            
            avg_tat += p.turnaround_time;
            avg_wt += p.waiting_time;
            avg_rt += p.response_time;
        }
        
        cout << "-----------------------------------------------------------------------------\n";
        cout << "Average:" << setw(36) << avg_tat/processes.size() << setw(12) << avg_wt/processes.size() 
             << setw(10) << avg_rt/processes.size() << endl;
        
        cout << "\nGantt Chart:\n";
        cout << "----------------------------------------------------------\n";
        for (int i = 0; i < gantt.size() - 1; i++) {
            cout << "| ";
            if (gantt[i].first == -1) cout << "IDLE";
            else cout << "P" << gantt[i].first;
            cout << " ";
        }
        cout << "|\n";        
        for (int i = 0; i < gantt.size(); i++) {
            cout << gantt[i].second << "\t";
        }
        cout << "\n----------------------------------------------------------\n";
    }
};

int main() {
    Scheduler scheduler;
    int n, choice, time_quantum = 0;    
    cout << "Enter number of processes: ";                             cin >> n;    
    for (int i = 0; i < n; i++) {
        int arrival, burst, priority;
        cout << "\nProcess " << i + 1 << " details:\nArrival time: ";  cin >> arrival;
        cout << "Burst time: ";                                        cin >> burst;
        cout << "Priority (lower value = higher priority): ";          cin >> priority;        
        scheduler.add_process(i + 1, arrival, burst, priority);
    }
    
    while (true) {
        cout << "\n--- CPU Scheduling Algorithms ---\n1. First Come First Serve (FCFS)\n";
        cout << "2. Round Robin (RR)\n3. Shortest Job First (Non-preemptive)\n";
        cout << "4. Shortest Remaining Time First (Preemptive)\n5. Priority (Non-preemptive)\n";
        cout << "6. Priority (Preemptive)\n0. Exit\nEnter choice: ";
        cin >> choice;        
        switch (choice) {
            case 0: return 0;
            case 1: scheduler.fcfs();
                    scheduler.display_results("FCFS");
                    break;
            case 2: cout << "Enter time quantum: ";
                    cin >> time_quantum;
                    scheduler.round_robin(time_quantum);
                    scheduler.display_results("Round Robin (TQ=" + to_string(time_quantum) + ")");
                    break;
            case 3: scheduler.sjf();
                    scheduler.display_results("SJF (Non-preemptive)");
                    break;
            case 4: scheduler.srtf();
                    scheduler.display_results("SRTF (Preemptive)");
                    break;
            case 5: scheduler.priority_non_preemptive();
                    scheduler.display_results("Priority (Non-preemptive)");
                    break;
            case 6: scheduler.priority_preemptive();
                    scheduler.display_results("Priority (Preemptive)");
                    break;
            default:cout << "Invalid choice!\n";
        }
    }    
    return 0;
}