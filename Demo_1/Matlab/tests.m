%% test1: deux signaux orthogonaux sans décalage
clear all
close all
clc

t = 1:100;

s_ref = sin(3.14.*t./10);           % f
orto_ref = sin((3.14/2).*t./10);    % f/2

[corr] = correlation(s_ref,orto_ref,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% disp('Le resultat de la correlation est:')
% disp(['[ ' num2str(corr) ' ]'])

maximum = max(abs(corr));

figure('NAME','test 1')
subplot(4,1,1)
plot(s_ref);
title('Signal 1')
subplot(4,1,2)
plot(orto_ref);
title('Signal 2')
subplot(4,1,3)
plot(autocorr)
title('Résultat auto-corrélation (Signal 1)')
subplot(4,1,4)
plot(corr)
title('Résultat corrélation')

if maximum >= 0.8
    disp('======================')
    disp('Test1:')
    disp('Détection réussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test1:')
    disp('Détection non réussie (allumer DEL 1)')
    disp('======================')
end
% %% test2 
% clear all
% %close all
% %clc
% 
% recObj = audiorecorder;
% disp('======================')
% disp('Start signal 1.')
% recordblocking(recObj, 1);
% disp('Stop signal 1.')
% disp('======================')
% play(recObj);
% 
% s_ref = getaudiodata(recObj);
% 
% pause(2)
% 
% disp('======================')
% disp('Start signal 2.')
% recordblocking(recObj, 1);
% disp('Stop signal 2.');
% disp('======================')
% 
% s_bruit = getaudiodata(recObj);
% 
% figure
% plot(s_bruit)
% 
% [corr] = correlation(s_bruit',s_ref',numel(s_bruit));
% [autocorr] = correlation(s_ref',s_ref',numel(s_bruit));
% 
% maximum = max(abs(corr));
% 
% figure('NAME','test 2')
% subplot(4,1,1)
% plot(s_ref');
% title('Signal 1')
% subplot(4,1,2)
% plot(s_bruit');
% title('Signal 2')
% subplot(4,1,3)
% plot(autocorr)
% title('Résultat auto-corrélation')
% subplot(4,1,4)
% plot(corr)
% title('Résultat corrélation')
% 
% %clc
% if maximum >= 0.8
%     disp('======================')
%     disp('Test2:')
%     disp('Détection réussie (allumer DEL 2)')
%     disp('======================')
% end
% 
% if maximum < 0.8
%     disp('======================')
%     disp('Test2:')
%     disp('Détection non réussie (allumer DEL 1)')
%     disp('======================')
% end
%% test2: deux signaux de longueur différente
clear all
%close all
%clc

t = 1:100;
s_ref = sin(3.14.*t./10);
petit_ref = s_ref;
petit_ref(end-34:end)=0;%Retirer 10 derniers points et remplacer par des zéros
 

[corr] = correlation(s_ref,petit_ref,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% disp('Le resultat de la correlation est:')
% disp(['[ ' num2str(corr) ' ]'])

maximum = max(abs(corr));

figure('NAME','test 2')
subplot(4,1,1)
plot(s_ref);
title('Signal 1')
subplot(4,1,2)
plot(petit_ref);
title('Signal 2')
subplot(4,1,3)
plot(autocorr)
title('Résultat auto-corrélation (Signal 1)')
subplot(4,1,4)
plot(corr)
title('Résultat corrélation')

%clc
if maximum >= 0.8
    disp('======================')
    disp('Test2:')
    disp('Détection réussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test2:')
    disp('Détection non réussie (allumer DEL 1)')
    disp('======================')
end

%% test3: deux signaux identiques
clear all
%close all
%clc

t = 1:100;

s_ref = sin(3.14.*t./10);

[corr] = correlation(s_ref,s_ref,numel(s_ref));

% disp('Le resultat de la correlation est:')
% disp(['[ ' num2str(corr) ' ]'])

maximum = max(abs(corr));

figure('NAME','test 3')
subplot(2,1,1)
plot(s_ref);
title('Signal 1')
subplot(2,1,2)
plot(corr)
title('Résultat auto-corrélation')

%clc
if maximum >= 0.8
    disp('======================')
    disp('Test3:')
    disp('Détection réussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test3:')
    disp('Détection non réussie (allumer DEL 1)')
    disp('======================')
end

%% test 4 deux signaux identiques décalés
clear all
%close all
%clc

t = 1:100;

s_ref = sin(3.14.*t./10);
s_ref_decal = sin(3.14.*t./10 -3.14/2);

[corr] = correlation(s_ref,s_ref_decal,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% disp('Le resultat de la correlation est:')
% disp(['[ ' num2str(corr) ' ]'])

maximum = max(abs(corr));

figure('NAME','test 4')
subplot(4,1,1)
plot(s_ref);
title('Signal 1')
subplot(4,1,2)
plot(s_ref_decal);
title('Signal 2')
subplot(4,1,3)
plot(autocorr)
title('Résultat auto-corrélation (Signal 1)')
subplot(4,1,4)
plot(corr)
title('Résultat corrélation')

%clc
if maximum >= 0.8
    disp('======================')
    disp('Test4:')
    disp('Détection réussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test4:')
    disp('Détection non réussie (allumer DEL 1)')
    disp('======================')
end
%% test5
clear all
%close all
%clc

t = 1:100;

s_ref = sin(3.14.*t./10);
s_bruit = awgn(s_ref,7);

[corr] = correlation(s_ref,s_bruit,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% disp('Le resultat de la correlation est:')
% disp(['[ ' num2str(corr) ' ]'])

maximum = max((corr));

figure('NAME','test 5')
subplot(4,1,1)
plot(s_ref);
title('Signal 1')
subplot(4,1,2)
plot(s_bruit);
ylim([-2,2]);
title('Signal 2')
subplot(4,1,3)
plot(autocorr)
title('Résultat auto-corrélation (Signal 1)')
subplot(4,1,4)
plot(corr)
title('Résultat corrélation')

%clc
if maximum >= 0.8
    disp('======================')
    disp('Test5:')
    disp('Détection réussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test5:')
    disp('Détection non réussie (allumer DEL 1)')
    disp('======================')
end