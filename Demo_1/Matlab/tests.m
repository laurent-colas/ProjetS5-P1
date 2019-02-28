%% test1: deux signaux orthogonaux sans décalage
clear all
close all
clc

t = 1:100;

s_ref = sin(3.14.*t./10);
orto_ref = cos(3.14.*t./10);

[corr] = correlation(s_ref,orto_ref,numel(s_ref));

disp('Le resultat de la correlation est:')
disp(['[ ' num2str(corr) ' ]'])

maximum = max(abs(corr))

figure
stem(corr)

%% test2 détectecte seulement voix humaine
clear all
close all
clc

recObj = audiorecorder;

disp('Start speaking.')
recordblocking(recObj, 1);
disp('End of Recording.');

play(recObj);

y = getaudiodata(recObj);
figure
plot(y)

%%

disp('Start noise.')
recordblocking(recObj, 1);
disp('End of Recording.');

bruit = getaudiodata(recObj);

figure
plot(bruit)
%%
[autocorr] = correlation(y',y',numel(y));
[corr] = correlation(y',bruit',numel(y));

maximumauto = max(autocorr)
maximum = max(corr)

figure
stem(corr)

figure
stem(autocorr)
%% test3: deux signaux de longueur différente
clear all
close all
clc

t = 1:100;
s_ref = sin(3.14.*t./10);
petit_ref = s_ref;
petit_ref(end-10:end)=0;%Retirer 10 derniers points et remplacer par des zéros
 
figure
plot(t,s_ref)

figure
plot(t,petit_ref)

[corr] = correlation(s_ref,petit_ref,numel(s_ref));

disp('Le resultat de la correlation est:')
disp(['[ ' num2str(corr) ' ]'])

maximum = max(abs(corr))

figure
stem(corr)

%% test4: deux signaux identiques
clear all
close all
clc

t = 1:100;

s_ref = sin(3.14.*t./10);

[corr] = correlation(s_ref,s_ref,numel(s_ref));

disp('Le resultat de la correlation est:')
disp(['[ ' num2str(corr) ' ]'])

maximum = max(abs(corr))

figure
stem(corr)

%% test 5 deux signaux identiques décalés
clear all
close all
clc

t = 1:100;

s_ref = sin(3.14.*t./10);
s_ref_decal = sin(3.14.*t./10 -2);

[corr] = correlation(s_ref,s_ref_decal,numel(s_ref));

disp('Le resultat de la correlation est:')
disp(['[ ' num2str(corr) ' ]'])

maximum = max(abs(corr))

figure
stem(corr)
%% test6
clear all
close all
clc

t = 1:100;

s_ref = sin(3.14.*t./10);
y = awgn(s_ref,20);

[corr] = correlation(s_ref,y,numel(s_ref));

disp('Le resultat de la correlation est:')
disp(['[ ' num2str(corr) ' ]'])

maximum = max((corr))

figure
plot(t,y)

figure
plot(t,s_ref)

figure
stem(corr)