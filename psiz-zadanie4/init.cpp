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

void FileComparation(const string file1path, const string file2path){
	char a{};
	char b{};
	int biterror;
	long long int numberofbytes;
	float BER =0;
	cout<<" rozpoczynam porownywanie plikow "<<endl;
	if (file1path == file2path) {
		cout<<" podano nazwe tego samego pliku dwa razy. Przewidywany BER = 0"<<endl;
		LogWrite(" podano nazwe tego samego pliku dwa razy. Przewidywany BER = 0");
	}
	if (!Checkfile(file1path)==false) {
		cout<<"  nie znaleziono pliku :" + file1path <<endl;
		LogWrite(" nie znaleziono pliku :" + file1path);
	}
	if (!Checkfile(file2path)==false)  {
		cout<<"  nie znaleziono pliku :" + file2path <<endl;
		LogWrite(" nie znaleziono pliku :" + file2path);
	}
	if ((Checkfile(file1path)==true) && (Checkfile(file2path)==true)){
		cout<< "rozpoczeto obliczanie BER ... \n";
		LogWrite("rozpoczeto obliczanie BER ...");
		ifstream plik1(file1path, ios::binary | ios::in);
		ifstream plik2(file2path, ios::binary | ios::in);
		int i = 0;
		while(!plik1.eof()){
			plik1 >> a;
			plik2 >> b;
			
			if (plik1.eof()) { break; } 
			if (plik2.eof()) { break; }
			
			
			numberofbytes = numberofbytes + 8;
			BER = hammingDistance(a, b) + BER;
			}
		plik1.close();
		plik2.close();
		
		stringstream stream;
		stream << std::fixed << std::setprecision(0) << BER;
		std::string s = stream.str();
		cout<< " Obliczony BER = "+s<<endl;
		LogWrite(" Obliczony BER = "+s);
	}
	
}

int main(int argc, char * argv[])
{
	string filename1, filename2;

	LogWrite(" Start");
	cout<<argc<<endl;
	if( argc = 3)
	{
		filename1 = argv[1];
		cout<<filename1+" wczytano plik1"<<endl;
		filename2 = argv[2];
		cout<<filename2+" wczytano plik2"<<endl;
		printSize(filename1);
		printSize(filename2);
		FileComparation(filename1,filename2);
	}
	else
	{
	cout << "podano nieprawidlowa liczbe argumentow!" << endl;
	exit;	
	}


}