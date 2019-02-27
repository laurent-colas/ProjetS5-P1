function [correlation] = correlation(x,y,l)
    nb = 2*l-1;
% Ajout de "0" avant et après pour pouvoir faire les oppérations
    x = [zeros(1,l-1) x zeros(1,l-1)]; 
    
% Boucle principale de l'algo  
correlation = zeros(1,nb);
    for i = 0:nb-1
       tempy = [zeros(1,i) y zeros(1,((nb-1)-i))]; 
       correlation(i+1) = sum(x .* tempy);
    end
   correlation = mynorm(correlation,numel(correlation));    % normalisation
end