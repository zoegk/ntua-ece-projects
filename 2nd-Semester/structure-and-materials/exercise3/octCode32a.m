Vd = 0.2:0.002:0.6;
Is = 10^(-13);
k = 1.38*10^(-23);
q = 1.6*10^(-19);
T = 300;
I = Is.*e.^(q.*Vd./(k.*T));
plot(Vd,I)
xlabel("Vd");
ylabel("I");
title("I - Vd");