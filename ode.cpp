/*************************************************************************************
Filename:					ass3.cpp
Version:                    1.0.0.0
Author/Student Name:		Alexandre Dagher
Student Number:				040868750
Course Name and Number:		CST8233
Assignment Number:			Assignment 3
Assignment Name:			Transient-Response Analysis of 1st Order Systems
Due Date:					December 6th, 2019
Submission Date:			December 5th, 2019
Professor's Name:			Abdullah Kadri
Purpose:					Find the solution of 1st order Ordinary Differential Equations (ODE) using well known methods; namely, Euler’s and Runge-Kutta 4th Order Methods.
**************************************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

using namespace std;
void eulers();
void rungeKutta();

/**************************************************************************************
Function name:				main()
Purpose:					Driver For My Program
Function in parameters:		none
Function out parameters:	none
Version:					1.0.0.0
Author/Student Name:		Alexandre Dagher
***************************************************************************************/
int main(void) {
	// Driver
	int choice;
	bool done = 1;

	while (done) {
		cout << ">> Choose the method for solving the ODE:\n\n";
		cout << "1. Euler's Method\n\n2. Runge-Kutta 4th Order Method\n\n>> ";
		cin >> choice;
		switch (choice) {
		case 1:
			eulers();
			cout << endl << endl;
			break;
		case 2:
			rungeKutta();
			cout << endl << endl;
			break;
		default:
			cout << "\nPlease enter a valid option\n" << endl;
		}
	}
	return 0;
}

/**************************************************************************************
Function name:				euler's()
Purpose:					Calculate slope intercepts using Euler's to Method
Function in parameters:		none
Function out parameters:	none
Version:					1.0.0.0
Author/Student Name:		Alexandre Dagher
**************************************************************************************/
void eulers() {

	// Variables used for calculations
	double hValue = 0, xValue = 0, yValue = 3, estimatedTemp = 0, derivativeAtPoint = 0,
		exactTemp = 0, errorPercetage = 0, valForExact = 0;

	cout << "\n>> Choose step size \"h\" (0.8, 0.2, 0.05)\n\n>> ";

	// Error Checking For h Value
	while (hValue != 0.2 && hValue != 0.05 && hValue != 0.8) {
		cin >> hValue;
		if (hValue != 0.2 && hValue != 0.05 && hValue != 0.8) {
			cout << "\nInvalid Input, Choose step size \"h\" (0.8, 0.2, 0.05)\n\n>> ";
		}
	}

	cout << endl;

	cout << "Time(second) " << setw(20) << "Exact Temp   " << setw(20) << "  Estimated Temp   " << setw(20) << "  Percentage Error " << endl;

	while (xValue + hValue <= 2.01) {

		//Creating and Updating The X Value To Preform Exact Temp Calculations
		valForExact = valForExact + hValue;

		// Calculations For Estimated Temp(C)
		derivativeAtPoint = cos(4 * xValue) - (2 * yValue);
		estimatedTemp = yValue + ((derivativeAtPoint) * (hValue));

		//Calculations For Exact Temp(C)
		exactTemp = (0.1 * (cos(4 * valForExact)) + (0.2 * (sin(4 * valForExact)) + (2.9 * exp(-2 * valForExact))));

		// Calculations For Error Percentage
		errorPercetage = 100 * ((exactTemp - estimatedTemp) / exactTemp);

		// Error Checking to see if Error Percentage Goes Negative, So I Can Change Back To Postitive
		if (errorPercetage < 0) {
			errorPercetage = errorPercetage * -1;
		}

		// Updated New X Value and Y Value
		xValue = xValue + hValue;
		yValue = estimatedTemp;

		// Formating for printing to console
		cout << std::fixed << std::left;

		//Used to print values correctly
		if (hValue == 0.05) {
			cout << setprecision(2) << setw(20) << xValue;
		}
		else {
			cout << setprecision(1) << setw(20) << xValue;
		}

		cout << setprecision(3) << setw(16) << exactTemp;
		cout << setprecision(3) << setw(20) << estimatedTemp;
		cout << setprecision(2) << errorPercetage << endl;

	}
}

/**************************************************************************************
Function name:				rungeKutta()
Purpose:					Calculate slope intercepts using Runge-Kutta 4th method to Method
Function in parameters:		none
Function out parameters:	none
Version:					1.0.0.0
Author/Student Name:		Alexandre Dagher
**************************************************************************************/
void rungeKutta() {

	// Variables for calculating Runge-Kutta 4th method, Error Percentage and Exact Temp
	double yValue = 3, xValue = 0, k1, k2, k3, k4, hValue = 0, estimatedTemp;
	double a2 = 0.5, exactTemp = 0, valForExact = 0, errorPercetage = 0;

	cout << "\n>> Choose step size \"h\" (0.8, 0.2, 0.05)\n\n>> ";

	// Error Checking For h Value
	while (hValue != 0.2 && hValue != 0.05 && hValue != 0.8) {
		cin >> hValue;

		if (hValue != 0.2 && hValue != 0.05 && hValue != 0.8) {
			cout << "\nInvalid Input, Choose step size \"h\" (0.8, 0.2, 0.05)\n\n>> ";
		}
	}

	cout << endl;

	cout << "Time(second) " << setw(20) << "Exact Temp   " << setw(20) << "  Estimated Temp   " << setw(20) << "  Percentage Error " << endl;

	while (xValue + hValue <= 2.01) {

		//Creating and Updating The X Value To Preform Exact Temp Calculations
		valForExact = valForExact + hValue;

		// Calculating k Values then adding points ( Runge-Kutta 4th method )
		k1 = cos(4 * xValue) - (2 * yValue);
		k2 = cos(4 * (xValue + a2 * hValue)) - (2 * (yValue + a2 * k1 * hValue));
		k3 = cos(4 * (xValue + a2 * hValue)) - (2 * (yValue + a2 * k2 * hValue));
		k4 = cos(4 * (xValue + hValue)) - (2 * (yValue + k3 * hValue));
		estimatedTemp = yValue + (hValue / 6) * (k1 + (2 * k2) + (2 * k3) + k4);

		//Calculations For Exact Temp(C)
		exactTemp = (0.1 * (cos(4 * valForExact)) + (0.2 * (sin(4 * valForExact)) + (2.9 * exp(-2 * valForExact))));

		// Calculations For Error Percentage
		errorPercetage = 100 * ((exactTemp - estimatedTemp) / exactTemp);

		// Error Checking to see if Error Percentage Goes Negative, So I Can Change Back To Postitive
		if (errorPercetage < 0) {
			errorPercetage = errorPercetage * -1;
		}

		// Updated New X Value and Y Value to Calculate next point
		xValue = xValue + hValue;
		yValue = estimatedTemp;

		// Formatting for printing to console
		cout << std::fixed << std::left;

		//Used to print values correctly
		if (hValue == 0.05) {
			cout << setprecision(2) << setw(20) << xValue;
		}
		else {
			cout << setprecision(1) << setw(20) << xValue;
		}

		cout << setprecision(3) << setw(16) << exactTemp;
		cout << setprecision(3) << setw(20) << estimatedTemp;
		cout << setprecision(2) << errorPercetage << endl;
	}
}

