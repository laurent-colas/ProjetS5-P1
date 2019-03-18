
function [h_circ] = circ_correlation_fft(a,b)
% zeropad to the same length M
if (length(a) < length(b))
    c = [ a zeros(1,length(b)-length(a)) ];
    d = b;
else
    c = a;
    d = [ b zeros(1,length(a)-length(b)) ];
end
% calculate crosscorrelation
e = fft(c);
f = fft(d);
g = f.*conj(e);
h_circ = fftshift(ifft(g));

end