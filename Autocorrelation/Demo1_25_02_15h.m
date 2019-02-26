%% clean and clear
clc 
close all
clearvars

%% Enregistrement du son
% 
% recObj1 = audiorecorder;
% 
% disp('Start speaking.')
% recordblocking(recObj1, 2);
% disp('End of Recording.');
% 
% %play(recObj1);
% 
% x = getaudiodata(recObj1);
% plot(x)
%%
t = 1:100;

x = sin(t);
noise = randn(numel(x),1);
noise = noise./max(abs(noise));

noise = noise.*max(x);

% y = x + noise';
y = t.^2;
%%

% figure
% subplot(2,1,1)
% plot(x)
% subplot(2,1,2)
% plot(y)
%% Autocorrelation
clc 
close all
clearvars

%vecteur de test
x = [-1 0 1 1];
y = [-1 0 1 1];

% 
% t = 1:100;
% 
% x = sin(t);
% y = cos(t);

[corr,lag] = correlation(x,y);

figure
stem(lag,corr)

%%

son = corr(1:(numel(corr)/2));

figure
plot(flip(son))
%%
sound(y,8000)