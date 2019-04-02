/* main_accordeur.h */
/*
  Créateur:    Bruno Gagnon, M. Sc.A
  Date:        2 septembre 2009
  Revisions:  

  DESCRIPTION : 
     Fichier d'entêtes principal pour un accordeur de guitare.
     Permet d'écouter les notes de guitare et d'obtenir l'erreur 
     sur l'accordement.
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
void initAccordeur();
void initAIC();
//void afficherMenu();
//void ajusterLED(int noCorde);
//int getCommandes();
//float genFrqCos(int , int);
//float genFrq_methode2(int , int);
//int min(int a, int b);
//int max(int a, int b);
//short * FIR_ASM (short *cPtr, short ech, const short h[], short *y);

#endif /* MAIN_ACCORDEUR_H_ */


