Nd = 10^14:5*10^14:10^18;
ZNd = 10^15*16;
qe = 1.6*10^(-19);
Rh = -1./(qe.*/Nd);
ZRh = -1/(qe.*/ZNd);
I = 10^(-3);
A = 2.5*10^(-3);
Bz = 10^(-4);
W = 500*10^(-6);
Vh = (Rh.*I.*Bz.*W)./A;
ZVh = (ZRh.*I.*Bz.*W)./A;

loglog(Nd, Vh, "g");
xlabel("Nd (cm^-3)", "fontsize", 10);
ylabel("Vh", "fontsize",10);
title("Hall", "fontsize", 15);
disp(ZVh)
