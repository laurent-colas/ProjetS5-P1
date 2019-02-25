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


x = [1 0 -1 0];
y = [1 0 -1 0];

x = [zeros(1,length(x)) x zeros(1,length(x))];
auto_correlation(1:length(y)*2-1,:) = 0;

for boucle_corr = 1:(length(y)*2-1)
   y_corr = [zeros(1,boucle_corr) y zeros(1,length(y)*2-boucle_corr)];
   auto_correlation(boucle_corr) = sum(x .* y_corr);
end


stem(auto_correlation)

% max_autocorrelation = 0;
% for i = 1:length(auto_correlation)
%     if auto_correlation(i,:) > max_autocorrelation
%         max_autocorrelation = auto_correlation(i,:);
%     end
% end
% 
% auto_correlation = auto_correlation ./  max_autocorrelation;












