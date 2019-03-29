#pragma once

#include "pch.h"
#include <iostream>
#include <math.h>
#include <stdio.h>




#define PI 3.14159265359



void magnitude_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_magnitude[], int length);
void phase_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_phase[], int length);
void fenetre_hamming(float w[], int length);
void fenetre_triangle(float w[], int length);