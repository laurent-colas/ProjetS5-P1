%% FICHIER DE TEST D�MO 1
% Les tests 1 � 5 sont effectu�s
% cons�quement fichier "Plan de test.xlsx"
% dans la section "plan de test autocorr�lation"


%% test 5.1: deux signaux orthogonaux sans d�calage
clear all
close all
clc

% Cr�ation du signal sp�cifique au test
t = 1:100;
s_ref = sin(3.14.*t./10);           % f
orto_ref = sin((3.14/2).*t./10);    % f/2

% Corr�lation
[corr] = correlation(s_ref,orto_ref,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% Affichage des signaux et r�sultats
figure('NAME','test 5.1')
subplot(4,1,1)
plot(s_ref);
title('Signal 1')
subplot(4,1,2)
plot(orto_ref);
title('Signal 2')
subplot(4,1,3)
plot(autocorr)
title('R�sultat auto-corr�lation (Signal 1)')
subplot(4,1,4)
plot(corr)
title('R�sultat corr�lation')

% interpr�tation du r�sultat de la corr�lation
maximum = max(abs(corr));

if maximum >= 0.8
    disp('======================')
    disp('Test 5.1:')
    disp('D�tection r�ussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test 5.1:')
    disp('D�tection non r�ussie (allumer DEL 1)')
    disp('======================')
end
%% test 5.2: deux signaux de longueur diff�rente
clear all

% Cr�ation du signal sp�cifique au test
t = 1:100;
s_ref = sin(3.14.*t./10);
petit_ref = s_ref;
petit_ref(end-34:end)=0; %Retirer 34 derniers points et remplacer par des z�ros
 
% Corr�lation
[corr] = correlation(s_ref,petit_ref,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% Affichage des signaux et r�sultats
figure('NAME','test 2')
subplot(4,1,1)
plot(s_ref);
title('Signal 1')
subplot(4,1,2)
plot(petit_ref);
title('Signal 2')
subplot(4,1,3)
plot(autocorr)
title('R�sultat auto-corr�lation (Signal 1)')
subplot(4,1,4)
plot(corr)
title('R�sultat corr�lation')

% interpr�tation du r�sultat de la corr�lation
maximum = max(abs(corr));

if maximum >= 0.8
    disp('======================')
    disp('Test 5.2:')
    disp('D�tection r�ussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test 5.2:')
    disp('D�tection non r�ussie (allumer DEL 1)')
    disp('======================')
end

%% test 5.3: deux signaux identiques
clear all

% Cr�ation du signal sp�cifique au test
t = 1:100;
s_ref = sin(3.14.*t./10);

% Corr�lation
[corr] = correlation(s_ref,s_ref,numel(s_ref));

% Affichage des signaux et r�sultats
figure('NAME','test 5.3')
subplot(2,1,1)
plot(s_ref);
title('Signal 1')
subplot(2,1,2)
plot(corr)
title('R�sultat auto-corr�lation')

% interpr�tation du r�sultat de la corr�lation
maximum = max(abs(corr));

if maximum >= 0.8
    disp('======================')
    disp('Test 5.3:')
    disp('D�tection r�ussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test 5.3:')
    disp('D�tection non r�ussie (allumer DEL 1)')
    disp('======================')
end

%% test 5.4: deux signaux identiques d�cal�s
clear all

% Cr�ation du signal sp�cifique au test
t = 1:100;
s_ref = sin(3.14.*t./10);
s_ref_decal = sin(3.14.*t./10 -3.14/2);

% Corr�lation
[corr] = correlation(s_ref,s_ref_decal,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% Affichage des signaux et r�sultats
figure('NAME','test 5.4')
subplot(4,1,1)
plot(s_ref);
title('Signal 1')
subplot(4,1,2)
plot(s_ref_decal);
title('Signal 2')
subplot(4,1,3)
plot(autocorr)
title('R�sultat auto-corr�lation (Signal 1)')
subplot(4,1,4)
plot(corr)
title('R�sultat corr�lation')

% interpr�tation du r�sultat de la corr�lation
maximum = max(abs(corr));

if maximum >= 0.8
    disp('======================')
    disp('Test 5.4:')
    disp('D�tection r�ussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test 5.4:')
    disp('D�tection non r�ussie (allumer DEL 1)')
    disp('======================')
end
%% test 5.5
clear all

% Cr�ation du signal sp�cifique au test
t = 1:100;
s_ref = sin(3.14.*t./10);
s_bruit = awgn(s_ref,7);    % signal s_ref bruit� gaussiennement avec un facteur SNR de 7

% Corr�lation
[corr] = correlation(s_ref,s_bruit,numel(s_ref));
[autocorr] = correlation(s_ref,s_ref,numel(s_ref));

% Affichage des signaux et r�sultats
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
title('R�sultat auto-corr�lation (Signal 1)')
subplot(4,1,4)
plot(corr)
title('R�sultat corr�lation')

% interpr�tation du r�sultat de la corr�lation
maximum = max((corr));

if maximum >= 0.8
    disp('======================')
    disp('Test 5.5:')
    disp('D�tection r�ussie (allumer DEL 2)')
    disp('======================')
end

if maximum < 0.8
    disp('======================')
    disp('Test 5.5:')
    disp('D�tection non r�ussie (allumer DEL 1)')
    disp('======================')
end