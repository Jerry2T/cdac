#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <limits>
using namespace std;

class Process {
public:
    int id, arrival_time, burst_time,       priority,       remaining_time; 
    int completion_time,  turnaround_time,  waiting_time,   response_time;   
    bool started;        

    Process(int id, int arrival, int burst, int priority) {
        this->id = id;              this->arrival_time = arrival;   this->burst_time = burst;
        this->priority = priority;  this->remaining_time = burst;   this->completion_time = 0;
        this->turnaround_time = 0;  this->waiting_time = 0;         this->response_time = -1;
        this->started = false;
    }
};

struct CompareFCFS {
    bool operator()(const Process& p1, const Process& p2) { return p1.arrival_time > p2.arrival_time; }
};

struct CompareSRTF {
    bool operator()(const Process& p1, const Process& p2) {
        if (p1.remaining_time == p2.remaining_time)  return p1.arrival_time > p2.arrival_time;
        return p1.remaining_time > p2.remaining_time;
    }
};

struct ComparePriority {
    bool operator()(const Process& p1, const Process& p2) {
        if (p1.priority == p2.priority)  return p1.arrival_time > p2.arrival_time;
        return p1.priority > p2.priority;
    }
};

class CPUScheduler {
private:
    vector<Process> processes;
    vector<pair<int, int>> gantt_chart;
public:
    void addProcess(int id, int arrival, int burst, int priority) {
        processes.push_back(Process(id, arrival, burst, priority));
    }

    void resetProcesses() {
        for (auto& p : processes) {
            p.remaining_time = p.burst_time;     p.completion_time = 0;
            p.turnaround_time = 0;               p.waiting_time = 0;
            p.response_time = -1;                p.started = false;
        }
        gantt_chart.clear();
    }

    void fcfs() {
        resetProcesses();
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.arrival_time < b.arrival_time;
        });        
        int current_time = 0;
        
        for (auto& p : processes) {            
            if (current_time < p.arrival_time) {
                gantt_chart.push_back({-1, current_time}); 
                current_time = p.arrival_time;
            }        
            gantt_chart.push_back({p.id, current_time});                        
            p.response_time = current_time - p.arrival_time;            
            current_time += p.burst_time;
            p.completion_time = current_time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;
        }        
        gantt_chart.push_back({-1, current_time});
    }
    
    void roundRobin(int time_quantum) {
        resetProcesses();        
        queue<int> ready_queue;
        vector<bool> in_ready_queue(processes.size(), false);        
        int current_time = 0, completed = 0;        
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrival_time == 0) {
                ready_queue.push(i);
                in_ready_queue[i] = true;
            }
        }
        
        while (completed < processes.size()) {
            if (ready_queue.empty()) {
                int next_arrival = numeric_limits<int>::max();
                for (int i = 0; i < processes.size(); i++) {
                    if (processes[i].remaining_time > 0 && processes[i].arrival_time < next_arrival) {
                        next_arrival = processes[i].arrival_time;
                    }
                }
                if (next_arrival > current_time) {
                    gantt_chart.push_back({-1, current_time});
                    current_time = next_arrival;
                }                
                for (int i = 0; i < processes.size(); i++) {
                    if (processes[i].arrival_time == current_time && processes[i].remaining_time > 0 && !in_ready_queue[i]) {
                        ready_queue.push(i);
                        in_ready_queue[i] = true;
                    }
                }
            }
            if (!ready_queue.empty()) {
                int idx = ready_queue.front();
                ready_queue.pop();
                in_ready_queue[idx] = false;
                gantt_chart.push_back({processes[idx].id, current_time});                
                if (!processes[idx].started) {
                    processes[idx].started = true;
                    processes[idx].response_time = current_time - processes[idx].arrival_time;
                }
                
                int execute_time = min(time_quantum, processes[idx].remaining_time);
                current_time += execute_time;
                processes[idx].remaining_time -= execute_time;
                
                for (int i = 0; i < processes.size(); i++) {
                    if (processes[i].arrival_time > current_time - execute_time && 
                        processes[i].arrival_time <= current_time && 
                        processes[i].remaining_time > 0 && 
                        !in_ready_queue[i]) {
                        ready_queue.push(i);
                        in_ready_queue[i] = true;
                    }
                }
                
                if (processes[idx].remaining_time == 0) {
                    completed++;
                    processes[idx].completion_time = current_time;
                    processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                    processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                }                 
                else {
                    ready_queue.push(idx);
                    in_ready_queue[idx] = true;
                }
            }
        }    
        gantt_chart.push_back({-1, current_time});
    }
    
    void sjf() {
        resetProcesses();
        int current_time = 0, completed = 0;
        while (completed < processes.size()) {
            int shortest_idx = -1;
            int shortest_burst = numeric_limits<int>::max();
                        
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
                for (int i = 0; i < processes.size(); i++) {
                    if (processes[i].remaining_time > 0 && processes[i].arrival_time < next_arrival) {
                        next_arrival = processes[i].arrival_time;
                    }
                }                                
                gantt_chart.push_back({-1, current_time});
                current_time = next_arrival;
            } else {                
                gantt_chart.push_back({processes[shortest_idx].id, current_time});                                
                processes[shortest_idx].response_time = current_time - processes[shortest_idx].arrival_time;                                
                current_time += processes[shortest_idx].burst_time;
                processes[shortest_idx].remaining_time = 0;                                
                processes[shortest_idx].completion_time = current_time;            
                processes[shortest_idx].turnaround_time = processes[shortest_idx].completion_time - processes[shortest_idx].arrival_time;
                processes[shortest_idx].waiting_time = processes[shortest_idx].turnaround_time - processes[shortest_idx].burst_time;                
                completed++;
            }
        }        
        gantt_chart.push_back({-1, current_time});
    }
    
    void srtf() {
        resetProcesses();        
        int current_time = 0, completed = 0, prev_running = -1;        
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
                for (int i = 0; i < processes.size(); i++) {
                    if (processes[i].remaining_time > 0 && processes[i].arrival_time < next_arrival) {
                        next_arrival = processes[i].arrival_time;
                    }
                }
                if (prev_running != -1) {
                    gantt_chart.push_back({-1, current_time});
                    prev_running = -1;
                }
                current_time = next_arrival;
            } else {             
                if (prev_running != processes[shortest_idx].id) {
                    gantt_chart.push_back({processes[shortest_idx].id, current_time});
                    prev_running = processes[shortest_idx].id;
                }               
                if (!processes[shortest_idx].started) {
                    processes[shortest_idx].started = true;
                    processes[shortest_idx].response_time = current_time - processes[shortest_idx].arrival_time;
                }
                current_time += 1;
                processes[shortest_idx].remaining_time -= 1;                
                if (processes[shortest_idx].remaining_time == 0) {
                    completed++;
                    processes[shortest_idx].completion_time = current_time;
                    processes[shortest_idx].turnaround_time = processes[shortest_idx].completion_time - processes[shortest_idx].arrival_time;
                    processes[shortest_idx].waiting_time = processes[shortest_idx].turnaround_time - processes[shortest_idx].burst_time;
                    prev_running = -1;
                }
            }
        }
        gantt_chart.push_back({-1, current_time});
    }
    
    void priorityNonPreemptive() {
        resetProcesses();       
        int current_time = 0, completed = 0;
        while (completed < processes.size()) {
            int highest_priority_idx = -1;
            int highest_priority = numeric_limits<int>::max();
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                    if (processes[i].priority < highest_priority) {
                        highest_priority = processes[i].priority;
                        highest_priority_idx = i;
                    }
                }
            }
            if (highest_priority_idx == -1) {
                int next_arrival = numeric_limits<int>::max();
                for (int i = 0; i < processes.size(); i++) {
                    if (processes[i].remaining_time > 0 && processes[i].arrival_time < next_arrival) {
                        next_arrival = processes[i].arrival_time;
                    }
                }                
                gantt_chart.push_back({-1, current_time});
                current_time = next_arrival;
            } else {
                gantt_chart.push_back({processes[highest_priority_idx].id, current_time});                
                processes[highest_priority_idx].response_time = current_time - processes[highest_priority_idx].arrival_time;    
                current_time += processes[highest_priority_idx].burst_time;
                processes[highest_priority_idx].remaining_time = 0;                
                processes[highest_priority_idx].completion_time = current_time;                
                processes[highest_priority_idx].turnaround_time = processes[highest_priority_idx].completion_time - processes[highest_priority_idx].arrival_time;
                processes[highest_priority_idx].waiting_time = processes[highest_priority_idx].turnaround_time - processes[highest_priority_idx].burst_time;            
                completed++;
            }
        }
        gantt_chart.push_back({-1, current_time});
    }
        
    void priorityPreemptive() {
        resetProcesses();        
        int current_time = 0, completed = 0, prev_running = -1;
        
        while (completed < processes.size()) {
            int highest_priority_idx = -1, highest_priority = numeric_limits<int>::max();            
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                    if (processes[i].priority < highest_priority) {
                        highest_priority = processes[i].priority;
                        highest_priority_idx = i;
                    }
                }
            }
            
            if (highest_priority_idx == -1) {
                int next_arrival = numeric_limits<int>::max();
                for (int i = 0; i < processes.size(); i++) {
                    if (processes[i].remaining_time > 0 && processes[i].arrival_time < next_arrival) {
                        next_arrival = processes[i].arrival_time;
                    }
                }
                if (prev_running != -1) {
                    gantt_chart.push_back({-1, current_time});
                    prev_running = -1;
                }
                current_time = next_arrival;
            } else {
                if (prev_running != processes[highest_priority_idx].id) {
                    gantt_chart.push_back({processes[highest_priority_idx].id, current_time});
                    prev_running = processes[highest_priority_idx].id;
                }
                if (!processes[highest_priority_idx].started) {
                    processes[highest_priority_idx].started = true;
                    processes[highest_priority_idx].response_time = current_time - processes[highest_priority_idx].arrival_time;
                }
                int next_time = current_time + processes[highest_priority_idx].remaining_time;
                for (int i = 0; i < processes.size(); i++) {
                    if (processes[i].arrival_time > current_time && processes[i].arrival_time < next_time && processes[i].priority < processes[highest_priority_idx].priority) {
                        next_time = processes[i].arrival_time;
                    }
                }
                
                int execute_time = next_time - current_time;                
                processes[highest_priority_idx].remaining_time -= execute_time;
                current_time = next_time;                
                if (processes[highest_priority_idx].remaining_time == 0) {
                    completed++;
                    processes[highest_priority_idx].completion_time = current_time;
                    processes[highest_priority_idx].turnaround_time = processes[highest_priority_idx].completion_time - processes[highest_priority_idx].arrival_time;
                    processes[highest_priority_idx].waiting_time = processes[highest_priority_idx].turnaround_time - processes[highest_priority_idx].burst_time;
                    prev_running = -1;
                }
            }
        }
        gantt_chart.push_back({-1, current_time});
    }
    
    void displayResults(const string& algorithm_name) {
        cout << "\n=======================================================================================" << endl;
        cout << algorithm_name << " Scheduling Results:" << endl;
        cout << "=======================================================================================" << endl;
        
        cout << setw(12) << "Process ID" << setw(15) << "Arrival Time" << setw(15) << "Burst Time" 
             << setw(15) << "Priority" << setw(15) << "Completion" << setw(15) << "Turnaround" 
             << setw(15) << "Waiting" << setw(15) << "Response" << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;        
        double avg_turnaround = 0, avg_waiting = 0, avg_response = 0;
        
        for (const auto& p : processes) {
            cout << setw(12) << p.id << setw(15) << p.arrival_time << setw(15) << p.burst_time 
                 << setw(15) << p.priority << setw(15) << p.completion_time << setw(15) << p.turnaround_time 
                 << setw(15) << p.waiting_time << setw(15) << p.response_time << endl;            
            avg_turnaround += p.turnaround_time;
            avg_waiting += p.waiting_time;
            avg_response += p.response_time;
        }        
        avg_turnaround /= processes.size();
        avg_waiting /= processes.size();
        avg_response /= processes.size();
        
        cout << "--------------------------------------------------------------------------------------" << endl;
        cout << "Average:" << setw(57) << avg_turnaround << setw(15) << avg_waiting << setw(15) << avg_response << endl;
        cout << "=======================================================================================" << endl;        
        cout << "\nGantt Chart:" << endl;
        cout << "----------------------------------------------------------------------------------" << endl;        
        for (int i = 0; i < gantt_chart.size() - 1; i++) {
            cout << "| ";
            if (gantt_chart[i].first == -1)  cout << "IDLE";
            else                             cout << "P" << gantt_chart[i].first;
            cout << " ";
        }
        cout << "|" << endl;
        
        for (int i = 0; i < gantt_chart.size(); i++) 
            cout << gantt_chart[i].second << "\t";
        cout << endl;
        cout << "----------------------------------------------------------------------------------" << endl;
    }
    vector<Process> getProcesses() { return processes; }
};

int main() {
    CPUScheduler scheduler;
    int n, choice, time_quantum = 0;    
    cout << "\n==== CPU Scheduling Simulator ====" << endl << "\nEnter the number of processes: ";
    cin >> n;    
    for (int i = 0; i < n; i++) {
        int arrival, burst, priority;        
        cout << "\nProcess " << i + 1 << ":" << endl;
        cout << "Arrival Time: ";                                   cin >> arrival;
        cout << "Burst Time: ";                                     cin >> burst;
        cout << "Priority (Lower value means higher priority): ";   cin >> priority;        
        scheduler.addProcess(i + 1, arrival, burst, priority);
    }
    
    while (true) {
        cout << "\n==== CPU Scheduling Algorithms ====" << endl << "1. First Come First Serve (FCFS)" << endl;
        cout << "2. Round Robin (RR)" << endl << "3. Shortest Job First (Non-Preemptive SRTF)" << endl;
        cout << "4. Shortest Remaining Time First (Preemptive SRTF)" << endl << "5. Priority Scheduling (Non-Preemptive)" << endl;
        cout << "6. Priority Scheduling (Preemptive)" << endl << "0. Exit" << endl << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: scheduler.fcfs();
                    scheduler.displayResults("First Come First Serve (FCFS)");
                    break;
            case 2: cout << "Enter Time Quantum: ";
                    cin >> time_quantum;
                    scheduler.roundRobin(time_quantum);
                    scheduler.displayResults("Round Robin (RR) with Time Quantum " + to_string(time_quantum));
                    break;
            case 3: scheduler.sjf();
                    scheduler.displayResults("Shortest Job First (Non-Preemptive SRTF)");
                    break;
            case 4: scheduler.srtf();
                    scheduler.displayResults("Shortest Remaining Time First (Preemptive SRTF)");
                    break;
            case 5: scheduler.priorityNonPreemptive();
                    scheduler.displayResults("Priority Scheduling (Non-Preemptive)");
                    break;
            case 6: scheduler.priorityPreemptive();
                    scheduler.displayResults("Priority Scheduling (Preemptive)");
                    break;
            case 0: cout << "Exiting program..." << endl;
                    return 0;
            default:cout << "Invalid choice. Please try again." << endl;
        }
    }    
    return 0;
}