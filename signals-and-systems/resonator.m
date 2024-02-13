%Nato to 3a)
function y = resonator(x, resonator_frequency, r, sampling_frequency)
    W = 2*pi*(resonator_frequency/sampling_frequency);
    num = [sin(W), 0, 0]; %arithmitis
    den = [1, -2*r*cos(W), r^2]; %paronomasths
    y = filter(num, den, x);
end