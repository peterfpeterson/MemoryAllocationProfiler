import matplotlib
import matplotlib.pyplot as plt

matplotlib.use('qtagg')

simplevec = """VECTOR SIZE = 1000000
Allocate:  0.0025 sec, CPU Fraction 1.00
virtual[13 MB] resident[10 MB] available[58981 MB] total[63871 MB]
Fill:  0.0049 sec, CPU Fraction 1.00
virtual[20 MB] resident[18 MB] available[58970 MB] total[63871 MB]
Free:  0.0005 sec, CPU Fraction 1.01
virtual[5 MB] resident[3 MB] available[59008 MB] total[63871 MB]
VECTOR SIZE = 1000000
Allocate:  0.0019 sec, CPU Fraction 1.00
virtual[13 MB] resident[10 MB] available[59004 MB] total[63871 MB]
Fill:  0.0041 sec, CPU Fraction 1.00
virtual[28 MB] resident[26 MB] available[58998 MB] total[63871 MB]
Free:  0.0001 sec, CPU Fraction 1.01
virtual[28 MB] resident[26 MB] available[59019 MB] total[63871 MB]
VECTOR SIZE = 10000000
Allocate:  0.0182 sec, CPU Fraction 1.00
virtual[104 MB] resident[102 MB] available[58942 MB] total[63871 MB]
Fill:  0.0404 sec, CPU Fraction 1.00
virtual[181 MB] resident[178 MB] available[58807 MB] total[63871 MB]
Free:  0.0030 sec, CPU Fraction 1.00
virtual[28 MB] resident[26 MB] available[58983 MB] total[63871 MB]
VECTOR SIZE = 100000000
Allocate:  0.1978 sec, CPU Fraction 1.00
virtual[791 MB] resident[788 MB] available[58221 MB] total[63871 MB]
Fill:  0.4395 sec, CPU Fraction 1.00
virtual[1554 MB] resident[1551 MB] available[57434 MB] total[63871 MB]
Free:  0.0264 sec, CPU Fraction 1.00
virtual[28 MB] resident[25 MB] available[58939 MB] total[63871 MB]
VECTOR SIZE = 1000000000
Allocate:  1.8272 sec, CPU Fraction 1.00
virtual[7658 MB] resident[7655 MB] available[51322 MB] total[63871 MB]
Fill:  3.9844 sec, CPU Fraction 1.00
virtual[15287 MB] resident[15284 MB] available[43675 MB] total[63871 MB]
Free:  0.2491 sec, CPU Fraction 1.00
virtual[28 MB] resident[26 MB] available[59023 MB] total[63871 MB]
VECTOR SIZE = 2000000000
Allocate:  3.6684 sec, CPU Fraction 1.00
virtual[15287 MB] resident[15284 MB] available[43756 MB] total[63871 MB]
Fill:  7.8908 sec, CPU Fraction 1.00
virtual[30546 MB] resident[30543 MB] available[28460 MB] total[63871 MB]
Free:  0.5017 sec, CPU Fraction 1.00
virtual[28 MB] resident[25 MB] available[59032 MB] total[63871 MB]
VECTOR SIZE = 3000000000
Allocate:  5.4292 sec, CPU Fraction 1.00
virtual[22916 MB] resident[22913 MB] available[36112 MB] total[63871 MB]
Fill: 11.8389 sec, CPU Fraction 1.00
virtual[45805 MB] resident[45801 MB] available[13220 MB] total[63871 MB]
Free:  0.7384 sec, CPU Fraction 1.00
virtual[28 MB] resident[25 MB] available[59080 MB] total[63871 MB]"""

simplevec = """VECTOR SIZE = 1000000
Allocate:  0.0021 sec, CPU Fraction 1.00
virtual[13 MB] resident[10 MB] available[50503 MB] total[63871 MB]
Fill:  0.0047 sec, CPU Fraction 1.00
virtual[20 MB] resident[18 MB] available[50491 MB] total[63871 MB]
Free:  0.0007 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[50510 MB] total[63871 MB]
VECTOR SIZE = 1000000
Allocate:  0.0019 sec, CPU Fraction 1.00
virtual[13 MB] resident[10 MB] available[50503 MB] total[63871 MB]
Fill:  0.0046 sec, CPU Fraction 1.00
virtual[28 MB] resident[26 MB] available[50502 MB] total[63871 MB]
Free:  0.0001 sec, CPU Fraction 1.02
virtual[28 MB] resident[26 MB] available[50524 MB] total[63871 MB]
VECTOR SIZE = 10000000
Allocate:  0.0202 sec, CPU Fraction 1.00
virtual[104 MB] resident[102 MB] available[50450 MB] total[63871 MB]
Fill:  0.0435 sec, CPU Fraction 1.00
virtual[181 MB] resident[178 MB] available[50367 MB] total[63871 MB]
Free:  0.0056 sec, CPU Fraction 1.00
virtual[28 MB] resident[26 MB] available[50499 MB] total[63871 MB]
VECTOR SIZE = 100000000
Allocate:  0.1873 sec, CPU Fraction 1.00
virtual[791 MB] resident[789 MB] available[49739 MB] total[63871 MB]
Fill:  0.4101 sec, CPU Fraction 1.00
virtual[1554 MB] resident[1551 MB] available[48980 MB] total[63871 MB]
Free:  0.0299 sec, CPU Fraction 1.00
virtual[28 MB] resident[26 MB] available[50505 MB] total[63871 MB]
VECTOR SIZE = 1000000000
Allocate:  1.8377 sec, CPU Fraction 1.00
virtual[7658 MB] resident[7655 MB] available[42850 MB] total[63871 MB]
Fill:  4.0314 sec, CPU Fraction 1.00
virtual[15287 MB] resident[15284 MB] available[35191 MB] total[63871 MB]
Free:  0.2596 sec, CPU Fraction 1.00
virtual[28 MB] resident[26 MB] available[50454 MB] total[63871 MB]
VECTOR SIZE = 2000000000
Allocate:  3.6540 sec, CPU Fraction 1.00
virtual[15287 MB] resident[15284 MB] available[35170 MB] total[63871 MB]
Fill:  8.1927 sec, CPU Fraction 1.00
virtual[30546 MB] resident[30542 MB] available[19831 MB] total[63871 MB]
Free:  0.5228 sec, CPU Fraction 1.00
virtual[28 MB] resident[25 MB] available[50404 MB] total[63871 MB]
VECTOR SIZE = 3000000000
Allocate:  5.4702 sec, CPU Fraction 1.00
virtual[22916 MB] resident[22913 MB] available[27490 MB] total[63871 MB]
Fill: 13.3537 sec, CPU Fraction 1.00
virtual[45805 MB] resident[45801 MB] available[6823 MB] total[63871 MB]
Free:  0.8659 sec, CPU Fraction 1.00
virtual[28 MB] resident[25 MB] available[52705 MB] total[63871 MB] """

tofevent_classic = """
VECTOR SIZE = 100000
Allocate:  0.0001 sec, CPU Fraction 1.00
virtual[7 MB] resident[3 MB] available[58593 MB] total[63871 MB]
Fill:  0.0004 sec, CPU Fraction 1.00
virtual[7 MB] resident[4 MB] available[58437 MB] total[63871 MB]
Free:  0.0001 sec, CPU Fraction 1.01
virtual[5 MB] resident[3 MB] available[58530 MB] total[63871 MB]
VECTOR SIZE = 1000000
Allocate:  0.0000 sec, CPU Fraction 1.01
virtual[20 MB] resident[3 MB] available[58530 MB] total[63871 MB]
Fill:  0.0036 sec, CPU Fraction 1.00
virtual[20 MB] resident[18 MB] available[58566 MB] total[63871 MB]
Free:  0.0004 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[58676 MB] total[63871 MB]
VECTOR SIZE = 10000000
Allocate:  0.0000 sec, CPU Fraction 1.03
virtual[158 MB] resident[3 MB] available[58676 MB] total[63871 MB]
Fill:  0.0358 sec, CPU Fraction 1.00
virtual[158 MB] resident[155 MB] available[58519 MB] total[63871 MB]
Free:  0.0036 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[58677 MB] total[63871 MB]
VECTOR SIZE = 100000000
Allocate:  0.0000 sec, CPU Fraction 1.01
virtual[1531 MB] resident[3 MB] available[58677 MB] total[63871 MB]
Fill:  0.3393 sec, CPU Fraction 1.00
virtual[1531 MB] resident[1529 MB] available[57160 MB] total[63871 MB]
Free:  0.0265 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[58695 MB] total[63871 MB]
VECTOR SIZE = 1000000000
Allocate:  0.0000 sec, CPU Fraction 1.04
virtual[15264 MB] resident[3 MB] available[58695 MB] total[63871 MB]
Fill:  3.4095 sec, CPU Fraction 1.00
virtual[15264 MB] resident[15262 MB] available[43480 MB] total[63871 MB]
Free:  0.2503 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[58767 MB] total[63871 MB]
VECTOR SIZE = 2000000000
Allocate:  0.0000 sec, CPU Fraction 1.00
virtual[30523 MB] resident[3 MB] available[58767 MB] total[63871 MB]
Fill:  6.7911 sec, CPU Fraction 1.00
virtual[30523 MB] resident[30520 MB] available[28169 MB] total[63871 MB]
Free:  0.4940 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[58746 MB] total[63871 MB]
"""

tofevent_int64 = """VECTOR SIZE = 100000
Allocate:  0.0001 sec, CPU Fraction 1.01
virtual[7 MB] resident[3 MB] available[57201 MB] total[63871 MB]
Fill:  0.0005 sec, CPU Fraction 0.96
virtual[7 MB] resident[4 MB] available[57195 MB] total[63871 MB]
Free:  0.0001 sec, CPU Fraction 1.05
virtual[5 MB] resident[3 MB] available[57196 MB] total[63871 MB]
VECTOR SIZE = 1000000
Allocate:  0.0000 sec, CPU Fraction 0.98
virtual[20 MB] resident[3 MB] available[57196 MB] total[63871 MB]
Fill:  0.0044 sec, CPU Fraction 0.98
virtual[20 MB] resident[18 MB] available[57163 MB] total[63871 MB]
Free:  0.0007 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[57179 MB] total[63871 MB]
VECTOR SIZE = 10000000
Allocate:  0.0000 sec, CPU Fraction 0.98
virtual[158 MB] resident[3 MB] available[57179 MB] total[63871 MB]
Fill:  0.0467 sec, CPU Fraction 1.00
virtual[158 MB] resident[155 MB] available[56972 MB] total[63871 MB]
Free:  0.0031 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[57124 MB] total[63871 MB]
VECTOR SIZE = 100000000
Allocate:  0.0000 sec, CPU Fraction 0.99
virtual[1531 MB] resident[3 MB] available[57124 MB] total[63871 MB]
Fill:  0.4072 sec, CPU Fraction 1.00
virtual[1531 MB] resident[1528 MB] available[55645 MB] total[63871 MB]
Free:  0.0269 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[57151 MB] total[63871 MB]
VECTOR SIZE = 1000000000
Allocate:  0.0000 sec, CPU Fraction 1.00
virtual[15264 MB] resident[3 MB] available[57151 MB] total[63871 MB]
Fill:  4.0358 sec, CPU Fraction 1.00
virtual[15264 MB] resident[15261 MB] available[41895 MB] total[63871 MB]
Free:  0.2553 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[57181 MB] total[63871 MB]
VECTOR SIZE = 2000000000
Allocate:  0.0000 sec, CPU Fraction 1.01
virtual[30523 MB] resident[3 MB] available[57181 MB] total[63871 MB]
Fill:  8.0663 sec, CPU Fraction 1.00
virtual[30523 MB] resident[30520 MB] available[26583 MB] total[63871 MB]
Free:  0.5197 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[57160 MB] total[63871 MB]
"""

eventlistb = """VECTOR SIZE = 100000 PULSE_SIZE = 100
Allocate:  0.0001 sec, CPU Fraction 1.01
virtual[6 MB] resident[3 MB] available[50546 MB] total[63871 MB]
Fill:  0.0003 sec, CPU Fraction 1.01
virtual[6 MB] resident[4 MB] available[50534 MB] total[63871 MB]
Free:  0.0001 sec, CPU Fraction 1.01
virtual[5 MB] resident[3 MB] available[50554 MB] total[63871 MB]
VECTOR SIZE = 1000000 PULSE_SIZE = 1000
Allocate:  0.0000 sec, CPU Fraction 1.00
virtual[13 MB] resident[3 MB] available[50554 MB] total[63871 MB]
Fill:  0.0020 sec, CPU Fraction 1.00
virtual[13 MB] resident[10 MB] available[50554 MB] total[63871 MB]
Free:  0.0004 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[50577 MB] total[63871 MB]
VECTOR SIZE = 10000000 PULSE_SIZE = 10000
Allocate:  0.0000 sec, CPU Fraction 1.01
virtual[82 MB] resident[3 MB] available[50577 MB] total[63871 MB]
Fill:  0.0243 sec, CPU Fraction 1.00
virtual[82 MB] resident[79 MB] available[50490 MB] total[63871 MB]
Free:  0.0029 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[50572 MB] total[63871 MB]
VECTOR SIZE = 100000000 PULSE_SIZE = 100000
Allocate:  0.0000 sec, CPU Fraction 1.02
virtual[770 MB] resident[3 MB] available[50572 MB] total[63871 MB]
Fill:  0.2008 sec, CPU Fraction 1.00
virtual[770 MB] resident[767 MB] available[49812 MB] total[63871 MB]
Free:  0.0171 sec, CPU Fraction 1.00
virtual[7 MB] resident[4 MB] available[50587 MB] total[63871 MB]
VECTOR SIZE = 1000000000 PULSE_SIZE = 1000000
Allocate:  0.0000 sec, CPU Fraction 1.00
virtual[7650 MB] resident[4 MB] available[50586 MB] total[63871 MB]
Fill:  1.9304 sec, CPU Fraction 1.00
virtual[7650 MB] resident[7647 MB] available[42925 MB] total[63871 MB]
Free:  0.1327 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[50577 MB] total[63871 MB]
VECTOR SIZE = 2000000000 PULSE_SIZE = 2000000
Allocate:  0.0000 sec, CPU Fraction 1.00
virtual[15295 MB] resident[3 MB] available[50577 MB] total[63871 MB]
Fill:  3.8590 sec, CPU Fraction 1.00
virtual[15295 MB] resident[15292 MB] available[35287 MB] total[63871 MB]
Free:  0.2643 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[50593 MB] total[63871 MB]
VECTOR SIZE = 3000000000 PULSE_SIZE = 3000000
Allocate:  0.0000 sec, CPU Fraction 1.02
virtual[22939 MB] resident[3 MB] available[50593 MB] total[63871 MB]
Fill:  5.7872 sec, CPU Fraction 1.00
virtual[22939 MB] resident[22936 MB] available[27600 MB] total[63871 MB]
Free:  0.3885 sec, CPU Fraction 1.00
virtual[5 MB] resident[3 MB] available[50560 MB] total[63871 MB]
"""

def parseResult(text):
    vec_size = []
    allocate = []
    fill=[]
    free = []

    for line in text.split("\n"):
        line = line.strip()
        if "VECTOR SIZE" in line:
            vec_size.append(float(line.split()[3]))
        elif "Allocate" in line:
            allocate.append(float(line.split()[1]))
        elif "Fill" in line:
            fill.append(float(line.split()[1]))
        elif "Free" in line:
            free.append(float(line.split()[1]))
        else:
            pass # related to memory usage

    return vec_size, allocate, fill, free


print("="*5, "simplevec")

for text, label in zip((simplevec, tofevent_classic, tofevent_int64, eventlistb),
                       ("simple", "classic", "int64", "alt")):
    vec_size, allocate, fill, free = parseResult(text)
    plt.plot(fill, vec_size, label=label)
plt.ylabel("num events")
plt.xlabel("seconds")
plt.legend()
plt.show()
