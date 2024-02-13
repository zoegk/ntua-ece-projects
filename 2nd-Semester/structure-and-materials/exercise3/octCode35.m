T = 300;
i = 15;
tn = 10^(-6);
Gf = 10^20;
Dn0 = Gf*tn;
t = 10^(-8)*(1+0.1*i):10^(-8):10^(-6);
Dn = Dn0.*e.^(-t./tn);
plot(t,Dn)
xlabel("t");
ylabel("Dn");
title("Dn -t");