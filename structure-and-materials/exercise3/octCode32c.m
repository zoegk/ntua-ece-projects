V = linspace(-0.1,0.1,600);
Is = 10^(-13);
k = 1.38*10^(-23);
q = 1.6*10^(-19);
T = 300;
I = Is.*(e.^(q.*V./(k.*T))-1);
plot(V,I)
xlabel("V");
ylabel("I");
title("I - V");