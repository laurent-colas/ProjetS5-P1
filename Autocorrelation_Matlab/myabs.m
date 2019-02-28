% fonction pour redresser le signal 
function [abs] = myabs(tab,l)
% boucle principale qui rend toute valeur négative, positive 
    for i = 1:l
            if tab(i) < 0
                tab(i) = - tab(i);
            end
    end
    abs = tab; 
end