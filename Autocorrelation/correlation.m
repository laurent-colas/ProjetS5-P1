function [correlation] = correlation(x,y)
    
% Ajustement de la longueur des signaux 
    nbx = numel(x);
    nby = numel(y);
    x = [x zeros(1,nby-1)];
    y = [y zeros(1,nbx-1)];

% Ajout de "0" avant et après pour pouvoir faire les oppérations
    x = [zeros(1,length(x)) x zeros(1,length(x))];
    correlation(1:length(y)*2-1,:) = 0;
    
% Boucle principale de l'algo  
    for boucle_corr = 1:(length(y)*2-1)
       y_corr = [zeros(1,boucle_corr) y zeros(1,length(y)*2-boucle_corr)];
       correlation(boucle_corr) = sum(x .* y_corr);
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

