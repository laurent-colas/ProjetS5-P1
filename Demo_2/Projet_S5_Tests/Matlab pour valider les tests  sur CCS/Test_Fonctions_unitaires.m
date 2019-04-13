%%TEST FONCTION FFT MATLAB POUR VALIDER LA VERSION EN LANGAGE C SUR CCS
clear all 
close all 
clc

%%

    c = [1 3 6.7 254 -23];
    
    for i = 1:1:5
        x(i) = c(i);
    end
    for i = 6:1:256
        x(i) = 0;
    end

    X.cmplx = fft(x);
    X.real = real(X.cmplx);
    X.img = imag(X.cmplx);
    X.magn = abs(X.cmplx);
    X.phase = angle(X.cmplx);
    
%%    
%%TEST FONCTION MAGNITUDE_COMPLEX MATLAB POUR VALIDER LA VERSION EN LANGAGE C SUR CCS
    
    XREF.magn = abs(X.cmplx);
    
%%
%%TEST FONCTION PHASE_COMPLEX MATLAB POUR VALIDER LA VERSION EN LANGAGE C SUR CCS

    XREF.phase = angle(X.cmplx);
    
%%
%%TEST FONCTION MEAN MATLAB POUR VALIDER LA VERSION EN LANGAGE C SUR CCS

    b = [1 3 6.7 254 -23];
    
    for i = 1:1:5
        k(i) = b(i);
    end
    for i = 6:1:256
        k(i) = 0;
    end
    moyenne = mean(k);

%%
%%TEST FONCTION MAXI_ABS MATLAB POUR VALIDER LA VERSION EN LANGAGE C SUR CCS

    m = [1 3 6.7 254 -23];
    
    for i = 1:1:5
        n(i) = m(i);
    end
    for i = 6:1:256
        n(i) = 0;
    end
    maxi_abs = max(abs(n));

%%
%%TEST FONCTION MAXI_ABS MATLAB POUR VALIDER LA VERSION EN LANGAGE C SUR CCS

    valeur_neg = -3.14159265358979;

    valeur_absolue = abs(valeur_neg);

%%
%%TEST FONCTION fenetre_hamming MATLAB POUR VALIDER LA VERSION EN LANGAGE C SUR CCS

w = hamming(256);

%%
%%TEST FONCTION fenetre_hamming MATLAB POUR VALIDER LA VERSION EN LANGAGE C SUR CCS

w2 = triang(256);



