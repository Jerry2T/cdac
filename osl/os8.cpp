#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
#include<cmath>
using namespace std;

void fcfs(vector<int> request,int head){
    int seek = 0;
    cout<<"Sequence of requests: ";
    for(auto i: request){
        cout<<i<<" ";
        seek += abs(head-i);
        head=i;
    }
    cout<<"\nTotal seek time: "<<seek<<endl;
}

void sstf(vector<int> request,int head){
    int seek=0;
    vector<bool> visited(request.size(), false);
    cout<<"Sequence of requests: ";
    for(int i=0;i<request.size(); i++){
        int minDistance = INT_MAX, index=-1;
        for(int j=0;j<request.size();j++){
            if(!visited[j] && abs(request[j]-head)<minDistance){
                minDistance=abs(request[j]-head);
                index=j;
            }
        }
        visited[index]=true;
        seek+=abs(head-request[index]);
        head=request[index];
        cout<<head<<" ";
    }
    cout<<"\nTotal seek time: "<<seek<<endl;
}

void scan(vector<int> request, int head,int diskSize ,string direction){
    int seek = 0;
    vector<int> left, right, seekSequence;
    if (direction == "left") left.push_back(0);
    else right.push_back(diskSize - 1);


    // Implement Scan here
}

int main(){
    int n, head, choice;
    vector<int> request(n);
    cout<<"Enter the number of requests: ";
    cin>>n;    
    cout<<"Enter the requests: ";
    for(int i=0;i<n;i++){
        cin>>request[i];
    }    
    cout<<"Enter the initial head position: ";
    cin>>head;

    cout<<"1: FCFS Disk Scheduling Algorithm\n";
    cout<<"2: SSTF Disk Scheduling Algorithm\n";
    cout<<"3: Scan Scheduling Algorithm\n";
    cout<<"4: C-Scan Disk Scheduling Algorithm\n";
    cin>>choice;

    switch (choice){
        case 1: cout<<"FCFS Disk Scheduling Algorithm\n";
                fcfs(request, head);
                break;
        case 2: cout<<"SSTF Disk Scheduling Algorithm\n";
                sstf(request, head);
                break;
        case 3: cout<<"Scan Scheduling Algorithm\n";
                // Implement Scan here
                break;
        case 4: cout<<"C-Scan Disk Scheduling Algorithm\n";
                // Implement C-Scan here
                break;
    default:cout<<"Invalid choice"<<endl;                
    }

    return 0;
}