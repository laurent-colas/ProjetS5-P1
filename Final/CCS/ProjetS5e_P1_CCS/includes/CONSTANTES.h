/* Ce fichier contient quelques constantes d'intérêts qui sont partagées 
   par plusieurs fonctions */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#ifndef NB_CYCLES_PAR_SEC
#define NB_CYCLES_PAR_SEC 225000000		// Nombre de cycles par secondes
#endif

#ifndef NB_CORDES
#define NB_CORDES 6		// Nombre de cordes de guitare
#endif

#ifndef L_TAMPON
#define L_TAMPON 8192 //4096 //256 //16384  	// Longueur du tampon circulaire d'échantillons
#endif

#ifndef FS
#define FS 8000			// Fréquence d'échantillonnage
//#define FS 7417			// Fréquence d'échantillonnage
#endif

#define CHAR_CONFIG 'C'
#define CHAR_CONFIR1_CONFIG 'G'
#define CHAR_IDENTI 'I'

char tabId [10] = {'k','l','m','n','o','p','q','r','s','t'};

const short coefPBd [255]={
                          -1,
                         -13,
                           0,
                         -13,
                          -1,
                         -11,
                          -5,
                          -7,
                         -10,
                          -3,
                         -14,
                           1,
                         -16,
                           2,
                         -15,
                          -1,
                         -10,
                          -7,
                          -3,
                         -13,
                           5,
                         -18,
                          10,
                         -18,
                          10,
                         -12,
                           4,
                           0,
                          -5,
                          15,
                         -13,
                          27,
                         -16,
                          33,
                         -10,
                          29,
                           7,
                          18,
                          30,
                           3,
                          53,
                          -7,
                          68,
                          -4,
                          69,
                          14,
                          55,
                          44,
                          32,
                          80,
                          10,
                         107,
                           0,
                         116,
                          11,
                         101,
                          44,
                          66,
                          89,
                          24,
                         131,
                          -9,
                         152,
                         -16,
                         139,
                           9,
                          92,
                          59,
                          24,
                         116,
                         -43,
                         154,
                         -83,
                         150,
                         -81,
                          96,
                         -34,
                           0,
                          37,
                        -110,
                         100,
                        -199,
                         119,
                        -236,
                          71,
                        -205,
                         -45,
                        -122,
                        -203,
                         -22,
                        -356,
                          43,
                        -452,
                          28,
                        -456,
                         -89,
                        -363,
                        -291,
                        -210,
                        -523,
                         -64,
                        -710,
                           0,
                        -781,
                         -77,
                        -695,
                        -308,
                        -469,
                        -646,
                        -176,
                        -993,
                          67,
                       -1219,
                         131,
                       -1205,
                         -82,
                        -883,
                        -605,
                        -260,
                       -1382,
                         567,
                       -2283,
                        1437,
                       -3123,
                        2159,
                       -3718,
                        2569,
                       28847,
                        2569,
                       -3718,
                        2159,
                       -3123,
                        1437,
                       -2283,
                         567,
                       -1382,
                        -260,
                        -605,
                        -883,
                         -82,
                       -1205,
                         131,
                       -1219,
                          67,
                        -993,
                        -176,
                        -646,
                        -469,
                        -308,
                        -695,
                         -77,
                        -781,
                           0,
                        -710,
                         -64,
                        -523,
                        -210,
                        -291,
                        -363,
                         -89,
                        -456,
                          28,
                        -452,
                          43,
                        -356,
                         -22,
                        -203,
                        -122,
                         -45,
                        -205,
                          71,
                        -236,
                         119,
                        -199,
                         100,
                        -110,
                          37,
                           0,
                         -34,
                          96,
                         -81,
                         150,
                         -83,
                         154,
                         -43,
                         116,
                          24,
                          59,
                          92,
                           9,
                         139,
                         -16,
                         152,
                          -9,
                         131,
                          24,
                          89,
                          66,
                          44,
                         101,
                          11,
                         116,
                           0,
                         107,
                          10,
                          80,
                          32,
                          44,
                          55,
                          14,
                          69,
                          -4,
                          68,
                          -7,
                          53,
                           3,
                          30,
                          18,
                           7,
                          29,
                         -10,
                          33,
                         -16,
                          27,
                         -13,
                          15,
                          -5,
                           0,
                           4,
                         -12,
                          10,
                         -18,
                          10,
                         -18,
                           5,
                         -13,
                          -3,
                          -7,
                         -10,
                          -1,
                         -15,
                           2,
                         -16,
                           1,
                         -14,
                          -3,
                         -10,
                          -7,
                          -5,
                         -11,
                          -1,
                         -13,
                           0,
                         -13,
                          -1};


#endif /* CONSTANTES_H_ */
