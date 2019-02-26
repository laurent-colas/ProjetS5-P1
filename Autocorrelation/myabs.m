% fonction pour redresser le signal 
function [abs] = myabs(x)
        for i = 1:numel(x)
                if x(i) < mean(x)
                    x(i) = - x(i);
                end
        end
    abs = x; 
end