

	.def _AutoCorrelation
	;.def _Zero

	.data
	.text



_AutoCorrelation
	.asmfunc

		; Protection du CSR et de l'AMR sur la pile
	STW A3, *B15--[2]
	STW A2, *B15--[2]
	STW A8, *B15--[2]
	STW A10, *B15--[2]
	STW A12, *B15--[2]
	STW A13, *B15--[2]
	
	STW B12, *B15--[2]
	STW B13, *B15--[2]
	
	MVC	AMR, B5
	STW B5, *B15--[2]	;Push AMR sur la pile (sur ce DSP, le pointeur de pile doit toujour changer en multiples de 8 bytes)

	
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

	; Restauration de l'AMR et des registres de travail

	LDW *++B15[2], B5		;Pop AMR de la pile (sur ce DSP, le pointeur de pile doit toujour changer en multiples de 8 bytes)
	NOP 5
	MVC B5, AMR

	LDW *++B15[2], B13
	NOP 5
	LDW *++B15[2], B12
	NOP 5
	LDW *++B15[2], A13
	NOP 5
	LDW *++B15[2], A12
	NOP 5
	LDW *++B15[2], A10
	NOP 5
	LDW *++B15[2], A8
	NOP 5
	LDW *++B15[2], A2
	NOP 5
	LDW *++B15[2], A3
	NOP 5
	
	
	B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5
	.endasmfunc
