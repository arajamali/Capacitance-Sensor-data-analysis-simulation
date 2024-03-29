#include <iostream>
#include <fstream>
#include <cmath>
#include "Header.h"
using namespace std;

int main()
{
	int Dev;
	int ThirtySecNumb;
	int Cc ;
	int PeakNum = 4500;
	int ModNum = 300000;
	double Limit_Lower_Peak ;
	double Limit_Upper_Bottom ;
	double V_TB;
	double FreqNum;
	cout<<"devidnet= ";
	cin >>  Dev;
	cout << endl << "Number of data points= ";
	cin >> ThirtySecNumb;
	cout << endl << "Capasitance number= ";
	cin >>  Cc;
	cout << endl << "Limit_Lower_Peak= ";
	cin >>  Limit_Lower_Peak;
	cout << endl << "Limit_Upper_Bottom =";
	cin >>  Limit_Upper_Bottom;
	cout << endl << "V_TB= ";
	cin >> V_TB;
	function(Dev, ThirtySecNumb, Cc, Limit_Lower_Peak, Limit_Upper_Bottom);
	int itr1 = 0, itr11 = 0;
	double L_s, L_f;
	ofstream x1;
	ifstream inputfile1, inputfile2,FreqnNum;
	inputfile1.open("Peak.txt");
	inputfile2.open("ModTime.txt");
	FreqnNum.open("FreqNum.txt");
	FreqnNum >> FreqNum;
	x1.open("check.txt");

	double *TimePeak, *PeakPoints, *TimeMod, *ModPoints, *MinForPeaksNum;
	TimePeak = new double[PeakNum];
	PeakPoints = new double[PeakNum];
	PeakPoints = new double[PeakNum];
	TimeMod = new double[ModNum];
	ModPoints = new double[ModNum];
	MinForPeaksNum = new double[PeakNum];
	//Data assignment to the new arrays
	//for (int pp = 0; pp < 20; pp++) {
		double check1 = 0, check2 = 0, check3 = 0;
		double sum = 0, sum1 = 0;
		double sumsum = 0, sum11 = 0;
		//double AvgPoints[PeakNum], AvgTime[PeakNum];
		double  AvgPoints_HLLS, AvgTime_HLLS;
		double  AvgPoints_HLTB, AvgTime_HLTB;
		int RealPeakNum = 0, RealModNum = 0, jj = 0, kk = 0;
		
   //Importing data from the files generated by the "func" 
		for (int j = 0; j < ModNum; j++) {
			inputfile2 >> check1;
			inputfile2 >> check2;
			if ((check3 - check1) != 0) {
				TimeMod[j] = check1;
				ModPoints[j] = check2;
				RealModNum = RealModNum + 1;
			}
			check3 = check1;
		}
		check1 = 0;
		check2 = 0;
		check3 = 0;
		for (int j = 0; j < PeakNum; j++) {
			inputfile1 >> check1;
			inputfile1 >> check2;
			if ((check3 - check1) != 0) {
				TimePeak[j] = check1;
				PeakPoints[j] = check2;
				RealPeakNum = RealPeakNum + 1;
			}
			check3 = check1;
		}
		check1 = 0;
		check2 = 0;
		check3 = 0;
		jj = 0;

		x1 << "Peak Numbers based on the given limits	"<<FreqNum<<endl;
		x1 << "Time_Botoom" << "	" << "Bottom"<<"	" << "Time_Peak" <<
         "	" << "Peak" <<"	" << "Time_HLLS" << "	" << "HLLS" << "	" <<
         "L_s" << "	" << "Time_HLTB" << "	" << "HLTB" << "	" << "L_f" << endl;
		
// Calculating L_s,L_f, H_LLS and H_TB and their associated times 
    // Slug pickups 		
		for (int i = 0; i < RealPeakNum; i++) { 
        // Start moving ahead to averaged data
			for (int j = jj; j < RealModNum; j++) { 
          //till you find the previous peak
				if (abs(ModPoints[j] - PeakPoints[i - 1]) < 0.001) {  
					if (abs(TimeMod[j] - TimePeak[i - 1]) < 0.001) { 
						kk = j;
					}
				}
        //find the current peak in averaged data 
				if (abs(ModPoints[j] - PeakPoints[i]) < 0.001) { 
					if (abs(TimeMod[j] - TimePeak[i]) < 0.001) {
						jj = j;
            // Then start moving back through the averaged data
						for (int k = j; k > 0; k--) {
                // till you find the minimum  
							if (ModPoints[k] < ModPoints[k - 1]) { 
                  // not just any minimum, the LUB
								if (ModPoints[k] < Limit_Upper_Bottom) { 
                    //store the number of LUB in your averaged data
									MinForPeaksNum[i] = k; 
                  // Now that you have the two ending points in your data
									for (int itr = k; itr < j; itr++) { 
                      //calculate the time and
										sum1 = sum1 + TimeMod[itr];
                    // the voltages from the averaged data
										sum = sum + ModPoints[itr]; 
										itr1 = itr1 + 1;
									}
									x1 << TimeMod[k] << "	" << ModPoints[k] << "	";
									//Hlls
                  //Continuation of averaging
									AvgPoints_HLLS = sum / (itr1); 
                  //Continuation of averaging
									AvgTime_HLLS = sum1 / (itr1); 
									sum = 0;
									sum1 = 0;
                  //Based on the input velocity, L_s is calculated
									L_s = V_TB*(TimeMod[j] - TimeMod[k]); 
									itr1 = 0;
									x1 << TimePeak[i]<<"	"<< PeakPoints[i]<<"	"
                     << AvgTime_HLLS << "	" << AvgPoints_HLLS << 
                     "	" << L_s <<"	";
                  //From the previous peak to next LUB
									for (int itr = kk; itr < k; itr++) { 
                      // average the time and 
										sum11 = sum11 + TimeMod[itr]; 
                    //voltage
										sumsum = sumsum + ModPoints[itr]; 
										itr11 = itr11 + 1;
									}
								
									//Hllf
                  //which is HLTB
									AvgPoints_HLTB = sumsum / (itr11); 
									AvgTime_HLTB = sum11 / (itr11);
									sumsum = 0;
									sum11 = 0;
                  //Based on the input velocity, L_F is calculated
									L_f = V_TB*(TimeMod[k] - TimeMod[kk]); 
									itr11 = 0;
									x1 << AvgTime_HLTB << "	" << AvgPoints_HLTB << "	" << L_f << endl;
									break;
								}
							}
						}
						break;
					}
				}
			}
		}
	x1.close();
}