function [auto_correlation] = auto_correlation(x)
    y = x;
    x = [zeros(1,length(x)) x zeros(1,length(x))];
    auto_correlation(1:length(y)*2-1,:) = 0;

    for boucle_corr = 1:(length(y)*2-1)
       y_corr = [zeros(1,boucle_corr) y zeros(1,length(y)*2-boucle_corr)];
       auto_correlation(boucle_corr) = sum(x .* y_corr);
    end

    auto_correlation = mynorm(auto_correlation);
end

function [max] = mymax(x)
    tempMax = 0;
    for i = 1:numel(x)
            if x(i) > tempMax
                tempMax = x(i);
            end
    end
    max = tempMax;
end

function [abs] = myabs(x)
        for i = 1:numel(x)
                if x(i) < 0
                    x(i) = - x(i);
                end
        end
    abs = x; 
end

function [norm] = mynorm(x)
    absMax = mymax(myabs(x));

    for i = 1:numel(x)
        norm(i) = x(i)/absMax;
    end
end

