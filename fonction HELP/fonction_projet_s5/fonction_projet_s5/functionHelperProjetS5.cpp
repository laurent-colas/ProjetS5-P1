
#include "pch.h"
#include "functionHelperProjetS5.h"
int i = 0;



void magnitude_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_magnitude[],int length) {
	for (i = 0; i < length; i++)
	{
		tableau_out_magnitude[i] = sqrt((tableau_in_real[i])*(tableau_in_real[i]) + (tableau_in_imag[i])*(tableau_in_imag[i]));
	}
}

void phase_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_phase[], int length) {
	for (i = 0; i < length; i++)
	{
		tableau_out_phase[i] = (float) atan2((double) tableau_in_imag[i],(double) tableau_in_real[i]);
	}
}

void fenetre_hamming(float w[], int length) {
	for (i = 0; i < length; i++)
	{
		w[i] = (float) (0.54 - 0.46*cos(2 * PI* i / length));
	}
}

void fenetre_triangle(float w[], int length) {
	if (length % 2 == 0) {
		for (i = 0; i < length / 2; i++)
		{
			w[i] = (((2 * i)) / (length));
		}
		for (i = length / 2; i < length; i++)
		{
			w[i] = (2 - ((2 * i)) / (length));
		}
	}
	/*else {
		for (i = 0; i <= length / 2; i++)
		{
			w[i] = ((2 * i) / (length + 1));
		}
		for (i = length / 2; i <= length; i++)
		{
			w[i] = (2 - ((2 * i) / (length + 1)));
		}
	}*/

}


