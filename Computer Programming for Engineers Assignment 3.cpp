#include <iostream>
#include <cmath>
#include <string>

using namespace std;

//Global Array
double seavar[12] = {4.89,5.52,6.21,6.88,7.20,6.76,6.33,6.39,6.35,6.04,5.13,4.68}; // seavar = Seasonal Variation
//Global Variables
double SCF = 0.18; // Solar Cell Efficiency
double PIF = 0.90; // Power Inverter Efficiency
//Symbolic Constants
#define ARRROW 12 //Array Rows
#define ARRCOLUMN 24 //Array Columns
#define NOH 12 //Number Of Hours (Size of Array to be filled)
//function prototypes
void inputvaluefunction(double& DER,double& SP,double& PW,double& Batteriescost);
double fillInInsolation(double InsMat[][ARRCOLUMN], double ROWS);
double dailyInsolation(double* pointer, int N, int S);
double searchMaxValue(double InsMat[][ARRCOLUMN],int N);// Function to Search for the Maximum Value in Matrix
//Main Function
int main()
{
    double insolationmatrix[ARRROW][ARRCOLUMN];
    for(int i = 0; i < ARRROW; i++) // initialises the entire array to 0
        for(int j = 0; j < ARRCOLUMN; j++)
            insolationmatrix [i][j]= 0;
    double DER = 0,SP = 0 ,PI = 0,BatteriesCost = 0;
    inputvaluefunction(DER, SP, PI, BatteriesCost);
    
    double insolDayMin = 0;
    insolDayMin = fillInInsolation(insolationmatrix, ARRROW); //function call. stores the returned value from the function to the given variable
    
    double insolHourMax =0, *insolHourMaxPtr = &insolHourMax;
    *insolHourMaxPtr = searchMaxValue(insolationmatrix, ARRROW);//function call. stores the returned value to the variable pointed to by the pointer
    
    double area = 0;
    area = ((DER)/(SCF * insolDayMin))/PIF; // Formula to calculate the area of the solar panel

    int NOPI = 0; // Number of Power Inverters
    NOPI = ceil ((insolHourMax *(area/5))*(SCF/PIF));
    
    double NumberOfBatteries =0;
    NumberOfBatteries =(ceil(DER/4.8));
    
    double cost = 0;
    cost = ((area * SP) + (NOPI *PI) + (NumberOfBatteries)*BatteriesCost); //calculates the total cost of the solar power system. DER/4.8 calculate the number of batteries.
    cout << "The total cost for the installation of a flat-panel photovoltaic (""solarcell"") power system for residential home use in Abu Dhabi, United Arab Emirates is $ "<< cost;
    cout<< " This takes into consideration the number of Power Inverters being "<< NOPI<< ", the number of batteries needed which are "<< NumberOfBatteries<< " and the area in m^2 of the solar panel " << area <<endl;
    return 0;
}
void inputvaluefunction(double& DER,double& SP,double& PI,double& BatteriesCost)
{
    do{//loop to validate the input
    cout << "Enter the Daily Energy Requirement in kWh"<< endl;
    cin >> DER;
        if (DER<=0)
            cout<< "Invalid Value. Enter a positive value for the Daily Energy Requirement"<<endl;
    }while(DER<=0);
    
    do{//loop to validate the input
    cout << "Enter the Cost of the Solar Panels per square meter"<<endl;
    cin>> SP;
        if (SP<=0)
            cout<< "Invalid Value. Enter a positive value for the Cost of the Solar Panels per square meter"<<endl;
    }while(SP<=0);
    
    do{//loop to validate the input
    cout<< "Enter the Cost of the Power Inverters"<<endl;
    cin>> PI;
        if (PI<=0)
            cout<< "Invalid Value. Enter a positive value for the Cost of the Power Inverters"<<endl;
    }while(PI<=0);
    
    do{//loop to validate the input
     cout << "Enter the Cost of the Batteries"<<endl;
    cin>> BatteriesCost;
        if (BatteriesCost<=0)
            cout<< "Invalid Value. Enter a positive value for the Cost of the Batteries"<<endl;
    }while(BatteriesCost<=0);
}
//function to fill in the 2D array insolationmatrix by calling the dailyinsolation function to fill each row of the array
double fillInInsolation(double InsMat[][ARRCOLUMN], double ROWS)
{
    double totalDailyInsolation[ARRROW];
    double smallestDailyInsolation = 0;
    double* pointer;
    for (int i = 0;i < ROWS; i++){
        pointer = &InsMat[i][6]; //this statement inside a loop passes the starting address of each consecutive row in each run of the loop
        totalDailyInsolation[i] = dailyInsolation(pointer,NOH, i); // stores the total insolation of each day into an array
    }
    // to search for the smallest value in the array
    if (totalDailyInsolation[0]<totalDailyInsolation[1])
        smallestDailyInsolation=totalDailyInsolation[0];
    else
         smallestDailyInsolation=totalDailyInsolation[1];
    // the above statement executes a comparision between two consecutive values in the array and stores the lower value into the variable as a starting point
    for(int y = 0; y < ROWS; y++)
        if (totalDailyInsolation[y] < smallestDailyInsolation) // this follows the comparision for all other values in the array
            smallestDailyInsolation = totalDailyInsolation[y];
    return smallestDailyInsolation; // returns the minimum total daily insolation
}
//this function fills in the 2D array called insolationmatrix using its pointer and returns the total insolation from each day
double dailyInsolation(double* pointer, int N, int S){
    double totalDailyInsolation =0;
    int h = 7;
    for (int i=0; i < N; i++){
        *(pointer)= 2*seavar[S]*(cos(0.2618 *(h-12)));
        totalDailyInsolation += *(pointer);
        pointer++;
        h++;
    }
    return totalDailyInsolation;
}
// function to search the maximum value from the 2D array
double searchMaxValue(double InsMat[][ARRCOLUMN],int N)
{
    double max = 0;
    if (InsMat[1][1] > InsMat[1][2])
        max = InsMat[1][1];
    else
        max = InsMat[1][2];
    
    for (int a = 0; a < N; a++) // the following checks for the largest value in the array
        for (int b = 0; b < ARRCOLUMN; b++)
            if (InsMat[a][b]>max)
                max = InsMat[a][b];
    return max;
}
