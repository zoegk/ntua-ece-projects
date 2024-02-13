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

rSi = 1./sSi;
ZrSi = 1./ZsSi;
rGaAs = 1./sGaAs;
ZrGaAs = 1./ZsGaAs;

loglog(Nd, rSi, "m");

hold on

loglog(Nd, rGaAs, "g");

line([ZNd ZNd], [0.0000001 ZrSi], "linestyle", "--", "color", "m");
line([ZNd ZNd], [0.0000001 ZrGaAs], "linestyle", "--", "color", "g");

legend("Resistivity-Si", "Resistivity-GaAs", "Resistivity-Si (Nd=16*10^15 cm^-3), "Resistivity-GaAs (Nd=16*10^15 cm^-3))
xlabel("Nd (cm^-3)", "fontsize", 10);
ylabel("Resistivity", "fontsize", 10);
title("Resistivity-Nd", "fontsize", 15);
disp(ZrSi)
disp(ZrGaAs)
