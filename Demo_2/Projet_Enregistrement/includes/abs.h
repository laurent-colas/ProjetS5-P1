/*
 * abs.h
 *
 *  Created on: 26 févr. 2019
 *      Author: Nicolas
 */

#ifndef SOURCE_CODE_C_ABS_H_
#define SOURCE_CODE_C_ABS_H_


void absolute(double * tab, int taille_tab)
{
    int i;
    //double moy_liste = moyenne(tab,length);
    for ( i = 0; i<taille_tab;i++)
    {
        if (tab[i] < 0)
        {
            tab[i] = - tab[i];
        }
    }

}

#endif /* SOURCE_CODE_C_ABS_H_ */
