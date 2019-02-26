% fonction pour normaliser le signal
function [norm] = mynorm(x)
    absMax = mymax(myabs(x));

    for i = 1:numel(x)
        norm(i) = x(i)/absMax;
    end
end