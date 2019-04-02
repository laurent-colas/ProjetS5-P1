#include <stdio.h>
#include <math.h>
#include "functionHelperProjetS5.h"






float tableau_test_FFT[256];
#pragma DATA_SECTION(tableau_test_FFT,".EXT_RAM");

float out_real[256];
#pragma DATA_SECTION(out_real,".EXT_RAM");

float out_imag[256];
#pragma DATA_SECTION(out_imag,".EXT_RAM");

float out_magnitude[256];
#pragma DATA_SECTION(out_magnitude,".EXT_RAM");

float out_phase[256];
#pragma DATA_SECTION(out_phase,".EXT_RAM");

float tableau_test_mean[256];
#pragma DATA_SECTION(tableau_test_mean,".EXT_RAM");

float tableau_test_max_abs[256];
#pragma DATA_SECTION(tableau_test_max_abs,".EXT_RAM");

float tableau_Hamming[256];
#pragma DATA_SECTION(tableau_Hamming,".EXT_RAM");

float tableau_Triangle[256];
#pragma DATA_SECTION(tableau_Triangle,".EXT_RAM");


void main()
{
/*******************************************************************
 *  TEST DE LA FONCTION FFT
*******************************************************************/
    //void FFT(float tableau_in[N], float tableau_out_real[N/2],float tableau_out_imag[N/2] )
    int i;


    tableau_test_FFT[0]=1;
    tableau_test_FFT[1]=3;
    tableau_test_FFT[2]=6.7;
    tableau_test_FFT[3]=254;
    tableau_test_FFT[4]=-23;
    for(i=5;i<256;i++){
        tableau_test_FFT[i]=0;
    }


    FFT(tableau_test_FFT, out_real, out_imag );

    for (i=0; i<5; i++)
    {

    }

/*******************************************************************
 *  TEST DE LA FONCTION MAGNITUDE_COMPLEX
*******************************************************************/
//    void magnitude_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_magnitude[], int l);

    magnitude_complex(out_real, out_imag, out_magnitude, N);

    for (i=0; i<5; i++)
    {

    }



/*******************************************************************
 *  TEST DE LA FONCTION PHASE_COMPLEX
*******************************************************************/
//    void phase_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_phase[], int l);

    phase_complex(out_real, out_imag, out_phase, N);

    for (i=0; i<5; i++)
    {

    }

/*******************************************************************
 *  TEST DE LA FONCTION MEAN
*******************************************************************/
//    float mean(float tab[], int l);

    tableau_test_mean[0]=1;
    tableau_test_mean[1]=3;
    tableau_test_mean[2]=6.7;
    tableau_test_mean[3]=254;
    tableau_test_mean[4]=-23;
    for(i=5;i<256;i++){
        tableau_test_mean[i]=0;
    }

    float moyenne;
    moyenne = mean(tableau_test_mean, N);

    for (i=0; i<5; i++)
    {

    }

/*******************************************************************
 *  TEST DE LA FONCTION MAXI_ABS
*******************************************************************/
//    float maxi_abs(float tab[],int l);

    tableau_test_max_abs[0]=1;
    tableau_test_max_abs[1]=3;
    tableau_test_max_abs[2]=6.7;
    tableau_test_max_abs[3]=254;
    tableau_test_max_abs[4]=-23;
    for(i=5;i<256;i++){
        tableau_test_max_abs[i]=0;
    }

    float maximum_absolue;
    maximum_absolue = maxi_abs(tableau_test_max_abs, N);

    for (i=0; i<5; i++)
    {

    }

/*******************************************************************
 *  TEST DE LA FONCTION VAL_ABSOLUT
*******************************************************************/
//    float val_absolut(float val);

    float valeur_absolue;
    float val_neg = -3.14159265358979;
    valeur_absolue = val_absolut(val_neg);

    for (i=0; i<5; i++)
    {

    }



/*******************************************************************
*  TEST DE LA FONCTION FENETRE_HAMMING
*******************************************************************/

    fenetre_hamming(tableau_Hamming, N);


    for (i=0; i<5; i++)
    {

    }

/*******************************************************************
*  TEST DE LA FONCTION FENETRE_TRIANGLE
*******************************************************************/

    fenetre_triangle(tableau_Triangle, N);


    for (i=0; i<5; i++)
        {

        }

/*******************************************************************
 *  LISTE DES PROTOTYPES À TESTER
*******************************************************************/

    /* TESTÉ :  */

//    void magnitude_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_magnitude[], int l);
//    void phase_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_phase[], int l);
//    void FFT(float tableau_in[], float tableau_out_real[],float tableau_out_imag[]);
//    float mean(float tab[], int l);
//    float val_absolut(float val);
//    float maxi_abs(float tab[],int l);
//    void correlation(double x[], double y[],int l,double out[]);
//    void fenetre_hamming(float w[], int l);
//    void fenetre_triangle(float w[], int l);
//    double AutoCorrelation(double * tab1, int longueur, double * tab2);
//    void correlation(double x[], double y[],int l,double out[]);

    /* RESTE À TESTER :  */

//    void IFFT(float tableau_in_real[],float tableau_in_imag[],float tableau_out[]);
//    void pre_traitement(struct TABLEAU_INIT Ech[2], struct TABLEAU_REF  *Sig_Ref);
//    void analyse_son(struct TABLEAU_IDENT *x2, struct TABLEAU_REF *Sig_Ref);

//    float maxi(float tab[],int l);
//    short maxi_abs_short(short tab[],int l);

//    short mean_short(short tab[], int l);




}


interrupt void c_int11()
{

}
