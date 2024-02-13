Nd = 10^16;
T = 200:5:500;
ZT = 204.5;
mnSi = (7*10^6).*T.^(-1.5);
ZmnSi = (7*10^6).*ZT.^(-1.5);
mnGaAs = (4.4*10^7).*T.^(-1.5);
ZmnGaAs = (4.4*10^7).*ZT.^(-1.5);

qe = 1.6*10^(-19);
sSi = qe.*mnSi.*Nd;
ZsSi = qe.*ZmnSi.*Nd;
sGaAs = qe.*mnGaAs.*Nd;
ZsGaAs = qe.*ZmnGaAs.*Nd;

rSi = 1./sSi;
ZrSi = 1./ZsSi;
rGaAs = 1./sGaAs;
ZrGaAs = 1./ZsGaAs;

plot(T, rSi, "m");
hold on
plot(T, rGaAs, "b");

line([ZT ZT], [0 ZsSi], "linestyle", "--", "color", "m");
line([ZT ZT], [0 ZsGaAs], "linestyle", "--", "color", "g");

legend("Resistivity-Si", "Resistivity-GaAs", "Resistivity-Si (T=204.5), "Resistivity-GaAs (T=204.5))
xlabel("Temprature (K)", "fontsize", 10);
ylabel("Resistivity", "fontsize", 10);
title("Resistivity-Temprature", "fontsize", 15);
disp(ZrSi)
disp(ZrGaAs)