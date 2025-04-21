#include <unordered_map> 
#include <algorithm> 
#include <iostream>
#include <vector>
#include <limits.h> 
using namespace std; 
 
void printMemory(vector<int> &memory){ 
    cout << "[ "; 
    for (int page : memory) { 
        cout << page << " "; 
    } 
    cout << "]" << endl; 
} 

int getValidInput(bool allowZero = false){ 
    int value; 
    while (true) { 
        cin >> value; 
        if (cin.fail() || value < 0 || (!allowZero && value == 0)){           
            cout<< "Invalid input! Please enter a valid positive number: ";  
        } else { 
            return value; 
        } 
    } 
} 
 
int FCFS(vector<int> pages, int frames){ 
    vector<int> memory; 
    int page_faults = 0; 
    cout << "\nFCFS Page Placement:" << endl; 
    for (int page : pages)  { 
        if (find(memory.begin(), memory.end(), page) == memory.end()) {  
            if (memory.size() < frames){ 
                memory.push_back(page); 
            }else{ 
                memory.erase(memory.begin()); 
                memory.push_back(page); 
            } 
            page_faults++; 
        } 
        printMemory(memory); 
    } 
    return page_faults; 
}

int LRU(vector<int> pages, int frames){ 
    vector<int> memory; 
    unordered_map<int, int> last_used; 
    int page_faults = 0; 
    cout << "\nLRU Page Placement:" << endl; 
 
    for (int i = 0; i < pages.size(); i++) { 
        int page = pages[i]; 
        if (find(memory.begin(), memory.end(), page) == memory.end()) {  
            if (memory.size() < frames) {                 
                memory.push_back(page); 
            }else{                                 
                int lru_page = memory[0]; 
                int min_last_used = last_used[lru_page]; 
                for (int p : memory){ 
                    if (last_used[p] < min_last_used){ 
                        lru_page = p; 
                        min_last_used = last_used[p]; 
                    } 
                }                                 
                memory.erase(remove(memory.begin(), memory.end(),lru_page),memory.end()); 
                memory.push_back(page); 
            } 
            page_faults++; 
        }         
        last_used[page] = i; 
        printMemory(memory);  
    } 
    return page_faults; 
}
int OPT(vector<int> pages, int frames){ 
    vector<int> memory; 
    int page_faults = 0; 
    cout << "\nOPT Page Placement:" << endl; 
 
    for (int i = 0; i < pages.size(); i++) { 
        int page = pages[i]; 
        if (find(memory.begin(), memory.end(), page) == memory.end()) {  
            if (memory.size() < frames) {                 
                memory.push_back(page); 
            }else{                                 
                int farthest_page = -1; 
                int farthest_index = -1; 
                for (int p : memory){ 
                    auto it = find(pages.begin() + i, pages.end(), p); 
                    if (it == pages.end()) { 
                        farthest_page = p; 
                        break; 
                    } else if (it - pages.begin() > farthest_index) { 
                        farthest_page = p; 
                        farthest_index = it - pages.begin(); 
                    } 
                }                                 
                memory.erase(remove(memory.begin(), memory.end(),farthest_page),memory.end()); 
                memory.push_back(page); 
            } 
            page_faults++; 
        }         
        printMemory(memory);  
    } 
    return page_faults; 
}

int main(){
    // Static input for testing
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int frames = 3;

    int faults_fcfs = FCFS(pages, frames);
    int faults_lru = LRU(pages, frames);
    int faults_opt = OPT(pages, frames);

    cout << "\nResults:" << endl;
    cout << "FCFS Page Faults: " << faults_fcfs << endl;
    cout << "LRU Page Faults: " << faults_lru << endl;
    cout << "OPT Page Faults: " << faults_opt << endl;

    return 0;
}