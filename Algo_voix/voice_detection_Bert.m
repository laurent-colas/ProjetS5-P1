clear all 
close all 
clc

fs = 8000;


dt = 1/fs;
w = hamming(2*fs);
w = w';
nbBits = 16;

%% Configuration 
for i = 1:3
    recObj = audiorecorder(fs,nbBits,1);
    disp(['Start speaking. ' num2str(i)])
    recordblocking(recObj, 2);
    disp('End of Recording.');
    x(i,:) = getaudiodata(recObj);
    x(i,:) = x(i,:)./max(abs(x(i,:)));
    x(i,:) = x(i,:)-mean(x(i,:));
    x(i,:) = x(i,:).*w;
    disp('===============');
end
%% Pré Traitement
TW = triang(numel(x(1,:))/2);
TW = TW';

for i = 1:3
    X(i,:).cmplx = fft(x(i,:));
    X(i,:).real = real(X(i,:).cmplx);
    X(i,:).img = imag(X(i,:).cmplx);
    X(i,:).magn = abs(X(i,:).cmplx);
    X(i,:).phase = angle(X(i,:).cmplx); 
end

XREF.cmplx = (X(1,:).cmplx + X(2,:).cmplx + X(3,:).cmplx)./3;
XREF.magn = abs(XREF.cmplx);
XREF.phase = angle(XREF.cmplx);

xREF = ifft(XREF.cmplx);
xREF = xREF./max(abs(xREF));
xREF = xREF-mean(xREF);

N = numel(xREF);      % nombre d'échantillon
Nb = floor(N/2)+1;
T = N*dt;           % durée du signal
df = 1/T; 
f = (0:1:Nb)*df;     % frequency vector (Hz)
f(Nb:end) = [];

for i = 1:3
    X(i).magn(Nb:end) = [];
    X(i).phase(Nb:end) = [];
    X(i).magn = X(i).magn./max(abs(X(i).magn));
    X(i).magn = TW.*X(i).magn;
    X(i).magn = X(i).magn./max(abs(X(i).magn));
end

XREF.magn(Nb:end) = [];
XREF.magn = XREF.magn./max(abs(XREF.magn));
XREF.magn = TW.*XREF.magn;
XREF.magn = XREF.magn./max(abs(XREF.magn));
XREF.phase(Nb:end) = [];

autoCorr = correlation(XREF.magn,XREF.magn,numel(XREF.magn));
for i = 1:3
    corr(i).magn = correlation(XREF.magn,X(i,:).magn,numel(XREF.magn));
    score(i) =  5^(mean(abs(autoCorr-corr(i).magn))*100);
end

seuil = (score(1)+score(2)+score(3))/3
%% Identification 

close all 
clc
recObj = audiorecorder(fs,nbBits,1);
disp('Start speaking.')
recordblocking(recObj, 2);
disp('End of Recording.');
x2 = getaudiodata(recObj);
x2 = x2./max(abs(x2));
x2 = x2 - mean(x2);
x2 = x2.*w';

X2 = fft(x2);
X2m = abs(X2);
X2p = angle(X2);
X2m(Nb:end) = [];
X2p(Nb:end) = [];
X2m = X2m./max(abs(X2m));
X2m = TW'.*X2m;
X2m = X2m./max(abs(X2m));
X2m = X2m';
X2p = X2p';

player = audioplayer(x2,fs);
play(player)

corr2.magn = correlation(XREF.magn,X2m,numel(XREF.magn));

score2 = 5^(mean(abs(autoCorr-corr2.magn))*100)

figure(1) 
plot(autoCorr)
hold on 
for i =1:3
figure(1) 
plot(corr(i).magn)
hold on 
end

figure(2) 
plot(autoCorr)
hold on 
plot(corr2.magn)

if score2 <= 20*seuil
    disp("Détection YEAH ! ta dit ton nom !!! ")
else
    disp("Pas le bon nom asti dcave")
end


