%% clean and clear
clc 
close all
clearvars

%% Correlation
%vecteur de test
t = 1:10;
s_ref = sin(3.14.*t./10);

s_ref2 = sin(3.14.*t);

figure 
plot(s_ref)
figure
plot(s_ref2)

[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

seuil = max(abs(autocorr));
[corr] = correlation(s_ref,s_ref2,numel(s_ref));

val = max(abs(corr));

figure 
plot(autocorr)

figure
plot(corr)
% 
% disp("Le resultat de la correlation est:")
% disp(['[ ' num2str(autocorr) ' ]'])

