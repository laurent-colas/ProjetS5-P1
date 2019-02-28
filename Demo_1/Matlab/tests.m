%% FICHIER DE TEST DÉMO 1
% Les tests 1 à 5 sont effectués
% conséquement fichier "Plan de test.xlsx"
% dans la section "plan de test autocorrélation"


%% test 5.1: deux signaux orthogonaux sans décalage
clear all
close all
clc

% Création du signal spécifique au test
t = 1:100;
s_ref = sin(3.14.*t./10);           % f
orto_ref = sin((3.14/2).*t./10);    % f/2

% Corrélation
[corr] = correlation(s_ref,orto_ref,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% Affichage des signaux et résultats
figure('NAME','test 5.1')
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

% interprétation du résultat de la corrélation
maximum = max(abs(corr));

if maximum >= 0.8
    disp('======================')
    disp('Test 5.1:')
    disp('Détection réussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test 5.1:')
    disp('Détection non réussie (allumer DEL 1)')
    disp('======================')
end
%% test 5.2: deux signaux de longueur différente
clear all

% Création du signal spécifique au test
t = 1:100;
s_ref = sin(3.14.*t./10);
petit_ref = s_ref;
petit_ref(end-34:end)=0; %Retirer 34 derniers points et remplacer par des zéros
 
% Corrélation
[corr] = correlation(s_ref,petit_ref,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% Affichage des signaux et résultats
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

% interprétation du résultat de la corrélation
maximum = max(abs(corr));

if maximum >= 0.8
    disp('======================')
    disp('Test 5.2:')
    disp('Détection réussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test 5.2:')
    disp('Détection non réussie (allumer DEL 1)')
    disp('======================')
end

%% test 5.3: deux signaux identiques
clear all

% Création du signal spécifique au test
t = 1:100;
s_ref = sin(3.14.*t./10);

% Corrélation
[corr] = correlation(s_ref,s_ref,numel(s_ref));

% Affichage des signaux et résultats
figure('NAME','test 5.3')
subplot(2,1,1)
plot(s_ref);
title('Signal 1')
subplot(2,1,2)
plot(corr)
title('Résultat auto-corrélation')

% interprétation du résultat de la corrélation
maximum = max(abs(corr));

if maximum >= 0.8
    disp('======================')
    disp('Test 5.3:')
    disp('Détection réussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test 5.3:')
    disp('Détection non réussie (allumer DEL 1)')
    disp('======================')
end

%% test 5.4: deux signaux identiques décalés
clear all

% Création du signal spécifique au test
t = 1:100;
s_ref = sin(3.14.*t./10);
s_ref_decal = sin(3.14.*t./10 -3.14/2);

% Corrélation
[corr] = correlation(s_ref,s_ref_decal,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% Affichage des signaux et résultats
figure('NAME','test 5.4')
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

% interprétation du résultat de la corrélation
maximum = max(abs(corr));

if maximum >= 0.8
    disp('======================')
    disp('Test 5.4:')
    disp('Détection réussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test 5.4:')
    disp('Détection non réussie (allumer DEL 1)')
    disp('======================')
end
%% test 5.5
clear all

% Création du signal spécifique au test
t = 1:100;
s_ref = sin(3.14.*t./10);
s_bruit = awgn(s_ref,7);    % signal s_ref bruité gaussiennement avec un facteur SNR de 7

% Corrélation
[corr] = correlation(s_ref,s_bruit,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% Affichage des signaux et résultats
figure('NAME','test 5.5')
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

% interprétation du résultat de la corrélation
maximum = max((corr));

if maximum >= 0.8
    disp('======================')
    disp('Test 5.5:')
    disp('Détection réussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test 5.5:')
    disp('Détection non réussie (allumer DEL 1)')
    disp('======================')
end