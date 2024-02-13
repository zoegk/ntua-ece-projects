T = 0:10:600;
k = 8.6173324.*10.^(-5);
Nd = 10^(16);
EgSi = 1.17 - ((4.73.*10.^(-4).*T.^2)./(T.+636));
EgGaAs = 1.52 - ((5.4.*10.^(-4).*T.^2)./(T.+204));
b = EgSi./(2.*k.*T);
NcSi = [(3.22*10^19)*(T./300).^(3./2)];
NvSi = [(1.83*10^19)*(T./300).^(3./2)];
NcGaAs = [(4.21*10^17)*(T./300).^(3./2)];
c = EgGaAs./(2.*k.*T);
NvGaAs = [(9.52*10^18)*(T./300).^(3./2)];
niSi = ((NcSi.*NvSi).^(1/2)).*e.^(-b);
niGaAs = ((NcGaAs.*NvGaAs).^(1/2)).*e.^(-c);
dESi = k.*T.*log(Nd./niSi);
dEGaAs = k.*T.*log(Nd./niGaAs);
subplot(2,1,1)
plot(T,dESi,"g");
xlabel ("T(K)", "fontsize", 12);
ylabel ("Ef-Ei(eV)", "fontsize", 12);
title("Ef-Ei of Si", "fontsize",18);
subplot(2,1,2)
plot(T,dEGaAs);
xlabel ("T(K)", "fontsize", 12);
ylabel ("Ef-Ei(eV)", "fontsize", 12);
title("Ef-Ei(eV) of GaAs", "fontsize",18);