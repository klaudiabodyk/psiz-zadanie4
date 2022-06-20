#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cstdint>



void LogWrite(string info)
{
	ofstream log;
	time_t now = time(0);
	log.open("log.txt", fstream::app ); 
	log << localtime(&now )<< " | " << info <<endl;
	log.close();
}

int main(int argc, char * argv[])
{
	string filename1, filename2;
	ifstream file1, file2;
	ofstream log ("log.txt");
	LogWrite(" Start");
	if( argc = 3)
	{
		filename1 = argv[2];
		filename2 = argv[3];
		
		file1.open( filename1, ios::binary);
		file2.open( filename2, ios::binary);
		if(!file1.is_open())
		{
			cout<<"Error, file "+filename2+" not open."<<endl;
			LogWrite("Error, file "+filename1+" not open.");
			exit;
		}
		if(!file2.is_open())
		{
			cout<<"Error, file "+filename2+" not open."<<endl;
				LogWrite("Error, file "+filename2+" not open.");
			exit;
		}		
		file1.close();
		file2.close();
	}
	else
	{
	cout << "podano nieprawidlowa liczbe argumentow!" << endl;
	exit;	
	}
}