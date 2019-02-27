// correlation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
#include <iostream>
#define length 10
#include "max.h"
#include "abs.h"
#include "norm.h"
#include "correlation.h"


int main()
{
	double t[length];
	int i;
	double s_ref[length];
	for (i = 0; i < length; i++)
	{
		s_ref[i] = sin(i*3.14 / 10);
	}
	double out[2 * length - 1] = {0};
	correlation(s_ref, s_ref,length,out);
	printf("Le resultat de la correlation est \n");
	printf("[ %f", out[0]);

	i = 1;
	for (; i < 2 * length - 1; i++)
	{
		printf(", %f",out[i]);
	}
	printf("]");
}