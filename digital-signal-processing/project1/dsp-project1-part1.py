#!/usr/bin/env python
# coding: utf-8

# ### Μέρος 1ο - Φασματική Ανάλυση και Ανίχνευση Ημιτονοειδών με τον Διακριτό Μετ/σμό Fourier (DFT)
# 
# ***Ερώτημα 1.1:*** Για να υπολογίσουμε το DFT του παραθυρωμένου σήματος y[n], πρέπει αρχικά να παράξουμε τα αρχικά σήματα x1[n] και x2[n], χρησιμοποιώντας τις δωσμένες παραμέτρους.


import numpy as np

L = 256
n = np.arange(L)

# Parameters for x1[n]
A1 = 1
w1 = np.pi/10
phi1 = 2 * np.pi * np.random.rand()

# Parameters for x2[n]
A2 = 0.9
w2 = np.pi/7
phi2 = 2 * np.pi * np.random.rand()

# Generate x1[n] and x2[n]
x1 = A1 * np.exp(1j * (w1 * n + phi1))
x2 = A2 * np.exp(1j * (w2 * n + phi2))

# Generate window and windowed signal
window = np.hamming(L)
y = window * (x1 + x2)


# Στην συνέχεια, υπολογίζουμε το DFT του παραθυρώμενου σήματος y[n], χρησιμοποιώντας την συνάρτηση numpy.fft.fft().



N = 256
Y = np.fft.fft(y, N)


# Και τέλος σχεδιάζουμε φάσμα πλάτους του DFT:



import matplotlib.pyplot as plt

plt.plot(np.abs(Y))
plt.xlabel('Frequency index (k)')
plt.ylabel('Amplitude')
plt.show()


# ***Ερώτημα 1.2:*** Επαναλαμβάνουμε το πείραμα για N = 512 και N = 1024. <br>
# <br>
#         *Αρχικά για N = 512:*



import numpy as np
import matplotlib.pyplot as plt

L = 256
n = np.arange(L)

# Parameters for x1[n]
A1 = 1
w1 = np.pi/10
phi1 = 2 * np.pi * np.random.rand()

# Parameters for x2[n]
A2 = 0.9
w2 = np.pi/7
phi2 = 2 * np.pi * np.random.rand()

# Generate x1[n] and x2[n]
x1 = A1 * np.exp(1j * (w1 * n + phi1))
x2 = A2 * np.exp(1j * (w2 * n + phi2))

# Generate window and windowed signal
L_pad = 512 - L
window = np.hamming(L)
y = np.pad(window * (x1 + x2), (0, L_pad), mode='constant')

N = 512
Y = np.fft.fft(y, N)

plt.plot(np.abs(Y))
plt.xlabel('Frequency index (k)')
plt.ylabel('Amplitude')
plt.show()


# *Και για N = 1024:*



import numpy as np
import matplotlib.pyplot as plt

L = 256
n = np.arange(L)

# Parameters for x1[n]
A1 = 1
w1 = np.pi/10
phi1 = 2 * np.pi * np.random.rand()

# Parameters for x2[n]
A2 = 0.9
w2 = np.pi/7
phi2 = 2 * np.pi * np.random.rand()

# Generate x1[n] and x2[n]
x1 = A1 * np.exp(1j * (w1 * n + phi1))
x2 = A2 * np.exp(1j * (w2 * n + phi2))

# Generate window and windowed signal
L_pad = 1024 - L
window = np.hamming(L)
y = np.pad(window * (x1 + x2), (0, L_pad), mode='constant')

N = 1024
Y = np.fft.fft(y, N)

plt.plot(np.abs(Y))
plt.xlabel('Frequency index (k)')
plt.ylabel('Amplitude')
plt.show()


# ***Ερώτημα 1.3:*** Επαναλαμβάνουμε το 1.1 για τιμές L = 512 και L = 1024.


import numpy as np
import matplotlib.pyplot as plt

# Experiment with L = 512
L = 512
n = np.arange(L)

# Parameters for x1[n]
A1 = 1
w1 = np.pi/10
phi1 = 2 * np.pi * np.random.rand()

# Parameters for x2[n]
A2 = 0.9
w2 = np.pi/7
phi2 = 2 * np.pi * np.random.rand()

# Generate x1[n] and x2[n]
x1 = A1 * np.exp(1j * (w1 * n + phi1))
x2 = A2 * np.exp(1j * (w2 * n + phi2))

# Generate window and windowed signal
window = np.hamming(L)
y = window * (x1 + x2)

# Compute Fourier transform
N = 512
Y = np.fft.fft(y, N)

# Plot magnitude spectrum
plt.plot(np.abs(Y))
plt.title('L = 512')
plt.xlabel('Frequency index (k)')
plt.ylabel('Amplitude')
plt.show()

# Experiment with L = 1024
L = 1024
n = np.arange(L)

# Parameters for x1[n]
A1 = 1
w1 = np.pi/10
phi1 = 2 * np.pi * np.random.rand()

# Parameters for x2[n]
A2 = 0.9
w2 = np.pi/7
phi2 = 2 * np.pi * np.random.rand()

# Generate x1[n] and x2[n]
x1 = A1 * np.exp(1j * (w1 * n + phi1))
x2 = A2 * np.exp(1j * (w2 * n + phi2))

# Generate window and windowed signal
window = np.hamming(L)
y = window * (x1 + x2)

# Compute Fourier transform
N = 1024
Y = np.fft.fft(y, N)

# Plot magnitude spectrum
plt.plot(np.abs(Y))
plt.title('L = 1024')
plt.xlabel('Frequency index (k)')
plt.ylabel('Amplitude')
plt.show()


# ***Ερώτημα 1.4:*** Αναλύουμε το σήμα και σχεδιάζουμε το πλάτος DFT για:
# 1. *Tετραγωνικό παράθυρο*
# 2. *Παράθυρο Hamming*


import numpy as np
import matplotlib.pyplot as plt

# Define signal parameters
L = 256
N = 1024
n = np.arange(L)
A1 = 1
w1 = 0.25*np.pi
phi1 = 2*np.pi*np.random.rand()
A2 = 0.05
w2 = 0.3*np.pi
phi2 = 2*np.pi*np.random.rand()

# Generate signals
x1 = A1 * np.exp(1j*(w1*n + phi1))
x2 = A2 * np.exp(1j*(w2*n + phi2))
window_square = np.ones(L)
window_hamming = np.hamming(L)
y_square = window_square*(x1 + x2)
y_hamming = window_hamming*(x1 + x2)

# Compute DFTs
Y_square = np.fft.fft(y_square, N)
Y_hamming = np.fft.fft(y_hamming, N)

# Plot DFT magnitudes
plt.figure(figsize=(10,4))
plt.subplot(1,2,1)
plt.plot(np.abs(Y_square))
plt.title('DFT Magnitude for Square Window')
plt.xlabel('Frequency index (k)')
plt.ylabel('Amplitude')
plt.subplot(1,2,2)
plt.plot(np.abs(Y_hamming))
plt.title('DFT Magnitude for Hamming Window')
plt.xlabel('Frequency index (k)')
plt.ylabel('Amplitude')
plt.tight_layout()
plt.show()

