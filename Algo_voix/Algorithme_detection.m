%% clean and clear
clc 
close all
clearvars

%% Enregistrement du son

recObj = audiorecorder(16000,8,1);
no_audio = 1;

while no_audio
    disp('Start speaking.')
    recordblocking(recObj, 0.5);
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

%play(recObj);
%plot(y)

