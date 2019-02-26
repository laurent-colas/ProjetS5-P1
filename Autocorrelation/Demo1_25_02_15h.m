%% clean and clear
clc 
close all
clearvars

%% Enregistrement du son

recObj = audiorecorder;

disp('Start speaking.')
recordblocking(recObj, 1);
disp('End of Recording.');

play(recObj);

y = getaudiodata(recObj);
plot(y)


%% Autocorrelation
clc 
close all
clearvars

% vecteur de test
x = [1 0 -1 0];
y = [1 0 -1 0 1 1 1 1 1 1];


corr = correlation(x,y);

figure
stem(corr)
