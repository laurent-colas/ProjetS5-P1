

	.def _AutoCorrelation
	;.def _Zero

	.data
	.text



_AutoCorrelation
	.asmfunc



	MV A4, A10 ; L
	MV A5, A11 ; L
	MV B4, B0 ; L
	MV A6, A8
	MV A7, A9


	SUB B0, 1, B0 ;soustraire 1 du nombre


	ZERO A4
	ZERO A5

Boucle2:

	LDDW *A10++, B7:B6 ;Loader valeur du tableau dans A2
	NOP 4

	LDDW *A8++, A13:A12 ;Loader valeur du tableau dans A2
	NOP 4

	MPYDP B7:B6,A13:A12,B13:B12
	NOP 9

	ADDDP A5:A4, B13:B12 ,A5:A4
	SUB B0, 1, B0 ;soustraire 1 du nombre d'encryption

	[B0] B Boucle2
	NOP 5



	B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5
	.endasmfunc
