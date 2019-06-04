#include <iostream>
#include <fstream>
#include <cmath>
#include "Header.h"
using namespace std;
//this number ashould be smaller than the maximum adjustment 
const int ModNum = 29500; 

int main() {
	int Dev;
	int ThirtySecNumb;
	int C2 = 2;
	int C3 = 3;

	double Sum = 0,check=100000;
	double Limit_Lower_Peak;
	double Limit_Upper_Bottom;

	double time2[ModNum], Vol2[ModNum];
	double time3[ModNum], Vol3[ModNum];
	int TimeAdj = 200; //for 0.98 seconds

	ifstream inputfile22,inputfile11;

	inputfile22.open("ModTime.txt");


	cout << "devidnet= ";
	cin >> Dev;
	cout << endl << "Number of data points= ";
	cin >> ThirtySecNumb;

	cout << endl << "Limit_Lower_Peak= ";
	cin >> Limit_Lower_Peak;
	cout << endl << "Limit_Upper_Bottom =";
	cin >> Limit_Upper_Bottom;

	function(Dev, ThirtySecNumb, C2, 
           Limit_Lower_Peak, Limit_Upper_Bottom);

	for (int j = 0; j < ModNum; j++) {
		//for (int i = 0; i < 4; i++) {
		inputfile22 >> time2[j];
		inputfile22 >> Vol2[j];


	}

	function(Dev, ThirtySecNumb, C3, 
           Limit_Lower_Peak, Limit_Upper_Bottom);
	inputfile11.open("ModTime.txt");
	for (int j = 0; j < ModNum; j++) {
		//for (int i = 0; i < 4; i++) {
		inputfile11 >> time3[j];
		inputfile11 >> Vol3[j];

	}

	// Error checking


	for (int i = 25; i <180; i++) {
		for (int j = 0; j < (ModNum - i); j++) {
			Sum = Sum + abs(Vol3[j] - Vol2[j + i]);
		}
		if (Sum/(ModNum - i) < check) {
			check = Sum / (ModNum - i);
			cout << check << " " << " " <<i<<" "<< time2[i]<<endl;
		}
		Sum = 0;
	}
	//cout << check; 
	cin >> Sum;
}