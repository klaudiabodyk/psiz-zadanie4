#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cstdint>
#include <windows.h>
#include <vector> 
#include <sstream>

using namespace std;

void LogWrite(const string info)
{
    const string logpath = "log.txt";
    time_t now = time(NULL);
    char* datetime = ctime(&now);
    ofstream log;
    log.open(logpath, ios_base::app ); 
    string logtemp; 
    log << datetime + info + "\n";
    log.close();
}

uint8_t hammingDistance(uint8_t n1, uint8_t n2)
{
    uint8_t x = n1 ^ n2; // XOR
    uint8_t setBits = 0;
    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }
    return setBits;
}

void printSize(const string &address) {
    fstream motd(address.c_str(), ios::binary | ios::in | ios::ate);
    if (motd) {
        fstream::pos_type size = motd.tellg();
        cout << size << "B";
    }
    else {
        perror(address.c_str());
    }
}

bool Checkfile(const string path){
    vector<char> writable(path.begin(), path.end());
    writable.push_back('\0');
    if(INVALID_FILE_ATTRIBUTES == GetFileAttributes(&*writable.begin()) && GetLastError()==ERROR_FILE_NOT_FOUND){
        return false;
    }
    else{
        return true;
    }
}