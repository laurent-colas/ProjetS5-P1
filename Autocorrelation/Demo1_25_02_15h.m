%% clean and clear
clc 
close all
clearvars

% %% Enregistrement du son
% 
% recObj = audiorecorder;
% 
% disp('Start speaking.')
% recordblocking(recObj, 1);
% disp('End of Recording.');
% 
% play(recObj);
% 
% y = getaudiodata(recObj);
% plot(y)


%% Autocorrelation
clc 
close all
clearvars


x = [1 0 -1 0 ];
load('Sin_1k')

y = y';

corr = auto_correlation(y);

stem(corr)



