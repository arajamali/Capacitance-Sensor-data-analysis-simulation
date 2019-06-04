#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void function(int Dev, int N_D,int Cc, double Limit_Lower_Peak, double Limit_Upper_Bottom){

	double FreqNum = 0;
	ofstream peakFile, ModTimeFile, FreqnNum;
	ifstream inputfile, ReadFilmSep;
	inputfile.open("RayData2.txt");
	ReadFilmSep.open("FilmSep.txt");
	FreqnNum.open("FreqNum.txt");
	peakFile.open("Peak.txt");
	ModTimeFile.open("ModTime.txt");

		int m = 0, n = 0, itr1, nn = 0;
		double *Glob_Max, *Glob_time;
		double sum = 0, sum1 = 0, sum2 = 0, Ave_h, itr = 0;;
		double *time, *time_Mod, C1, C2, *C3, *C3_Mod, *peak, *time_Peack, B, *NumCount;

		Glob_Max = new double[N_D / Dev];
		Glob_time = new double[N_D / Dev];
		time = new double[N_D];
		time_Mod = new double[N_D / Dev + 1];
		C3 = new double[N_D];
		C3_Mod = new double[N_D / Dev + 1];
		peak = new double[N_D / Dev + 1];
		time_Peack = new double[N_D / Dev + 1];
		NumCount = new double[N_D / Dev + 1];

//{ Probe Allocation 

		if (Cc == 1) {
			for (int j = 0; j < N_D; j++) {
				//for (int i = 0; i < 4; i++) {
				inputfile >> time[j];
				inputfile >> C3[j];
				inputfile >> C1;
				inputfile >> C2;
				time[j] = time[j] * 4;
			}
		}

		if (Cc == 2) {
			for (int j = 0; j < N_D; j++) {
				//for (int i = 0; i < 4; i++) {
				inputfile >> time[j];
				inputfile >> C1;
				inputfile >> C3[j];
				inputfile >> C2;
				time[j] = time[j] * 4;

			}
		}

		if (Cc == 3) {
			for (int j = 0; j < N_D; j++) {
				//for (int i = 0; i < 4; i++) {
				inputfile >> time[j];
				inputfile >> C1;
				inputfile >> C2;
				inputfile >> C3[j];
				time[j] = time[j] * 4;
			}
		}

//}

// Averaging the data 
		for (int i = 0; i < N_D; i = i + Dev) {
			sum = 0, sum1 = 0;
			for (int j = 0; j < Dev; j++) {
				sum = sum + time[i + j];
				sum1 = sum1 + C3[i + j];

			}
			time_Mod[m] = sum / Dev;
			C3_Mod[m] = sum1 / Dev;
			m = m + 1;
		}
//}
		 
// Local Peak pick up{

		for (int i = 1; i < N_D / Dev + 1; i++) {
			if (C3_Mod[i] >= C3_Mod[i - 1]) { ////
				if (C3_Mod[i] >= C3_Mod[i + 1]) {
					if (C3_Mod[i] > Limit_Lower_Peak) {
						//peak[n] = (C3_Mod[i] + C3_Mod[i + 1]) / 2.0;
						peak[n] = C3_Mod[i];
						time_Peack[n] = (time_Mod[i]);
						NumCount[n] = i;
						n = n + 1;
					}

				}
			}
		}

//}

// True peak picking up (Global)
		for (int i = 0; i < n; i++) {
			itr1 = NumCount[i];
			for (int j = 1; j < 2000; j++) {
				if (itr1 + j + 1 < N_D) {
					if (C3_Mod[itr1 + j + 1] > C3_Mod[itr1 + j]) {
						if (C3_Mod[itr1 + j] < Limit_Upper_Bottom) {
							if ((itr1 + j) < NumCount[i + 1]) {
								Glob_Max[nn] = C3_Mod[itr1];
								Glob_time[nn] = time_Mod[itr1];
								nn = nn + 1;
							
								break;
							}
						}
					}
				}
			}
		}

//}


// Poor last point fixing {
		if (Glob_Max[nn - 1] != peak[n - 1]) {
			Glob_Max[nn] = peak[n - 1];
			Glob_time[nn] = time_Peack[n - 1];
		}

	//}
	
// Data file export{
		for (int i = 0; i < nn + 1; i++) {
			
				peakFile << Glob_time[i] << " " << Glob_Max[i] << endl;
			
		}
		for (int i = 0; i < (N_D) / Dev - 1; i++) { //It used to be (N_D-1000) but i changed it to N_D just
			
				ModTimeFile << time_Mod[i] << " " << C3_Mod[i] << endl;
			}
		
		FreqNum = FreqNum + nn+1;

	FreqnNum << FreqNum;

	ModTimeFile.close();
	peakFile.close();
	FreqnNum.close();
	//}
}

