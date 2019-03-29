/*
 * test.h
 *
 *  Created on: 27 f�vr. 2019
 *      Author: laure
 */

#ifndef SOURCE_C_TEST_H_
#define SOURCE_C_TEST_H_

#include "max.h"
#include "abs.h"


void test1(double t[], double s_ref[], double b_ref[]);
void test2(double t[], double s_ref[], double b_ref[]);
void test3(double t[], double s_ref[], double b_ref[]);
void test4(double t[], double s_ref[], double b_ref[]);
void init_vecteur(double s_ref[], double b_ref[]);

//Autocorr�lation
void test1(double t[], double s_ref[], double b_ref[]) {
    printf("\n Test 1 \n");
    int i;

    for (i = 0; i < length; i++) {
            s_ref[i] = sin(i*3.14 / length);
        }

    double out[2 * length - 1] = {0};
    correlation(s_ref, s_ref, length, out);


    printf("Le resultat de la correlation normalise est \n");
    printf("[ %f", out[0]);

    for (i = 1; i < 2 * length - 1; i++) {
        printf(", %f",out[i]);
    }
    printf("]");

    //absolute(out, 2 * length - 1);
    double lll = 2 * length - 1;
    double seuil = max(out, lll);

    printf("\n Le seuil est \n");
    printf(" %f", seuil);

    init_vecteur(s_ref, b_ref);


}

//Corr�lation entre sin et cos
void test2(double t[], double s_ref[], double b_ref[]) {
    printf("\n Test 2 \n");
    int i;

    for (i = 0; i < length; i++) {
            s_ref[i] = sin(i*3.14 / length);
        }

    for (i = 0; i< length; i++) {
        b_ref[i] = cos(i*3.14 / length);
    }

    double out[2 * length - 1] = {0};
    correlation(s_ref, b_ref, length, out);

    printf("Le resultat de la correlation normalise est \n");
    printf("[ %f", out[0]);


    for (i = 1; i < 2 * length - 1; i++) {
        printf(", %f",out[i]);
    }
    printf("]");


    double lll = 2 * length - 1;
    double seuil = max(out, lll);

    printf("\n Le seuil est \n");
    printf(" %f", seuil);

    init_vecteur(s_ref, b_ref);


}
//Vecteurs tailles diff�rentes
void test3(double t[], double s_ref[], double b_ref[]) {
    printf("\n Test 3 \n");
    int i;

    for (i = 0; i < length; i++) {
            s_ref[i] = sin(i*3.14 / length);
        }

    for (i = 0; i< length - 4; i++) {
        b_ref[i] = sin(i*3.14 / length);
    }

    double out[2 * length - 1] = {0};
    correlation(s_ref, b_ref, length, out);

    double seuil = max(out, 2 * length - 1);

    printf("Le resultat de la correlation normalise est \n");
    printf("[ %f", out[0]);


    for (i = 1; i < 2 * length - 1; i++) {
        printf(", %f",out[i]);
    }
    printf("]");

    printf("\n Le seuil est \n");
    printf(" %f", seuil);

    init_vecteur(s_ref, b_ref);
}

//Identiques mais d�cal�s
void test4(double t[], double s_ref[], double b_ref[]) {
    printf("\n Test 4 \n");
    int i;

    for (i = 0; i < length; i++) {
            s_ref[i] = sin(i*3.14 / length);
        }

    for (i = 0; i < length; i++) {
            b_ref[i] = sin((i-4)*3.14 / length);
        }

    double out[2 * length - 1] = {0};
    correlation(s_ref, b_ref, length, out);

    double seuil = max(out, 2 * length - 1);

    printf("Le resultat de la correlation normalise est \n");
    printf("[ %f", out[0]);


    for (i = 1; i < 2 * length - 1; i++) {
        printf(", %f",out[i]);
    }
    printf("]");

    printf("\n Le seuil est \n");
    printf(" %f", seuil);


    init_vecteur(s_ref, b_ref);
}


void init_vecteur(double s_ref[], double b_ref[]) {
    int i;
    for (i = 0; i < length; i++) {
            s_ref[i] = 0;
            b_ref[i] = 0;
        }
}



#endif /* SOURCE_C_TEST_H_ */