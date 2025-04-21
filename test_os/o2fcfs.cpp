#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<climits>
using namespace std;

struct Process{
    int id, remaining_time, completion_time, turnaround_time, waiting_time;
    int arrival_time, burst_time, priority;
};

void printtable(bool p, vector<Process>& proc){
    cout<<"\nProcess ID\t\tArrival Time\t\tBurst Time";
    if(p) cout<<"\t\tPriority";
    cout<<"\t\tCompletion Time\t\tTurnaround Time\t\tWaiting Time\n";
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------\n";
    for(int i=0; i<proc.size(); i++){
        cout<<proc[i].id<<"\t\t\t"<<proc[i].arrival_time<<"\t\t\t"<<proc[i].burst_time;
        if(p) cout<<"\t\t"<<proc[i].priority;
        cout<<"\t\t\t"<<proc[i].completion_time<<"\t\t\t"<<proc[i].turnaround_time<<"\t\t\t"<<proc[i].waiting_time<<endl;
    }
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------\n";
    
    int n=proc.size();
    double avg_waiting_time, avg_turnaround_time = 0;
    for(int i=0; i<proc.size(); i++){
        avg_turnaround_time += proc[i].turnaround_time;
        avg_waiting_time += proc[i].waiting_time;
    }
    cout<<"Average Turnaround Time: "<< avg_turnaround_time/n <<endl;    
    cout<<"Average Waiting Time: "<< avg_waiting_time/n <<endl;
}

void fcfs(vector<Process>& proc){
    int n=proc.size();
    sort(proc.begin(), proc.end(),[](Process a, Process b){ return a.arrival_time < b.arrival_time;});
    proc[0].completion_time = proc[0].arrival_time + proc[0].burst_time;
    proc[0].turnaround_time = proc[0].completion_time - proc[0].arrival_time;
    proc[0].waiting_time = 0;

    for(int i=1; i<n;i++){
        proc[i].waiting_time = max(0, proc[i-1].completion_time -proc[i].arrival_time);  
        proc[i].completion_time = proc[i].waiting_time + proc[i].burst_time + proc[i].arrival_time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }
    printtable(false, proc);
}

int main(){
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    vector<Process> proc(n);
    cout<<"Enter the arrival time, burst time and priority of each process:\n";
    for(int i=0; i<n; i++){
        proc[i].id = i+1;
        cin>>proc[i].arrival_time>>proc[i].burst_time>>proc[i].priority;
        proc[i].remaining_time = proc[i].burst_time;
    }
    
    cout<<"First Come First Serve Scheduling:\n";
    fcfs(proc);
    return 0;
}