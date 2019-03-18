function [h] = correlation_fft(a,b)
% zeropad to the same length M + length of correlation 2M-1
if (length(a) < length(b))
    c = [ zeros(1,length(b)-1) a zeros(1,length(b)-length(a)) ];
    d = [ b zeros(1,length(b)-1) ];
else
    c = [ zeros(1,length(a)-1) a ];
    d = [ b zeros(1,length(a)-length(b)+length(a)-1) ];
end
% calculate crosscorrelation
e = fft(c);
f = fft(d);
g = e.*conj(f);
h = ifft(g);

end


