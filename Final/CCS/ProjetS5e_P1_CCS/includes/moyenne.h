/*
 * moyenne.h
 *
 *  Created on: 26 févr. 2019
 *      Author: Nicolas
 */

#ifndef SOURCE_CODE_C_MOYENNE_H_
#define SOURCE_CODE_C_MOYENNE_H_

float moyenne (double * tab, int taille_tab)
{
    float somme = 0.0;
    float moy = 0.0;
    int i;
    for (i = 0; i<taille_tab; i++)
    {

        somme+=tab[i];

    }

    moy = somme/taille_tab;
    return moy;
}

#endif /* SOURCE_CODE_C_MOYENNE_H_ */
