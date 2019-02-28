
function [correlation] = correlation(x,y,l)    
% D�termination coefficients Rxx0 et Ryy0
    rxx0 = sum(x.*x);
    ryy0 = sum(y.*y);
    
    nb = 2*l-1;
% Ajout de "0" avant et apr�s pour pouvoir faire les opp�rations
    x = [zeros(1,l-1) x zeros(1,l-1)]; 
    
% Boucle principale de l'algo  
correlation = zeros(1,nb);
    for i = 0:nb-1
       tempy = [zeros(1,i) y zeros(1,((nb-1)-i))]; 
% multiplication pts � pts et sommation du tout 
       correlation(i+1) = sum(x .* tempy)/sqrt(rxx0*ryy0); 
    end
end