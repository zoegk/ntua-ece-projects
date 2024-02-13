Nd = 10^14:5*10^14:10^18;
T = 300;
ZNd = 10^15*16;

mnSi = (7*10^6).*T.^(-1.5);
mnGaAs = (4.4*10^7).*T.^(-1.5);
qe = 1.6*10^(-19);
sSi = qe.*mnSi.*Nd;
ZsSi = qe.*mnSi.*ZNd;
sGaAs = qe.*mnGaAs.*Nd;
ZsGaAs = qe.*mnGaAs.*ZNd;

plot(Nd, sSi, "b");
hold on
plot(Nd, sGaAs, "g");
line([ZNd ZNd], [0 ZsSi], "linestyle", "--", "color", "b");
line([ZNd ZNd], [0 ZsGaAs], "linestyle", "--", "color", "g");

legend("Conductivity-Si", "Conductivity-GaAs", "Conductivity-Si (Nd=16*10^15 cm^-3), "Conductivity-GaAs (Nd=16*10^15 cm^-3))
xlabel("Nd (cm^-3)", "fontsize", 10);
ylabel("Conductivity", "fontsize", 10);
title("Conductivity-Nd", "fontsize", 15);
disp(ZsSi)
disp(ZsGaAs)
