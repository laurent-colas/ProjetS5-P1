%% Clean
clear all 
close all 
clc

%% test 1

t = 0:1000-1;
f = 500;
fe = 8000;
x_sin = sin(2*pi*(f/fe)*t);

%x = [0,1,2,3,4,5];
x_fft = fft(x_sin);
x_real = real(x_fft);
x_imag = imag(x_fft);
x_abs = abs(x_fft);

w = hamming(1000);
w = w';

x_sin_hamm = x_sin .* w;

n = 0:1000-1;
N = 1000-1;
w_hamm = 0.54 - 0.46.*cos(2.*pi.*(n./N));

%% fenetre triangle

L = 100;
%triag(L) = [];
if mod(L,2) == 0
    for n=1:L/2
        triag(n) = (2*n-1)/L;
    end
    for n=L/2+1:L
        triag(n) = 2-(2*n-1)/L;
    end
end
if mod(L,2) == 1
    for n=1:(L+1)/2
        triag(n) = (2*n)/(L+1);
    end
    for n=(L+1)/2+1:L
        triag(n) = 2-(2*n)/(L+1);
    end
end