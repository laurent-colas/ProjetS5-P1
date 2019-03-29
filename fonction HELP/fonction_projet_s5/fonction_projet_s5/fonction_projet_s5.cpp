// fonction_projet_s5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "functionHelperProjetS5.h"

int main()


{
	const int length = 4;
	float tableau_in_real[length] = {2.41421356237310, - 1 ,- 0.414213562373095, - 1};
	float tableau_in_imag[length] = { 0	,1.11022302462516e-16	,0 ,- 1.11022302462516e-16 };
	float tableau_out_magnitude[length] = {0};
	float tableau_out_phase[length] = { 0 };

	float w[100] = {0};

	magnitude_complex(tableau_in_real,tableau_in_imag,tableau_out_magnitude,length);
	phase_complex(tableau_in_real, tableau_in_imag, tableau_out_phase, length);
	//fenetre_hamming(w,100);
	fenetre_triangle(w, 100);
    std::cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
