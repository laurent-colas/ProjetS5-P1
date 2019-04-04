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
#define L_TAMPON 256	// Longueur du tampon circulaire d'échantillons
#endif

#ifndef FS
#define FS 8000			// Fréquence d'échantillonnage
//#define FS 7417			// Fréquence d'échantillonnage
#endif


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
const short coefPH [255] = {4,
                          4,
                          5,
                          5,
                          5,
                          6,
                          6,
                          6,
                          7,
                          7,
                          8,
                          8,
                          9,
                          9,
                         10,
                         10,
                         11,
                         11,
                         12,
                         13,
                         13,
                         14,
                         14,
                         15,
                         16,
                         16,
                         17,
                         18,
                         18,
                         19,
                         19,
                         20,
                         20,
                         21,
                         21,
                         22,
                         22,
                         22,
                         22,
                         22,
                         22,
                         22,
                         21,
                         21,
                         20,
                         19,
                         18,
                         17,
                         16,
                         14,
                         13,
                         11,
                          9,
                          7,
                          4,
                          2,
                         -1,
                         -4,
                         -8,
                        -11,
                        -15,
                        -19,
                        -23,
                        -28,
                        -33,
                        -38,
                        -43,
                        -49,
                        -54,
                        -60,
                        -67,
                        -73,
                        -80,
                        -87,
                        -94,
                       -101,
                       -109,
                       -117,
                       -125,
                       -133,
                       -141,
                       -149,
                       -158,
                       -167,
                       -176,
                       -185,
                       -194,
                       -203,
                       -212,
                       -222,
                       -231,
                       -240,
                       -250,
                       -259,
                       -268,
                       -278,
                       -287,
                       -296,
                       -305,
                       -314,
                       -323,
                       -332,
                       -340,
                       -348,
                       -357,
                       -365,
                       -372,
                       -380,
                       -387,
                       -394,
                       -401,
                       -407,
                       -413,
                       -419,
                       -424,
                       -429,
                       -434,
                       -438,
                       -442,
                       -445,
                       -448,
                       -451,
                       -454,
                       -455,
                       -457,
                       -458,
                       -459,
                      32313,
                       -459,
                       -458,
                       -457,
                       -455,
                       -454,
                       -451,
                       -448,
                       -445,
                       -442,
                       -438,
                       -434,
                       -429,
                       -424,
                       -419,
                       -413,
                       -407,
                       -401,
                       -394,
                       -387,
                       -380,
                       -372,
                       -365,
                       -357,
                       -348,
                       -340,
                       -332,
                       -323,
                       -314,
                       -305,
                       -296,
                       -287,
                       -278,
                       -268,
                       -259,
                       -250,
                       -240,
                       -231,
                       -222,
                       -212,
                       -203,
                       -194,
                       -185,
                       -176,
                       -167,
                       -158,
                       -149,
                       -141,
                       -133,
                       -125,
                       -117,
                       -109,
                       -101,
                        -94,
                        -87,
                        -80,
                        -73,
                        -67,
                        -60,
                        -54,
                        -49,
                        -43,
                        -38,
                        -33,
                        -28,
                        -23,
                        -19,
                        -15,
                        -11,
                         -8,
                         -4,
                         -1,
                          2,
                          4,
                          7,
                          9,
                         11,
                         13,
                         14,
                         16,
                         17,
                         18,
                         19,
                         20,
                         21,
                         21,
                         22,
                         22,
                         22,
                         22,
                         22,
                         22,
                         22,
                         21,
                         21,
                         20,
                         20,
                         19,
                         19,
                         18,
                         18,
                         17,
                         16,
                         16,
                         15,
                         14,
                         14,
                         13,
                         13,
                         12,
                         11,
                         11,
                         10,
                         10,
                          9,
                          9,
                          8,
                          8,
                          7,
                          7,
                          6,
                          6,
                          6,
                          5,
                          5,
                          5,
                          4,
                          4};

const short coefPB[255] = {
                           5,
                                    -6,
                                     7,
                                    -7,
                                     6,
                                    -4,
                                     2,
                                     0,
                                    -2,
                                     5,
                                    -7,
                                     8,
                                    -9,
                                     9,
                                    -8,
                                     6,
                                    -3,
                                     0,
                                     4,
                                    -7,
                                    11,
                                   -13,
                                    15,
                                   -15,
                                    13,
                                   -10,
                                     5,
                                     0,
                                    -6,
                                    12,
                                   -17,
                                    22,
                                   -24,
                                    24,
                                   -21,
                                    16,
                                    -9,
                                     0,
                                    10,
                                   -19,
                                    28,
                                   -34,
                                    38,
                                   -37,
                                    33,
                                   -25,
                                    14,
                                     0,
                                   -15,
                                    30,
                                   -43,
                                    52,
                                   -57,
                                    57,
                                   -50,
                                    38,
                                   -21,
                                     0,
                                    22,
                                   -44,
                                    63,
                                   -77,
                                    84,
                                   -83,
                                    73,
                                   -55,
                                    30,
                                     0,
                                   -32,
                                    64,
                                   -91,
                                   111,
                                  -121,
                                   119,
                                  -105,
                                    79,
                                   -43,
                                     0,
                                    46,
                                   -91,
                                   130,
                                  -158,
                                   172,
                                  -170,
                                   150,
                                  -113,
                                    62,
                                     0,
                                   -66,
                                   131,
                                  -187,
                                   228,
                                  -250,
                                   247,
                                  -219,
                                   165,
                                   -91,
                                     0,
                                    99,
                                  -196,
                                   282,
                                  -346,
                                   382,
                                  -381,
                                   340,
                                  -260,
                                   144,
                                     0,
                                  -161,
                                   325,
                                  -476,
                                   598,
                                  -673,
                                   689,
                                  -634,
                                   501,
                                  -288,
                                     0,
                                   354,
                                  -759,
                                  1197,
                                 -1645,
                                  2078,
                                 -2474,
                                  2809,
                                 -3063,
                                  3222,
                                 29487,
                                  3222,
                                 -3063,
                                  2809,
                                 -2474,
                                  2078,
                                 -1645,
                                  1197,
                                  -759,
                                   354,
                                     0,
                                  -288,
                                   501,
                                  -634,
                                   689,
                                  -673,
                                   598,
                                  -476,
                                   325,
                                  -161,
                                     0,
                                   144,
                                  -260,
                                   340,
                                  -381,
                                   382,
                                  -346,
                                   282,
                                  -196,
                                    99,
                                     0,
                                   -91,
                                   165,
                                  -219,
                                   247,
                                  -250,
                                   228,
                                  -187,
                                   131,
                                   -66,
                                     0,
                                    62,
                                  -113,
                                   150,
                                  -170,
                                   172,
                                  -158,
                                   130,
                                   -91,
                                    46,
                                     0,
                                   -43,
                                    79,
                                  -105,
                                   119,
                                  -121,
                                   111,
                                   -91,
                                    64,
                                   -32,
                                     0,
                                    30,
                                   -55,
                                    73,
                                   -83,
                                    84,
                                   -77,
                                    63,
                                   -44,
                                    22,
                                     0,
                                   -21,
                                    38,
                                   -50,
                                    57,
                                   -57,
                                    52,
                                   -43,
                                    30,
                                   -15,
                                     0,
                                    14,
                                   -25,
                                    33,
                                   -37,
                                    38,
                                   -34,
                                    28,
                                   -19,
                                    10,
                                     0,
                                    -9,
                                    16,
                                   -21,
                                    24,
                                   -24,
                                    22,
                                   -17,
                                    12,
                                    -6,
                                     0,
                                     5,
                                   -10,
                                    13,
                                   -15,
                                    15,
                                   -13,
                                    11,
                                    -7,
                                     4,
                                     0,
                                    -3,
                                     6,
                                    -8,
                                     9,
                                    -9,
                                     8,
                                    -7,
                                     5,
                                    -2,
                                     0,
                                     2,
                                    -4,
                                     6,
                                    -7,
                                     7,
                                    -6,
                                     5};


#endif /* CONSTANTES_H_ */
