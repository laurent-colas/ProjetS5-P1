% fonction pour normaliser le signal
function [norm] = mynorm(x,l)
    absolute = myabs(x,numel(x));               % redressement
    AbsMax = mymax(absolute,numel(absolute));   % valeur max
    
% boucle principale qui normalise le signal
    for i = 1:l
        norm(i) = x(i)/AbsMax;
    end
end