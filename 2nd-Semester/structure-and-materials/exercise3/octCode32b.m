Vr = linspace(-0.8,-0.1,100);
Is = 10^(-13);
k = 1.38*10^(-23);
q = 1.6*10^(-19);
T = 300;
Ir = Is.*(e.^(q.*Vr./(k.*T))-1);
plot(Vr,Ir)
xlabel("Vr");
ylabel("Ir");
title("Ir - Vr");