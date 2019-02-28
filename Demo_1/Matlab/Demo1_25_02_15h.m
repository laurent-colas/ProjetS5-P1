%% clean and clear
clc 
close all
clearvars
%% Autocorrelation
%vecteur de test
t = 1:10;
s_ref = sin(3.14.*t./10);

figure
stem(s_ref)

[corr] = correlation(s_ref,s_ref,numel(s_ref));

disp('Le resultat de la correlation est:')
disp(['[ ' num2str(corr) ' ]'])



