T = 300;
i = 15;
fbn = 0.67;
Vd = 0.1:0.001:0.35;
ZVd = (0.25 + i*10^(-4));
A = 120;
k = 1.38*10^(-23);
q = 1.6*10^(-19);
Jst = A*(T^2)*e^((-q*fbn)/(k*T));
J = Jst.*e.^(((Vd.*q)./(k.*T)).-1);
plot(Vd,J)
xlabel("Vd");
ylabel("J");
title("J - Vd");