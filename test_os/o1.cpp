#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void execute_cp(const string &command){
    stringstream ss(command);
    string cmd,src,dest;
    ss>>cmd>>src>>dest;
    if(!fileExists(src)){
        cout<<"File "<<src<<" does not exist."<<endl;
        return;
    }
    if(fileExists(dest)){
        cout<<"File "<<dest<<" already exists."<<endl;
        return;
    }
    ifstream srcFile(src, ios::binary);
    ofstream destFile(dest, ios::binary);
    destFile<<srcFile.rdbuf();    
}

