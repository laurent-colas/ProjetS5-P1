function [correlation,decalage] = correlation(x,y)
    
% Ajustement de la longueur des signaux 
    nbx = numel(x);
    nby = numel(y);
    if nbx ~= nby
        x = [x zeros(1,nby-1)];
        y = [y zeros(1,nbx-1)];
    end
    nb = numel(x);
    decalage = (-(nb-1)):(nb-1);
    nDec = numel(decalage);
    
% Ajout de "0" avant et apr�s pour pouvoir faire les opp�rations
    y = [zeros(1,nb-1) y zeros(1,nb-1)]; 
    nby = numel(y);
    
% Boucle principale de l'algo  
    for i = 0:nDec-1
       buff = y((nDec-i):(nby-i));
       correlation(i+1) = sum(x .* buff);
    end
    correlation = mynorm(correlation);
end

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

% fonction pour redresser le signal 
function [abs] = myabs(x)
        for i = 1:numel(x)
                if x(i) < mean(x)
                    x(i) = - x(i);
                end
        end
    abs = x; 
end

% fonction pour normaliser le signal
function [norm] = mynorm(x)
    absMax = mymax(myabs(x));

    for i = 1:numel(x)
        norm(i) = x(i)/absMax;
    end
end

