% fonction pour trouver la valeur max
function [tempMax] = mymax(x,l)
    tempMax = 0;
% boucle principale qui recherche la plus grande valeur
    for i = 1:l
            if x(i) > tempMax
                tempMax = x(i);
            end
    end
end