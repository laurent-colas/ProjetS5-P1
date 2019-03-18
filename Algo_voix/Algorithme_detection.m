%% clean and clear
clc 
close all
clearvars


%% 1. Enregistrement de la voix initial
recObj_ini = audiorecorder(16000,8,1);

disp('Dite votre nom.')
recordblocking(recObj_ini, 0.5);
disp('Enregistrement terminé');
x = getaudiodata(recObj_ini);
fen_ini = hamming(length(x));
x_fen = x .* fen_ini;

% Calcul de la FFT et déterminer les fréquences conséquentes
X = fft(x_fen);



%% 2. Detection de présence

recObj = audiorecorder(16000,8,1);
no_audio = 1;

while no_audio
    disp('Start speaking.')
    recordblocking(recObj, 0.2);
    disp('End of Recording.');

    y = getaudiodata(recObj);
    %y = y';

    w = hamming(length(y));
    y_fen = y.*w;

    % Enveloppe temporelle
    b = fir1(1999,pi./1000);
    enveloppe = filter(b,[1],abs(y_fen)).*2;
    if max(enveloppe) > 0.5
        no_audio = 0;
    end
end

figure(1)
subplot(3,1,1)
plot(y)
title('son original')
subplot(3,1,2)
plot(y_fen)
title('son fenetrer')
subplot(3,1,3)
plot(enveloppe)
title('envellope')

%% 3. Enregistrement du son

recObj = audiorecorder(16000,8,1);
disp('Start speaking 2.')
recordblocking(recObj, 0.5);
disp('End of Recording 2.');
y = getaudiodata(recObj);

w = hamming(length(y));
y_fen = y.*w;

Y = fft(y_fen);

%% 4. Analyse fft et correlation du signal

%[h] = correlation_fft(x_fen, y_fen);
[h_circ] = circ_correlation_fft(x_fen, y_fen);

plot(h_circ)
