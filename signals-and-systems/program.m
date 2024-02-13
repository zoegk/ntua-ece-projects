%Meros 1

%Erwthma 1a)
Fs=8000;
myName = audiorecorder;
disp('Start of recording');
recordblocking(myName, 2); %katagrafh gia duo defterolepta
disp('End of Recording');
play(myName);
name = getaudiodata(myName);
audiowrite('myname.wav',name, 8000); 

filename="myname.wav";
[name,Fs]=audioread(filename);
sound(name);
pause(3);


%Erwthma 1b)
time = linspace(0, 2, 16000); %dianisma
figure(1);
plot(time, name);
title('My Name');
xlabel('Time');
ylabel('Amplitude');
pause(2);

CutName = name(8001:8800); %periodiko kommati tou onomatos mou diarkeias 1000msec
figure(2);
time = linspace(0, 0.1, 800);
plot(time, CutName);
title('100ms part of my name');
xlabel('Time');
ylabel('Amplitude');
pause(2);
CutAudio = audioplayer(CutName, 8000); %dhmiourgo;ume audio file
play(CutAudio);
pause(3)
audiowrite('rec.wav', CutName, 8000); %to apothikevoume

%Erwthma 1c)
n = 0:199;

signal_norm = normalize(name, 'range', [-1 1]);

w = 0.54 - 0.46.*cos(2.*pi.*n./200);  
sq = signal_norm.*signal_norm;
energy = conv(sq,w);

signal_big_norm = normalize(name, 'range', [-60 60]);
figure(3)
hold on;
plot(signal_big_norm, 'b');
plot(energy, 'r', 'LineWidth',2);
hold off;
title('Scaled Signal with Energy');
xlabel('Samples');
ylabel('Magnitude');
pause(2);

%Erwthma 1d)

DFT = fft(CutName, 1024) %dft se 1024 deigmata
freq = linspace(0, 8000, 1024); %1024 deigmata
NormalScale = abs(DFT);
LogScale = 20*log10(NormalScale);
figure(4);
subplot(2, 1, 1);
plot(freq, NormalScale);
title('DFT (Normal Scale)');
xlabel('Frequency');
ylabel('Amplitude');
subplot(2, 1, 2);
plot(freq, LogScale);
title('DFT (Logarithmic Scale)');
xlabel('Frequency');
ylabel('Amplitude (dB)');

%Meros 2.1

%Erwthma 2.1a,b,c)

%N=2
a2 = [1 0 0];
b2 = [1/3 1/3 1/3];
figure(5)
freqz(b2, a2);
title('Frequency Response (N=2)');
pause(2);
figure(6)
[z2,p2,k2] = tf2zp(b2,a2);
zplane(z2,p2);
title('Zero-Pole Diagram (N=2)');
pause(2);

%N=5
a5 = [1 0 0 0 0 0];
b5 = [1/6 1/6 1/6 1/6 1/6 1/6];
figure(7)
freqz(b5, a5);
title('Frequency Response (N=5)');
pause(2);
figure(8)
[z5,p5,k5] = tf2zp(b5,a5);
zplane(z5,p5);
title('Zero-Pole Diagram (N=5)');
pause(2);

%N=10
a10 = [1 0 0 0 0 0 0 0 0 0 0];
b10 = [1/11 1/11 1/11 1/11 1/11 1/11 1/11 1/11 1/11 1/11 1/11];
figure(9)
freqz(b10, a10);
title('Frequency Response (N=10)');
pause(2);
figure(10)
[z10,p10,k10] = tf2zp(b10,a10);
zplane(z10,p10);
title('Zero-Pole Diagram (N=10)');
pause(2);

%Erwthma 2.1d)

%n=2
wc2=0.1;
[bb2,aa2] = butter(2,wc2);
figure(11)
freqz(bb2,aa2)
title('Frequency Response (2th-order lowpass Butterworth)');
pause(2);
figure(12)
[zz2,pp2,kk2] = tf2zp(bb2,aa2);
zplane(zz2,pp2);
title('Zero-Pole Diagram (2th-order lowpass Butterworth)');
pause(2);

%n=8
wc8=0.1;
[bb8,aa8] = butter(8,wc8);
figure(13)
freqz(bb8,aa8)
title('Frequency Response (8th-order lowpass Butterworth)');
pause(2);
figure(14)
[zz8,pp8,kk8] = tf2zp(bb8,aa8);
zplane(zz8,pp8);
title('Zero-Pole Diagram (8th-order lowpass Butterworth)');
pause(2);

%Meros 2.2

%Erwthma 2.2a)

signal = audioread("cello_note.wav");
fs = 44100;
fasma = fft(signal);
figure(15)
plot(abs(fasma));
title('DFT of "Cello Note" Signal');
xlabel('Frequency');
ylabel('Magnitude');
pause(2);
sound(signal, fs);
pause(3);

%Erwthma 2.2b)

signal2 = audioread("cello_note_noisy.wav");
fasma2 = fft(signal2);
figure(16)
plot(abs(fasma2));
title('DFT of "Cello Note Noisy" Signal');
xlabel('Frequency');
ylabel('Magnitude');
pause(2); 
sound(signal2, fs);
pause(3);

%Erwthma 2.2c)

fc = 10^9; % oso afksanetai akoume megaluteres suxnothtes
[b, a] = butter(6,0.1);
filteredSignal = filter(b, a, signal2); %efarmozoume to butterworth filtro
player = audioplayer(filteredSignal, fs);
fasma3 = fft(filteredSignal);
figure (17)
plot(abs(fasma3));
title('DFT of Denoised "Cello Note Noisy" Signal');
xlabel('Frequency');
ylabel('Magnitude');
pause(2);
play(player);   %paizoume to apothoruvhmeno shma
pause(3);

%Erwthma 2.2d)

%Xrhsimopoiw filtro kinoumemou mesou gia N=10
filteredSignal2 = filter(b10, a10, signal2);
player2 = audioplayer(filteredSignal2, fs);
fasma4 = fft(filteredSignal2);
figure (18)
plot(abs(fasma4));
title('DFT of Denoised "Cello Note Noisy" Signal');
xlabel('Frequency');
ylabel('Magnitude');
pause(2);
play(player2);
pause(3);

%Meros 3

%Erwthma 3a)
%sto telos

%Erwthma 3b)
fr = 200;
clear fs;
fs = 800;
time = linspace(0, 800, 800);
freq = linspace(0, 800, 800);


%r=0.95
r = 0.95;

 W = 2*pi*(fr/fs);
    num = [sin(W), 0, 0]; %arithmitis
    den = [1, -2*r*cos(W), r^2]; %paronomasths

ImpResponse = impz(num, den, fs);
figure(19);
subplot(2, 1, 1);
plot(time, ImpResponse);
title('Impulse Response (r=0.95)');
xlabel('Time');
ylabel('Amplitude');
FreqResponse = fft(ImpResponse);
subplot(2, 1, 2);
plot(freq, abs(FreqResponse));
title('Frequency Response (r=0.95)');
xlabel('Frequency');
ylabel('Amplitude');
pause(2);

%r=0.7
clear r;
r=0.7;
ImpResponse = impz(num, den, fs);
figure(20);
subplot(2, 1, 1);
plot(time, ImpResponse);
title('Impulse Response (r=0.7)');
xlabel('Time');
ylabel('Amplitude');
FreqResponse = fft(ImpResponse);
subplot(2, 1, 2);
plot(freq, abs(FreqResponse));
title('Frequency Response (r=0.7)');
xlabel('Frequency');
ylabel('Amplitude');
pause(2);

%r=1
clear r;
r = 1;
ImpResponse = impz(num, den, fs);
figure(21);
subplot(2, 1, 1);
plot(time, ImpResponse);
title('Impulse Response (r=1)');
xlabel('Time');
ylabel('Amplitude');
FreqResponse = fft(ImpResponse);
subplot(2, 1, 2);
plot(freq, abs(FreqResponse));
title('Frequency Response (r=1)');
xlabel('Frequency');
ylabel('Amplitude');
pause(2);

%r=1.2
clear r;
r = 1.2;
ImpResponse = impz(num, den, fs);
figure(22);
subplot(2, 1, 1);
plot(time, ImpResponse);
title('Impulse Response (r=1.2)');
xlabel('Time');
ylabel('Amplitude');
FreqResponse = fft(ImpResponse);
subplot(2, 1, 2);
plot(freq, abs(FreqResponse));
title('Frequency Response (r=1.2)');
xlabel('Frequency');
ylabel('Amplitude');
pause(2);


%Erwthma 3.c)
clear fs;
fs = 8000; %fs >= 2fmax
fr1 = 500;
fr2 = 1500;
fr3 = 2500;
d = zeros(1, 8000);
d(1) = 1; %delta function
clear r;
r = 0.95;
out1 = resonator(d, fr1, r, fs);
out2 = resonator(out1, fr2, r, fs);
out3 = resonator(out2, fr3, r, fs);
TotalFreqResponse = fft(out3);
freq = linspace(0, 8000, 8000);
figure(23);
plot(freq, abs(TotalFreqResponse));
title('Total Frequency Response')
pause(2);

%Erwthma 3.d)
imptr = zeros(1,1601); %suxnothta 8000Hz kai diarkeia 0.2sec
imptr(1:80:end) = 1; %kroustikh kathe 10 milli
xronos = linspace(0, 0.2, 1601);
suxn = linspace(0, 8000, 1601);
trainOut1 = resonator(imptr, fr1, r, fs);
trainOut2 = resonator(trainOut1, fr2, r, fs);
trainOut3 = resonator(trainOut2, fr3, r, fs);
trainFreqResp = fft(trainOut3);
figure(24);
plot(suxn, abs(trainFreqResp));
title('DFT of Impulse Train Response');
xlabel('Frequency');
ylabel('Amplitude');
arithmitis = [1, -1];
paronomastis = [1, 0];
FirstDif = filter(arithmitis, paronomastis, trainOut3); %x[n]-x[n-1]
figure(25);
subplot(2, 1, 1);
plot(xronos, trainOut3); %sxediazoume x[n]
title('Impulse Train Response (x[n])');
xlabel('Time');
ylabel('Amplitude');
subplot(2, 1, 2);
plot(xronos, FirstDif); %sxediazoume x[n]-x[n-1]
title('x[n]-x[n-1]');
xlabel('Time');
ylabel('Amplitude');
pause(2);
audio1 = audioplayer(trainOut3, 8000); %to audiofile gia to x[n]
audio2 = audioplayer(FirstDif, 8000); %to audiofile gia to x[n]-x[n-1]
play(audio1);
pause(3);
play(audio2);
pause(3);
audiowrite('x{n).wav',trainOut3, 8000);
audiowrite('x(n)-x(n-1).wav', FirstDif, 8000);
DFTFirstDif = fft(FirstDif);
figure(26);
plot(suxn, abs(DFTFirstDif));
title('DFT of First Difference');
xlabel('Frequency');
ylabel('Amplitude');
pause(2);

%Meros 4

%4.1 
S = imread("image.png"); 
imshow(S); 


%4.2
[x, y] = find(S,1); 
P = [x, y]; 
B = bwtraceboundary(S,P,"n"); 
figure(27)
subplot(2,2,1)
plot(B); 

%4.3
x = B(:, 1);
y = B(:, 2); 
z = x + j*y; 
Z = fft(z); 
subplot(2,2,2)
plot(abs(Z)); 


%4.4 
N=length(Z); 
M=200; 
for n=1:N 
zm(n) = Z(1); 
for k=2:M 
zm(n)=zm(n)+((1/N)*Z(k).*exp(j*2*pi*(k-1)*n/N)); end 
end 
xm=real(zm); 
ym=imag(zm); 
subplot(2,2,3)
plot(xm, ym); 

%4.5 
M = 200; 
for n=1:N 
zhatm(n) = Z(1); 
for k=2:M/2
 zhatm(n) = zhatm(n) + (1/N)*Z(k).*exp(j*2*pi*(k-1)*n/N); 
end 
for  k=N-M/2:N
zhatm(n) = zhatm(n) + (1/N)*Z(k).*exp(j*2*pi*(k-1)*n/N); 
end 
end

hatm = real(zhatm); 
yhatm = imag(zhatm); 
subplot(2,2,4)
plot(hatm, yhatm);
