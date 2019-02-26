% fonction pour trouver la valeur max
function [max] = mymax(x)
    tempMax = 0;
    for i = 1:numel(x)
            if x(i) > tempMax
                tempMax = x(i);
            end
    end
    max = tempMax;
end