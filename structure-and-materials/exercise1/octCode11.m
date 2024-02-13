tmpr = 0:50:800;
a = 1.17;
b = (4.73*10^(-4)).*tmpr.^2;
c = tmpr.+636;
eg1 = a.-b./c;

k = 1.52
l = (5.4*10^(-4)).*tmpr.^2;
m = tmpr.+204;
eg2 = k.-l./m;

z = 115;

plot (tmpr, eg1, "r")
hold on
plot (tmpr, eg2, "m", [z, z], [0 1.497612853], '--');

ylabel ("Eg(eV)")
xlabel ("Temprature (K)")
legend ("Si", "GaAs")