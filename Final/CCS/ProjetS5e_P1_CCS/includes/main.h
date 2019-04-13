/* main.h */
/*

  DESCRIPTION : 
     Fichier d'entêtes principal pour le traitement de la voix
*/

#ifndef MAIN_ACCORDEUR_H_
#define MAIN_ACCORDEUR_H_

/*************************************************************
 Liste des structures
*************************************************************/



/*************************************************************
 Liste des prototypes de fonction
*************************************************************/
void attendre(float seconds);
interrupt void c_int11();
void initDSK();
short * FIR_ASM (short *cPtr, short ech, const short h[], short *y);

#endif /* MAIN_ACCORDEUR_H_ */


