d = 10^(-9):10^(-10):5*10(-9);
i = 15
d0 = (1+0.004*i)*10^(-9);
E = 0.4*1.60217662*10^(-19);
Vo = 0.5*1.60217662*10^(-19);
m = 9.1093897*10^(-31);
hbar = 1.0545718*10^(-34);
a = (2*m*(Vo-E)/(hbar^2))^(1/2);
T = 16*(E/Vo)*(1-E/Vo)*e.^(-2.*a.*d);
T0 = 16*(E/Vo)*(1-E/Vo)*e.^(-2.*a.*d0);
plot(d,T);
line([d0,d0],[0,T0],"linestyle","--","color","b");
line([0,d0],[T0,T0],"linestyle","--","color","b");
xlabel("d(nm)", "fontsize", 12);
ylabel("T(J)", "fontsize", 12);
legend("T(d)");
title("Transmission factor", "fontsize", 18);