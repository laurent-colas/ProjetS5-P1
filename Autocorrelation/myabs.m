function [abs] = myabs(x)
        for i = 1:numel(x)
                if x(i) < 0
                    x(i) = - x(i);
                end
        end
    abs = x; 
end