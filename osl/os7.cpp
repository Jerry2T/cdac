#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;

void printCache(const list<int>& cache) {
    cout << "Cache: ";
    for (int page : cache) {  cout << page << " ";   }
    cout << endl;
}

void fifoPageReplacement(vector<int> pages, int capacity) {
    queue<int> q;
    unordered_set<int> s;
    int page_faults = 0, page_hits = 0;
    list<int> cache;   
    for (int page : pages) {
        if (s.find(page) == s.end()) {
            cout << "Miss:  " << page << endl;
            if (q.size() == capacity) {
                int front = q.front();
                q.pop();
                s.erase(front);
                cache.remove(front);
            }
            q.push(page);
            s.insert(page);
            cache.push_back(page);
            page_faults++;
        } else {
            cout << "Hit:   " << page << endl;
            page_hits++;
        }
        printCache(cache);
    }
    cout << "FIFO - Page Faults: " << page_faults << " | Page Hits: " << page_hits << endl;
}

void optimalPageReplacement(vector<int> pages, int capacity) {
    unordered_set<int> s;
    int page_faults = 0, page_hits = 0;
    list<int> cache;   
    for (int i = 0; i < pages.size(); i++) {
        if (s.find(pages[i]) == s.end()) {
            cout << "Miss:  " << pages[i] << endl;
            if (s.size() == capacity) {
                int farthest = -1, indexToRemove;
                for (int page : s) {
                    auto it = find(pages.begin() + i, pages.end(), page);
                    if (it == pages.end()) {
                        indexToRemove = page;
                        break;
                    } else {
                        int distance = it - pages.begin();
                        if (distance > farthest) {
                            farthest = distance;
                            indexToRemove = page;
                        }
                    }
                }
                s.erase(indexToRemove);
                cache.remove(indexToRemove);
            }
            s.insert(pages[i]);
            cache.push_back(pages[i]);
            page_faults++;
        } else {
            cout << "Hit:   " << pages[i] << endl;
            page_hits++;
        }
        printCache(cache);
    }
    cout << "Optimal - Page Faults: " << page_faults << " | Page Hits: " << page_hits << endl;
}

void lruPageReplacement(vector<int> pages, int capacity) {
    unordered_map<int, list<int>::iterator> indexes;
    unordered_set<int> s;
    list<int> cache;
    int page_faults = 0, page_hits = 0;   
    for (int page : pages) {
        if (s.find(page) == s.end()) {
            cout << "Miss:  " << page << endl;
            if (s.size() == capacity) {
                int lru = cache.front();
                s.erase(lru);
                cache.pop_front();
            }
            cache.push_back(page);
            s.insert(page);
            page_faults++;
        } else {
            cout << "Hit:   " << page << endl;
            cache.erase(indexes[page]);
            cache.push_back(page);
            page_hits++;
        }
        indexes[page] = --cache.end();
        printCache(cache);
    }
    cout << "LRU - Page Faults: " << page_faults << " | Page Hits: " << page_hits << endl;
}

void mruPageReplacement(vector<int> pages, int capacity) {
    unordered_set<int> s;
    list<int> cache;
    int page_faults = 0, page_hits = 0;   
    for (int page : pages) {
        if (s.find(page) == s.end()) {
            cout << "Miss:  " << page << endl;
            if (s.size() == capacity) {
                int mru = cache.back();
                s.erase(mru);
                cache.pop_back();
            }
            cache.push_back(page);
            s.insert(page);
            page_faults++;
        } else {
            cout << "Hit:   " << page << endl;
            cache.remove(page);
            cache.push_back(page);
            page_hits++;
        }
        printCache(cache);
    }
    cout << "MRU - Page Faults: " << page_faults << " | Page Hits: " << page_hits << endl;
}

int main() {
    int choice, capacity, n, page;    
    cout << "Enter the number of pages ";                   cin >> n;
    vector<int> pages;
    cout << "Enter the pages (space separated):\n";
    for (int i = 0; i < n; i++) {
        cin >> page;
        pages.push_back(page);
    }    
    cout << "Enter cache capacity: ";                       cin >> capacity;       
    cout << "Choose Page Replacement Algorithm:\n";
    cout << "1. FIFO\n2. Optimal\n3. LRU\n4. MRU\nEnter choice: ";
    cin >> choice;   
    switch (choice) {
        case 1: fifoPageReplacement(pages, capacity);       break;
        case 2: optimalPageReplacement(pages, capacity);    break;
        case 3: lruPageReplacement(pages, capacity);        break;
        case 4: mruPageReplacement(pages, capacity);        break;
        default: cout << "Invalid choice!" << endl;
    }
    return 0;
}